"""
    File: how_deep.py
    Author: Jaylen Jenkins
    Date: 4/10/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        A recursive program that counts the depth of lists.
"""

"""
    Desc:
        - A recursive function that determines which list is deepest and returns a value equivalent to that depth.
    Accepts:
        - list_struct: The lists of lists/empty lists.
        - counter: Counts the current level of depth.
        - depth_list: A list that keeps track of all levels of depth.
        
    Returns:
        - depth: The primary return variable. Returns the lowest depth.
        - counter: The subordinate return variable. Occurs after reaching the lowest_depth a list.
"""
def how_deep(list_struct, counter, depth_list):
    # Base Case: If the received list is empty and it is the first list, then it returns the counter.
    if counter == 1 and not list_struct:
        return counter

    # If the list_struct has anything inside of it, then it appends the counter to the depth_list.
    if list_struct:
        depth_list.append(counter)

    # If it detects a list is empty, it will take the highest value out of the depth_list and set it to counter.
    # Counter is returned here.
    if not list_struct:
        # If the length of the depth_list is greater than one, it will compare the values within depth_list to each other.
        # Otherwise, it will just return the value of depth_list.
        if len(depth_list) > 1:
            for i in range(len(depth_list) - 1):
                if depth_list[i] > depth_list[i + 1]:
                    counter = depth_list[i]
                else:
                    counter = depth_list[i + 1]
        else:
            return counter

        return counter + 1

    # For-loop that runs for each element in depth_list.
    for i in range(len(list_struct)):
        depth = how_deep(list_struct[i], counter + 1, depth_list)

    return depth
    

if __name__ == '__main__':
    print(how_deep([[[], [], [], [[[]]]], []], 1, []))
    print(how_deep([], 1, []))
    print(how_deep([[], []], 1, []))
    print(how_deep([[[]], [], [[]], [[[]]]], 1, []))
    print(how_deep([[[[], [[]], [[[]]], [[[[]]]]]]], 1, []))
    print(how_deep([[[], []], [], [[], []]], 1, []))
