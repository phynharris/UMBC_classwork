"""
    File: catalan.py
    Author: Jaylen Jenkins
    Date: 4/10/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Gives the user the Catalan numbers of 0~20
"""

"""
    Desc:
        - A recursive function that generates Catalan numbers.
    Accepts:
        - num: The number being entered into the Catalan equation.
    Returns:
        - Returns a Catalan equation combined with recursive logic.
"""
def catalan(num):
    # Base Case: If the number is 0, then it returns a 1.
    if num == 0:
        return 1
    # Outside the base case, the number being tested is put through the Catalan equation.
    # This equation contains a recursion of the catalan function.
    else:
        return ((2 * ((2 * num) - 1)) * catalan(num - 1)) // (num + 1)


# Prints the Catalan Numbers for 0~20.
if __name__ == "__main__":
    for i in range(0, 20):
        print(i, catalan(i))
