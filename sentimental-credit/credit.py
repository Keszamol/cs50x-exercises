# ask user for input
def userinput():
    number = input("Number: ")
    return number


number = userinput()


# check the conditions of this input
def general_condition(number):
    while not number.isdigit():
        number = input("Number: ")
    return number


number = general_condition(number)


# implement the luhns algorithm for the checksum
def luhns_condition(number):

    number_length = len(number)
    number_length = int(number_length)
    i = number_length-2
    j = number_length-1
    k = 0
    multiply = []
    first = []

    for i in range(i, -1, -2):
        digit = int(number[i])
        product = digit * 2

        if product > 9:
            product -= 9
        multiply.append(product)

    for j in range(j, -1, -2):
        digit = int(number[j])
        first.append(digit)

    checksum = sum(multiply) + sum(first)
    return checksum


checksum = luhns_condition(number)


# credit card conditions
def credit_condition(number, checksum):
    if checksum % 10 != 0:
        print("INVALID")
        return

    number = str(number)

    if len(number) == 15 and number[:2] == "34" or number[:2] == "37":
        print("AMEX")
    elif len(number) == 16 and number[:2] >= "51" and number[:2] <= "55":
        print("MASTERCARD")
    elif number[:1] == "4" and len(number) == 13 or len(number) == 16 and number[:1] == "4":
        print("VISA")
    else:
        print("INVALID")


credit_condition(number, checksum)
