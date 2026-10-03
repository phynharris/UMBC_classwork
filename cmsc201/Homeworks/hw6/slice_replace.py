"""
    File: slice_replace.py
    Author: Jaylen Jenkins
    Date: 4/10/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Uses recursion to replace the insides of a string.
"""

"""
    Desc:
        - A recursive function that replaces desired parts of a string.
    Accepts:
        - big_string: The string whose contents are being tested to see if they match find_string.
        - find_string: The string that the user wants to get rid of from big_string.
        - replace_with: The string that the user wants injected into big_string.
    Returns:
        - A recursion of slice_replace if the base case is not met.
"""
def slice_replace(big_string, find_string, replace_with):
    # Variables
    # new_string takes the first character in big_string and goes up to the length of find_string.
    new_string = big_string[0:len(find_string)]

    # Base Case: If the length of the find_string is greater than the length of big_string, then only is big_string returned
    if len(find_string) > len(big_string):
        return big_string

    # If find_string is equal to new_string, then replace with is returned + a recursion of sice_replace.
    # This recursion of slice replace accepts a slice of big_string with new_string taken out of it.
    if find_string == new_string:
        return replace_with + slice_replace(big_string[len(find_string):], find_string, replace_with)
    # Else, return the first letter in new_string + a recursion of sice_replace.
    # This recursion of slice_replace accepts a slice of big_string with new_string[0] removed.
    else:
        return new_string[0] + slice_replace(big_string[1:], find_string, replace_with)


"""
    Asks the user for the big_string, the find_string, and the replace_with string.
    Afterwards, it prints out the result of the recursive function slice_replace.
"""
if __name__ == "__main__":
    big_string = input("Enter a string: ")
    find_string = input("What part of your string do you want to replace? ")
    replace_with = input("What do you want to replace it with? ")

    print(slice_replace(big_string, find_string, replace_with))
