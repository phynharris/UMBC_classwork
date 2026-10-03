"""
File:         names.py
Author:       Jaylen Jenkins
Date:         3/25/2025
Section:      25
E-mail:       fp31977@umbc.edu
Description:  YOUR DESCRIPTION GOES HERE AND HERE
              YOUR DESCRIPTION CONTINUED SOME MORE
"""


def sum_list(numbers):
    """
    Sums a list of integers
    :param numbers: a list of integers
    :return: the sum of the integers in numbers
    """
    sum = 0
    for i in range(len(numbers)):
        sum += numbers[i]

    return sum


def get_string_lengths(strings):
    """
    Given a list of strings, return a list of integers representing
    the lengths of the input strings
    :param strings: a list of strings
    :return: a list of integers representing the lengths of the input strings
    """

    pets_length = []
    for string in strings:
        pets_length.append(len(string))

    return pets_length


def get_names():
    """
    Asks the user for a list of names
    :return: a list of strings for the names the user entered
    """


if __name__ == '__main__':
    kitties = [
        "Jules",
        "Stubby",
        "Tybalt",
        "Scooter",
        "KC",
        "Garfield",
        "Bucky"
    ]

    # print the sum of the lengths of the strings in kitties
    print("There are", sum_list(get_string_lengths(kitties)), "letters in kitties.")

    puppers = [
        "Charlie",
        "Chuck",
        "Chuckadero",
        "Char",
        "Charmander",
        "Charles, Lord of Hearts, King of Snuggles"
    ]

    # prints the sum of the lengths of the strings in puppers
    print("There are", sum_list(get_string_lengths(puppers)), "letters in puppers.")
    # gets names from the user and reports how many letters are in all the names

    names = []
    name = ""

    while name != "quit":
        name = input("Enter a name: ")

        if name != "quit":
            names.append(name)

    print("There are", sum_list(get_string_lengths(names)), "letters in your list of names.")
