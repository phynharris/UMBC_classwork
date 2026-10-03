"""
    File: ab_equality.py
    Author: Jaylen Jenkins
    Date: 4/10/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        The user enters a number and will be told the possible combinations of a's and b's where there are the same
            amount.
"""

"""
    Desc:
        - A recursive function that creates all possible of ab combinations.
        - It will only print out combinations where the number of a's and number of b's are the same.
    Accepts:
        - n: The variable representing how many more a's or b's may be added to the string.
        - k: Compares the number of a's and b's. If 0, then the # of a's and b's are the same.
        - current: The current string, it starts empty, and is appended over the recursion.
    Returns:
        - If none of the base cases are met, then it returns a recursion of itself,
            add a: a is appended to current and k increments by 1.
            add b: b is appended to current and k decrements by 1.
"""
def a_and_b(n, k, current):
    # Base Case: The user will be presented an error if they enter an odd number.
    if current == "" and n % 2 == 1:
        print("That number cannot be used here because it is odd.")
        return

    # Base Case: If n is equal to 0, then current is returned.
    # This will also occur at the end of the function.
    if n == 0:
        if k == 0:
            print(current)
        return

    # Adds an 'a', k increments by 1.
    a_and_b(n - 1, k + 1, current + 'a')

    # Adds an 'b', k decrements by 1.
    a_and_b(n - 1, k - 1, current + 'b')

if __name__ == "__main__":
    # Calls the a_and_b function,
    # The first argument is am input function that asks the user for the number they want.
    a_and_b(int(input("Enter a number get all possible combinations of ab when there are equal a's and b's. ")), 0, "")
