"""
    File: list_diff.py
    Author: Jaylen Jenkins
    Date: 2/22/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Requests user input for the length of lists and makes the user enter a number in each element.
        The program then compares the two lists, and it tells the user where there are differences.
"""

if __name__ == "__main__":
    list_a = []
    list_b = []
    difference = []
    list_size = int(input("How large do you want your lists to be? "))

    #Nested for loops that gather the user input for each list. They append each number into the list.
    for i in range(2):
        if i == 0:
            for j in range(list_size):
                number = int(input(f"What is the {j + 1}th integer? "))
                list_a.append(number)
        elif i == 1:
            for k in range(list_size):
                number = int(input(f"What is the {k + 1}th integer? "))
                list_b.append(number)

    # This for loop compares the nth element in each list. If they're different, it keeps track of that.
    for l in range(list_size):
        if list_a[l] != list_b[l]:
            difference.append(l)

    if len(difference) == 0:
        print("There are no differences in these lists. ")
    else:
        print(f"There are differences at position {difference}.")
