import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    if 'user_id' in session:
        user_id = session['user_id']

    # Hole das aktuelle Bargeld des Benutzers
    money = db.execute("SELECT cash FROM users WHERE id = ?", (user_id,))

    if money:
        cash = money[0]['cash']
    else:
        cash = 0

    # Hole alle Aktien des Benutzers
    rows = db.execute(
        "SELECT stock, sum(share) AS total_shares, price FROM purchase WHERE user_id = ? GROUP BY stock", (user_id,))

    total_value = cash  # Setze den initialen Gesamtwert auf das Bargeld

    # Iteriere durch jede Aktie und berechne den Gesamtwert
    for row in rows:
        stock_symbol = row['stock']
        stock = lookup(stock_symbol)  # Hole den aktuellen Preis für das Stock
        if stock:
            row['actual_price'] = stock['price']  # Setze den aktuellen Preis
            row['value'] = row['total_shares'] * row['actual_price']  # Berechne den Gesamtwert
            total_value += row['value']  # Füge den Wert der Aktie zum Gesamtwert hinzu
        else:
            row['actual_price'] = None
            row['value'] = 0

    return render_template("index.html", cash=cash, rows=rows, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if 'user_id' in session:
        user_id = session['user_id']

    money = db.execute("SELECT cash FROM users WHERE id = ?", (user_id,))

    if money:
        cash = money[0]['cash']

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing symbol", 400)

        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol", 400)

        share = request.form.get("shares")

        try:
            share = int(share)
            if share <= 0:
                return apology("You need a positive number of shares", 400)
        except ValueError:
            return apology("You need to enter a valid number for shares", 400)

        price = stock["price"]
        total_price = price * share

        if cash < total_price:
            return apology("You do not have enough money to buy this", 400)

        db.execute("INSERT INTO purchase (user_id, stock, share, price) VALUES (?, ?, ?, ?)",
                   user_id, symbol, share, price)
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_price, user_id)
        db.execute("INSERT INTO transactions (user_id, action, stock, share, price) VALUES (?, ?, ?, ?, ?)",
                   user_id, "buy", symbol, share, price)

        return redirect("/")

    return render_template("buy.html", cash=cash)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session['user_id']

    # Holen der Transaktionen des Benutzers aus der Datenbank
    rows = db.execute(
        "SELECT Action, stock, share, Price, date FROM transactions WHERE user_id = ? ORDER BY date DESC", (user_id,))

    # Durchlaufe alle Zeilen und setze die Werte für Kauf und Verkauf
    for row in rows:
        action = row['Action'].strip().lower()  # Entferne Leerzeichen und setze Kleinbuchstaben

        if action == 'buy':
            row['value'] = row['share']  # Für Kauf, nur die Anzahl der Aktien
        elif action == 'sell':
            row['value'] = -row['share']  # Für Verkauf, die negative Anzahl der Aktien
        else:
            row['value'] = 0  # Wenn keine gültige Aktion

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing symbol")

        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol")

        return render_template("quoted.html", stock=stock)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        password = request.form.get("password")
        username = request.form.get("username")

        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("Password must be confirmed with same password", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        try:
            # Versuche, den Benutzernamen zusammen mit dem Passwort zu speichern
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, generate_password_hash(password))
        except ValueError as e:
            # Prüfen, ob es sich um einen Fehler wegen des UNIQUE Constraints handelt
            if "UNIQUE constraint failed" in str(e):
                return apology("Username already exists", 400)
            else:
                # Für andere Fehler kannst du hier eine allgemeine Fehlerbehandlung hinzufügen
                return apology("Unexpected Error", 400)

        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if 'user_id' in session:
        user_id = session['user_id']

    # Hole alle gekauften Aktien des Benutzers und aggregiere die Anzahl der Aktien pro Symbol
    rows = db.execute("""
        SELECT stock, SUM(share) AS total_shares
        FROM purchase
        WHERE user_id = ?
        GROUP BY stock
    """, (user_id,))

    if request.method == "POST":
        share = request.form.get("shares")
        stock_symbol = request.form.get("symbol")

        try:
            share = int(share)
        except ValueError:
            return apology("You need to type a valid amount", 403)

        if not stock_symbol:
            return apology("You need to select a stock", 403)

        elif share <= 0:
            return apology("You need to type a positive amount", 403)

        # Durchlaufe alle Aktien des Benutzers
        for row in rows:
            if stock_symbol == row['stock']:
                stock_symbol = row['stock']
                stock = lookup(stock_symbol)

                # Überprüfen, ob der Benutzer genug Aktien zum Verkauf hat
                if share > row['total_shares']:
                    return apology("You don't own that many shares")

                # Berechne den Verkaufspreis und die Menge
                price = stock['price']
                sale_value = share * price

                # Wenn alle Aktien verkauft werden, lösche sie, andernfalls aktualisiere den Anteil
                db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", sale_value, user_id)
                db.execute("INSERT INTO transactions (user_id, action, stock, share, price) VALUES (?, ?, ?, ?, ?)",
                           user_id, "sell", stock_symbol, share, price)

                # Lösche oder aktualisiere die Aktien in der Kauf-Tabelle
                db.execute("""
                    UPDATE purchase
                    SET share = share - ?
                    WHERE stock = ? AND user_id = ? AND share >= ?
                """, share, stock_symbol, user_id, share)

                if row['total_shares'] == share:
                    db.execute("DELETE FROM purchase WHERE stock = ? AND user_id = ?",
                               stock_symbol, user_id)

                return redirect("/")

        return apology("You don't own this stock", 403)

    return render_template("sell.html", rows=rows)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        user_id = session['user_id']
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirm_password")

        if not current_password or not new_password or not confirm_password:
            return apology("All fields must be filled out", 403)

        if new_password != confirm_password:
            return apology("New password and confirmation do not match", 403)

        rows = db.execute("SELECT hash FROM users WHERE id = ?", user_id)

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], current_password):
            return apology("Incorrect current password", 403)

        db.execute("UPDATE users SET hash = ? WHERE id = ?",
                   generate_password_hash(new_password), user_id)

        return redirect("/")

    return render_template("change_password.html")
