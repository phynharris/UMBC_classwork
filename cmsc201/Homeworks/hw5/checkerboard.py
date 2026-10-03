"""
    File: checkerboard.py
    Author: Jaylen Jenkins
    Date: 3/14/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Creates a checkerboard by asking the user for its size and which symbols represent the squares.
"""

def checkerboard(size, symbols):
    symbols_list = symbols.split()

    while len(symbols_list) != 2:
        symbols = input("Error. Invalid amount of symbols.\n"
                        "Enter the symbols you want for the board? ")
        symbols_list = symbols.split()

    symbol1 = symbols_list[0]
    symbol2 = symbols_list[1]

    for y in range(size):
        if y % 2 == 0:
            for x in range(size):
                if x % 2 == 0:
                    print(symbol1, end="")
                else:
                    print(symbol2, end="")
        elif y % 2 == 1:
            for x in range(size):
                if x % 2 == 1:
                    print(symbol1, end="")
                else:
                    print(symbol2, end="")
        print("")

if __name__ == "__main__":
    size = int(input("How large do you want your checkerboard? "))
    symbols = input("What are the symbols you want for the board? ")

    checkerboard(size, symbols)
