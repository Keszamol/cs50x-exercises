import cs50

MIN = 1
MAX = 8


def input_condition():  # User value must be between 1 and 8 and contain only digits
    height = input("Height: ")  # User query of height
    while not height.isdigit() or int(height) < MIN or int(height) > MAX:
        height = input("Height: ")
    return height


height = input_condition()


def pyramid(height):
    hash_count = 0
    for i in range(int(height)):  # Outer loop, sets the lines based on the height input
        print("")
        height = int(height)-1  # After each pass, height -1 (space)
        hash_count = int(hash_count)+1  # After each pass, hash +1 (#)
        for j in range(height):  # Inner Loop 1: Prints the spaces on the left pyramide
            print(" ", end="")
        for k in range(hash_count):  # Inner Loop 2: Prints the hashes on the left pyramide
            print("#", end="")
        print(" ", end="")
        for l in range(hash_count):  # Inner Loop 3: Prints the hashes on the left pyramide
            print("#", end="")
        for m in range(height):  # Inner Loop 4: Prints the spaces on the left pyramide
            print(" ", end="")

    print("")  # printing a new line after the function


pyramid(height)
