SELECT description
FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Crime Infos: 10:15 am, in the Bakery, littering 16:36, interview same day with 3 whitnesses, interview transcript mentions bakery

SELECT name, transcript
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

--- Whitnesses: Ruth, Eugene, Rayomnd

--- Infos:
---         - Within 10 min of the theft -> Thief is in a car at bakery parking lot
---         - Thief was seen earlyer morning by the ATM on Leggett Street, withdrawing money
---         - Thief called someone after theft (call was less than a minute). Planning to takte the earlyest flight tomorrow, purchased it after theft.

SELECT account_number, amount
FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type = 'withdraw';

SELECT name
FROM people
WHERE id IN (

    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN ('28500762', '28296815', '76054385', '49610011', '16153065', '25506511', '81061156', '26013199')
);

--- People at ATM: Kenny, Iman, Benista, Taylor, Brooke, Luca, Diana, Bruce

SELECT license_plate
FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30;

SELECT name
FROM people
WHERE license_plate IN ('5P2BI95', '94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55');

--- People car: Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce
--- People doubled: Iman, Luca, Diana, Bruce


SELECT name
FROM people
WHERE phone_number IN (

    SELECT caller
    FROM phone_calls
    WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
);

-- Caller Double: Diana, Bruce


SELECT name, passport_number
FROM people
WHERE passport_number IN (

    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (

        SELECT id
        FROM flights
        WHERE year = 2024 AND month = 7 AND day = 29 AND hour < 12
    )
)
ORDER BY name ASC;

-- Thief = Bruce with passport_number = 5773159633

SELECT id
FROM flights
WHERE id IN (

    SELECT flight_id
    FROM passengers
    WHERE passport_number = '5773159633'
);

-- Flug-ID = 36

SELECT full_name, city
FROM airports
WHERE id IN (

    SELECT destination_airport_id
    FROM flights
    WHERE id = '36'
);

-- LaGuardia Airport in New York City

SELECT name
FROM people
WHERE phone_number IN (

    SELECT receiver
    FROM phone_calls
    WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60 AND caller = 'Bruce'
);

-- Accompile is Robin
