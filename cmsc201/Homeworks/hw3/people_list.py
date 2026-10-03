"""
    File: people_list.py
    Author: Jaylen Jenkins
    Date: 2/22/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program allows the user to pick the step value for how often then main for program runs.
        They will then be told to add a name, remove a name, or find the longest name in the list.
        If the longest name is tied with another name, the highest in lexicographical order is chosen.
"""

if __name__ == "__main__":
    # Variable set up. steps is selected by the user.
    steps = int(input("How many steps should this program run? "))
    my_list = []
    name_exists = False #Is used in the [remove] code to determine if a name exists in the list.
    longest_name = ""

    for i in range(steps):

        # Prompts the user to pick one of three actions.
        # If the user enters an invalid option, the step is skipped.
        action_input = input(f"Step {i + 1}/{steps}. \n"
              f"'add [name]': Add a name to your list. \n"
              f"'remove [name]': Remove a name from your list. \n"
              f"'max': Print the longest name in the list. \n"
              f"What is your action? ")

        # Splits the input into 'action', and 'name' (if applicable).
        action = action_input.split()

        # Uses the append function to add a name to the list.
        if action[0].lower() == "add":
            my_list.append(action[1])
            print(f"\nAdded name: '{action[1]}'.")
            print("Current list of names:", my_list)

        # Uses the remove function to get rid of the desired name.
        # If the name does not exist, it will display an error to the user.
        elif action[0].lower() == "remove":
            name_exists = False
            for name in my_list:
                if name == action[1]:
                    my_list.remove(name)
                    name_exists = True
                    print(f"\nRemoved name: '{action[1]}'.")
                    print("Current list of names:", my_list)

            if name_exists == False:
                print("\nThat name does not exist. ")

        # Will go through the list and determine which name has the longest length.
        elif action[0].lower() == "max":
            if len(my_list) > 0: #If there is nothing in the list, then the user is given an error message.
                longest_name = my_list[0]
                if len(my_list) != 0: #If there is only one word in the list, then that is the longest word.
                    # Starting at index 0 and going until one less than the length of the list, it will determine
                    # if the following word is longer.
                    for j in range(len(my_list) - 1):
                        if len(longest_name) < len(my_list[j + 1]):
                            longest_name = my_list[j + 1]
                        # If the longest name ever results in a tie, the highest in lexicographical order is favored.
                        elif len(longest_name) == len(my_list[j + 1]):
                            if longest_name > my_list[j + 1]:
                                longest_name = my_list[j + 1]
                print(f"Longest name is '{longest_name}'. ")
            else:
                print("\nError. There are no names.")
        else:
            print("\nError, action is not 'add', 'delete', or 'max'. Step skipped.")

    print("\nList of names is:", my_list)
