"""
    File: pascal.py
    Author: Jaylen Jenkins
    Date: 3/14/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Prompts the user to enter a bunch of numbers.
        Program takes the pascal sum of them.
"""

# Takes in nothing and returns a list of numbers.
def next_level():
    # Asks for the values the user wants and then splits them
    num_input = input("What values do you want to run the next level on? ").lower()
    while num_input == "":
        num_input = input("What values do you want to run the next level on? ").lower()

    num_list = num_input.split()

    return num_list

# Takes a list of numbers and returns a list of the pascal sum of the numbers in the initial list.
def num_adder(init_list):
    pascal_list = []

    # The first element in the new list is the first element in the initial list.
    pascal_list.append(int(init_list[0]))

    pascal_sum = 0

    # Takes the pascal sum of each element in the given list and appends it to a new list.
    for i in range(len(init_list) - 1):
        pascal_sum = int(init_list[i]) + int(init_list[i + 1])
        pascal_list.append(pascal_sum)
        pascal_sum = 0

    # Makes the last element in the pascal list equal to 1
    pascal_list.append(1)

    # Turns the numbers to strings and joins them to a single string
    pascal_numbers = "".join(str(pascal_list))

    return pascal_numbers


if __name__ == "__main__":
    program = ''
    while program != "quit":
        # Takes the input for the pascal triangle
        given_list = next_level()

        # Sums the numbers, creating the sum for the triangle.
        pascal_nums = num_adder(given_list)

        print(pascal_nums)

        program = input("Enter 'quit' to quit. ").lower()
