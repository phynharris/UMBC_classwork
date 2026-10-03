"""
    File: quasi_palindrome.py
    Author: Jaylen Jenkins
    Date: 3/14/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Asks the user for a word and determines if it is a quasi-palindrome.
"""

# Determines if the user's word is a quasi-palindrome
def quasi_palindrome(word, errors):
    error_count = 0

    # Takes the first half of the word
    first_half = word[:len(word) // 2]

    # Takes the second half of the word and reverses it
    second_half = word[:len(word) // 2 - 1:-1]
    is_palindrome = True

    # Compares the first half and the reversed second half and counts the differences between them.
    for i in range(len(first_half)):
        if first_half[i] != second_half[i]:
            error_count += 1

    # If the number of errors is greater than the tolerance, then the word is not a palindrome.
    if error_count > errors:
        is_palindrome = False

    return is_palindrome

if __name__ == "__main__":
    palindrome = ""
    # Program will terminate once the user enters 'quit'.
    while palindrome != "quit":
        palindrome = input("\n('quit' to quit)\n"
                           "What is the word you wish to check? ")

        if palindrome.lower() != "quit":
            tolerance = int(input("What is the maximum amount of errors you'll allow? "))

            result = quasi_palindrome(palindrome.lower(), tolerance)

            if result:
                print(f"{palindrome} is a {tolerance}-quasi-palindrome")
            else:
                print(f"{palindrome} is not a {tolerance}-quasi-palindrome")
