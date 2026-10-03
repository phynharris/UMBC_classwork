"""
    File: factor_me.py
    Author: Jaylen Jenkins
    Date: 2/28/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program asks the user for a number and will display the prime factors of that number
        if they are any less than 50.
"""

if __name__ == "__main__":
    list_of_primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47][::-1]
    factors = []
    counter = 0

    # Allows the user to enter a number. Number must be greater than 1.
    given_num = int(input("Enter a number and see its prime factors: "))
    while given_num <= 1:
        given_num = int(input("Error. Cannot determine factors of that number.\n"
                              "Enter a number and see its prime factors: "))
    num = given_num

    # While loop that checks if the modulus of the given number by each prime number is 0.
    while counter < len(list_of_primes):
        # If it is zero, the while loop resets and checks with the next number.
        # The next number is the given number divided by the prime number that resulted in mod 0.
        if num % list_of_primes[counter] == 0:
            factors.append(str(list_of_primes[counter]))
            num = num / list_of_primes[counter]
            counter = 0
        # If the number's mod is not 0, then it moves onto the next prime in the list.
        else:
            counter += 1

    # Whether or not the number has at least two prime factors less than 5-, it prints the appropriate response.
    if len(factors) > 0:
        print(f"{given_num}'s factors are:", " * ".join(factors))
    else:
        print(f"{given_num} has no factors less than 50.")
