"""
    File: binary.py
    Author: Jaylen Jenkins
    Date: 4/10/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Converts decimal numbers to binary numbers via recursion.
"""

"""
    Desc:
        - Converts a given decimal number to a binary number.
    Accepts:
        - dec_num: The number to be determined either odd of even.
        - og_number: The original number.
    Returns:
        - A recursion of itself with either + '0' or '1', so that it returns the binary num in sequential order.
"""
def to_bin(dec_num, og_number):
    # Base Case: If the scrutinized number is a 0.
    if dec_num == 0:
        # If the original number is 0, then a zero is returned.
        if og_number == 0:
            return str(dec_num)
        # If the original number is not a 0, then it returns an empty string.
        else:
            return ""

    # If the number is even, a 0 is added to the end of the number.
    # If the number is odd, a 1 is added to the end of the number.
    if dec_num % 2 == 0:
        return str(to_bin(dec_num // 2,og_number)) + "0"
    elif dec_num % 2 == 1:
        return str(to_bin(dec_num // 2, og_number)) + "1"


if __name__ == "__main__":
    # The user enters the number they want to convert from decimal to binary here.
    # It will call a recursive function to convert the number.
    # The loop will stop when the user enters a number less than or equal to -1.
    number = int(input("Enter a number: "))
    while number > -1:
        binary = to_bin(number, number)
        print("0b" + binary, bin(number))
        number = int(input("Enter a number: "))

