QUARTERS = 25
DIMES = 10
NICKELS = 5
PENNIES = 1


# ask user for change input
def userinput():
    change = input("Change: ")
    return change


change = userinput()


# check user input conditions
def input_conditions(change):
    while change.isalpha() or change == "" or float(change) < 0:
        change = input("Change: ")
    change = float(change) * 100
    change = int(change)
    return change


change = input_conditions(change)


# calculate how much coins you have to give
def calculate_change(change):

    quar_change = int(change) // int(QUARTERS)
    quar_rest = int(change) % int(QUARTERS)

    dim_change = int(quar_rest) // int(DIMES)
    dim_rest = int(quar_rest) % int(DIMES)

    nick_change = int(dim_rest) // int(NICKELS)
    nick_rest = int(dim_rest) % int(NICKELS)

    pen_change = int(nick_rest) // int(PENNIES)

    return quar_change, dim_change, nick_change, pen_change


quar_change, dim_change, nick_change, pen_change = calculate_change(change)


# print result
def print_change(quar_change, dim_change, nick_change, pen_change):

    sum = quar_change + dim_change + nick_change + pen_change
    print(int(sum))


print_change(quar_change, dim_change, nick_change, pen_change)
