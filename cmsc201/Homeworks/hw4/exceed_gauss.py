"""
    File: exceed_gauss.py
    Author: Jaylen Jenkins
    Date: 2/26/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program takes an int input from the user and takes the Gauss Sum of that number until it exceeds it,
        and prints it out.
"""

if __name__ == "__main__":

    gauss_num = 0
    counter = 1

    # Requests the number
    pos_int = int(input("What is a number you'd like to take the Gauss Sum of until it "
                        "equals or exceeds your number? "))

    # While the gauss sum is lower than the given number, it will continue to add numbers.
    while gauss_num < pos_int:
        gauss_num = gauss_num + counter
        counter += 1

    print(f"After {counter - 1} iterations, the Gauss Sum is {gauss_num}, which equals or exceeds {pos_int}.")
