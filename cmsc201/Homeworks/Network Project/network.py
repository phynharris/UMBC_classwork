"""
    File: network.py
    Author: Jaylen Jenkins
    Date: 5/3/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        pass
"""

COMMANDS = ["switch-add", "switch-connect",
            "phone-add", "start-call", "end-call",
            "display", "network-save", "network-load",
            "quit"]
NUMBERS = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]

"""
    Desc:
        - Verifies that eah character in a string is a number
    Parameters:
        - string: The string being tested
    Returns:
        - True/False: False if there is an extant non-number character, otherwise True.
"""
def verify_num(string):
    for character in string:
        # If a character in a string is not a number, then the string is invalid and False is returned.
        if character not in NUMBERS:
            return False

    return True

"""
    Desc:
        - Allows the user to create a new switchboard.
    Parameters:
        - area_codes: The current dictionary of switchboards.
        - area_code: The area code the user entered.
        - connections: The dictionary that shows which switchboards connect to each other.
    Returns:
        - None
"""
def switch_add(area_codes, area_code, connections):
    # If the area code already exists, then it is not added again.
    if area_code in area_codes:
        print("That area code already exists")
    # If there are non-number characters in the are_code, then the command fails.
    elif not verify_num(area_code):
        print("Invalid area code")
    # Else the area code is set as a key for the area_codes and connections dictionaries.
    else:
        print(f"Created switchboard with area code {area_code}")
        area_codes[area_code] = []
        connections[area_code] = []

    return

"""
    Desc:
        - Connects two switchboards to each other.
    Parameters:
        - area_codes: the dictionary of switchboards/area codes.
        - connections: the dictionary of switchboard connections.
        - ac_one: the first area code in question.
        - ac_two: the second area code in question
    Returns:
        - None
"""
def switch_connect(area_codes, connections, ac_one, ac_two):
    # Prevents the user from connecting a switchboard to itself
    if ac_one == ac_two:
        print("Please enter two different area codes")
    # Checks if either area code exists. If either does not, then the user is informed.
    elif ac_one not in area_codes or ac_two not in area_codes:
        print("One or more of the area codes you entered do not exist")
    # Checks if the connection has already been made.
    elif ac_two in connections[ac_one]:
        print("That connection has already been made")
    # If neither of the above apply, then the switchboards are connected.
    else:
        print(f"Connection made between switchboards {ac_one} and {ac_two}")
        connections[ac_one].append(ac_two)
        connections[ac_two].append(ac_one)

    return

"""
    Desc:
        - Removes the hyphens out of a phone number and splits the number into a list.
    Parameters:
        - number: The string to have its hyphens removed.
    Returns:
        - number: The string with its hyphens now removed.
"""
def split_hyphens(number):
    number = number.split("-")  # Splits the phone number into a list with a length dependent on the # of hyphens.

    return number

"""
    Desc:
        - Determines if an area code exists.
    Parameters:
        - area_codes: The dictionary of switchboards/area codes.
        - area_code: The area code being tested.
    Returns:
        - True/False: True if an area_code exists.
"""
def ac_exists(area_codes, area_code):
    # Checks if a particular area code is in the switchboards
    if area_code in area_codes:
        return True
    else:
        return False

"""
    Desc:
        - Adds a phone number to a switchboards.
    Parameters:
        - area_codes: Dictionary of all area codes.
        - phone_number: The phone number that the user entered.
        - calls: The dictionary of phones in a call.
    Returns:
        - None
"""
def phone_add(area_codes, phone_number, calls):
    # Checks if there are any hyphens in the number.
    if "-" in phone_number:
        # Returns the phone-number as a list.
        num_split = split_hyphens(phone_number)
    else:
        print("Invalid phone number")
        return

    # If there are unnecessary hyphens (e.g. 410--- or 555-5-), then the command fails.
    for num in num_split:
        if not num:
            print("Invalid phone number")
            return

    # Lists and Vars
    area_code = num_split[0]
    partial_num = "".join(num_split[1:]) #Phone number w/o the area code
    standard_phone = area_code + "-" + partial_num # Phone num set up like XXX-XXXXXXXX
    calls[standard_phone] = ""

    # If the area code does not exist, then the command fails.
    if not ac_exists(area_codes, area_code):
        print(f"Error. Area code {area_code} does not exist.")
        return
    # If the number already exists, then the command fails.
    elif standard_phone in area_codes[area_code]:
        print("Error. That number already exists.")
        return
    # Appends the num into the area_codes[area_code].
    else:
        print(f"Added {partial_num} to {area_code}")
        area_codes[area_code].append(area_code + "-" + partial_num)

"""
    Desc:
        - Recursive function for validating a phone call.
    Parameters:
        - boards: Dictionary of switchboards
        - connections: Dictionary of switchboard connections
        - test_switch: The area code that is currently being tested
            its initialized as the first area code the user entered.
        - static_switch: Used to see if both area codes entered by the user match.
            this is always the second area code the user entered.
        - phone1: The first phone number.
        - phone2: The second phone number.
        - tried: A list of area codes that have already been tried.
    Returns:
        - True/False: If the phone call can be made (if the switchboards connect)
"""
def call_valid_recursive(boards, connections, test_switch, static_switch, phone1, phone2, tried):
    # If no numbers have been tried, then it checks if both area codes entered are the same.
    # The initial area code will then be appended to tried.
    if not tried:
        tried.append(test_switch)

        # If phone numbers exists in the area code, then the call works.
        if test_switch == static_switch and phone1 in boards[static_switch] and phone2 in boards[static_switch]:
            return True

        # If the first phone number is not in the first area code, then the call fails.
        if phone1 not in boards[test_switch]:
            return False

    # For as many connections as the area code being tested has...
    for code in connections[test_switch]:

        # Numbers that have been tried will be skipped.
        if code not in tried:

            # If the second phone_number is found in the switchboard currently being checked, then the call works.
            if phone2 in boards[code]:
                return True

            # Recursive case
            else:
                # Appends the tested area code to tried.
                tried.append(code)
                return call_valid_recursive(boards, connections, code, static_switch, phone1, phone2, tried)

    return False

"""
    Desc:
        - Checks if the phone call the user wants to make is valid.
    Parameters:
        - boards: Dictionary of switchboards
        - connections: Dictionary of switchboard connections
        - phone_nums: List of entered phone numbers
        - calls: Dictionary of phone calls
    Returns:
        - True/False: If the phone call can be made (if the switchboards connect)
"""
def call_valid(boards, connections, phone_nums, calls):
    # Lists
    index_range = len(phone_nums)
    area_codes = [""] * index_range
    rem_nums = [""] * index_range

    # If there are hyphens in both phone numbers, then the variables are declared.
    # Otherwise, the call fails.
    for i in range(index_range):
        num = phone_nums[i]

        # If hyphens are present in the number, then the number is split into a list based on the hyphens.
        if "-" in num:
            num = split_hyphens(num)
            area_codes[i] += num[0]
            rem_nums[i] = combine_num(num[1:])

            # If the user enters hyphens inappropriately (eg 410--434, 4-1-) then, the command fails.
            if not rem_nums[i]:
                print("At least one of the numbers you entered was invalid")
                return False

        # If there are no hyphens, then the command fails.
        else:
            print("At least one of the numbers you entered is invalid")
            return False

    # Vars
    first_num = area_codes[0] + "-" + rem_nums[0]
    second_num = area_codes[1] + "-" + rem_nums[1]

    # Call fails if neither area code exists.
    if not (ac_exists(boards, area_codes[0]) and ac_exists(boards, area_codes[1])):
        print("One or more of the are codes you entered do not exist")
        return False

    # If neither phone number exists, then the call is invalid.
    if first_num not in boards[area_codes[0]] or second_num not in boards[area_codes[1]]:
        print("One or more of those phone numbers do not exist")
        return False

    # If one of the numbers is already in a call, then the command fails.
    if calls[first_num] or calls[second_num]:
        print("One or more of those numbers is already in a call")
        return False

    # Calls a recursive function to verify that the phone numbers are valid.
    if call_valid_recursive(boards, connections, area_codes[0], area_codes[1], first_num, second_num, []):
        return True

    return False

"""
    Desc:
        - Combines parts of phone nuber strings into a single string
    Parameters:
        - string_list: A list of strings to be combined.
    Returns:
        - combined_num: The combined phone number string 
"""
def combine_num(string_list):
    combined_num = ""
    # For each number in the string, that number is appended to the combined_num string
    for number in string_list:
        combined_num += number

    return combined_num

"""
    Desc:
        - Puts two (verified) phone numbers into a call
    Parameters:
        - phone_nums: List of the two phone numbers entered
        - calls: The dictionary of phone calls
"""
def start_call(phone_nums, calls):

    # Converts a phone number into XXX-XXXXXXX
    for i in range(len(phone_nums)):
        num = phone_nums[i]
        num = split_hyphens(num)
        rem = combine_num(num[1:])

        num = num[0] + "-" + rem
        phone_nums[i] = num

    # Puts the other number into either's call dict.
    calls[phone_nums[0]] = phone_nums[1]
    calls[phone_nums[1]] = phone_nums[0]

    print(f"{phone_nums[0]} is calling {phone_nums[1]}")

    return

"""
    Desc:
        - Ends a call between two phone numbers.
    Parameters:
        - num1: The first phone_number
        - num2: The second phone number
        - calls: The dictionary of phone calls
        - area_codes: The dictionary of switchboards
    Returns:
        - None
"""
def end_call(num1, num2, calls, area_codes):
    # Vars
    ac_1 = split_hyphens(num1)[0]
    ac_2 = split_hyphens(num2)[0]
    partial_num1 = "".join(split_hyphens(num1)[1:])
    partial_num2 = "".join(split_hyphens(num2)[1:])
    
    # If the user enters hyphens inappropriately (eg 410--434, 4-1-) then, the command fails.
    if not partial_num1 or not partial_num2:
        print(partial_num2, partial_num1)
        print("One or more of those phone numbers do not exist")
        return

    # Phone num set up like XXX-XXXXXXXX 
    adjusted_num1 = ac_1 + "-" + partial_num1
    adjusted_num2 = ac_2 + "-" + partial_num2

    # If neither phone number exists, then the command fails
    if adjusted_num1 not in area_codes[ac_1] or adjusted_num2 not in area_codes[ac_2]:
        print(adjusted_num1, area_codes[ac_1])
        print(adjusted_num2, area_codes[ac_2])
        print("One or more of those phone numbers do not exist")

    # If neither area code exists, then the command fails
    elif ac_1 not in area_codes or ac_2 not in area_codes:
        print("One ore more of those area codes do not exist")

    # If the numbers aren't in a call with each other, then the command fails
    elif adjusted_num1 not in calls[adjusted_num2]:
        print(f"{num1} & {num2} are not in a call")

    # If the numbers are in a call, then the call is ended
    elif adjusted_num1 in calls[adjusted_num2]:
        print(f"Ending call between {num1} and {num2}")
        calls[adjusted_num1] = ""
        calls[adjusted_num2] = ""

    return

"""
    Desc:
        - Displays the switchboards
    Parameters:
        - sb: Dictionary of switchboards
        - connections: Dictionary of switchboard connections
        - calls: Dictionary of phone calls
    Returns:
        - None
"""
def display(boards, connections, calls):
    # For as many area codes in switchboards...
    for code in boards:
        print(f"Switchboard with area code {code}: ") # Display each switchboard
        
        # For as many trunk connections exist for the current switchboard...
        print("\tTrunk lines are: ")
        for connection in connections[code]:
            print(f"\t\tTrunk line connection with {connection}") # Display each trunk connection
        
        # For each phone number in the current switchboard...
        print("\tLocal phone numbers are: ")
        for num in boards[code]:
            # Get the digits at after the area code
            condensed_num = ""
            split_num = split_hyphens(num)
            for split in split_num[1:]:
                condensed_num += split
            
            # If the phone is not in use, that is outputted.
            # Otherwise, It displays itself anf the other number it is connected to
            if not calls[num]:
                print(f"\t\t{condensed_num} is not currently in use")
            else:
                print(f"\t\t{condensed_num} is currently in a call with {calls[num]}")

    return

"""
    Desc:
        - Saves switchboard data dn connections to 'network_data.txt'
    Parameters:
        - boards: Dictionary of switchboards
        - connections: Dictionary of switchboard connections
    Returns:
        - None
"""
def save_network(boards, connections):
    # Saves the data into the network_data.txt file.
    with open("network_data.txt", "w") as data_file:
        data_file.write(str(boards) + "\n")
        data_file.write(str(connections))
    
    return

"""
    Desc:
        - Merges numbers together in if they are next to each other in the data line.
    Parameters:
        - string: The string that the numbers are being extracted from
        - index_add: How much the i_index will be moved by
    Returns:
        - num: The condensed number
        - index_add: An int that increases the index
"""
def merge_num(string, index_add):
    # First number will always bee the 0th index of the given string
    num = string[0]

    # For as large as the string is (minus 1)...
    for i in range(len(string) - 1):
        # If the following character is a number, then it is added to num
        # And index_add goes up by one
        if string[i + 1] in NUMBERS:
            num += string[i + 1]
            index_add += 1
        # Once the next character is not a number, then num and index_add are returned.
        else:
            return [num, index_add]

"""
    Desc:
        - Takes the data out from the network data file and converts it to compatible information
    Parameters:
        - data: The line of data being read
        - board_data:
            - Either the dictionary of switchboards
            - Or the dictionary of switchboard connections
        - board_name: The dict that is currently being appended to (switchboards/switch_connections)
    Returns:
        - None
"""
def transfer_data(data, board_data, board_name):
    # Vars
    i = 0
    j = 0
    bracket_open = False

    # While index_i is less than the length of the data line.
    while i < len(data):
        if j % 2 == 0: # Dict keys
            # If the character being tested in data is a number...
            if verify_num(data[i]):
                # All following/adjacent numbers are merged into a string and i is shifted forward
                merge_info = merge_num(data[i:], 0)
                key = merge_info[0]
                i += merge_info[1]

                # This number becomes an area code/key for board_data
                board_data[key] = ""

                j += 1

        elif j % 2 == 1: # Dict elements
            # If the character being tested in data is a number...
            if verify_num(data[i]):
                # Sets element to ""
                # If the brackets are not open, then element_data is set to an empty list.
                # Afterwards, bracket_open is set to True
                element = ""
                if not bracket_open:
                    element_data = []
                bracket_open = True

                # While the ith data is a number...
                while verify_num(data[i]):
                    element += data[i] #It is added to the element.

                    # If the following character is not a number, then element is appended to element data.
                    if not verify_num(data[i + 1]) and data[i + 1] != "-":
                        if board_name == "switch-data":
                            element_data.append(key + "-" + element)
                        elif board_name == "switch-conn":
                            element_data.append(element)

                    # If the character 2 away from the ith data is a closing bracket, then bracket_open is
                        # set to False
                    # ELement data is also appended to the board_data at the most recent key.
                    if data[i + 2] == "]":
                        bracket_open = False
                        board_data[key] = element_data

                    i += 1

                # If the bracket_open is False, then the j counter goes up
                if not bracket_open:
                    j += 1

            # If the ith data element and following element are opening and closing brackets respectively
                # Then the j counter goes up by one
            elif data[i] == "[" and data[i + 1] == "]":
                j += 1

        i += 1

    # For every area_code in board_data, if it contains an empty element, then it is assigned an empty list.
    for area_code in board_data:
        if board_data[area_code] == "":
            board_data[area_code] = []

    return

"""
    Desc:
        - Loads the phones back into the program.
    Parameters:
        - boards: Dictionary of switchboards
        - calls: Dictionary of phone_calls
    Returns:
        - None
"""
def re_add_phones(boards, calls):
    # Puts each phone number into the phone_calls dictionary with a "" value.
    for area_code in boards:
        for num in boards[area_code]:
            calls[num] = ""

    return

"""
    Desc:
        - Loads the data from the network_data.txt file
        - Retrieves all switch boards, their phone numbers, and their connections.
        - Retrieves all phone_calls
    Parameters:
        - boards: Dictionary of switchboards
        - connections: Dictionary of switchboard connections
        - calls: Dictionary of phone calls
    Returns:
        - None
"""
def load_network(boards, connections, calls):
    # Opens the network_data.txt file in read mode
    with open("network_data.txt", "r") as data_file:
        # Reads the two lines in the file and assigns the first to switch[board]_data
        # And the second to [switchboard]connections_data
        data_lines = data_file.readlines()
        switch_data = data_lines[0]
        connections_data = data_lines[1]
        transfer_data(switch_data, boards, "switch-data") # Converts the data in switch_data
        transfer_data(connections_data, connections, "switch-conn") # Converts the data in connection_data

    re_add_phones(boards, calls)

    return



if __name__ == "__main__":
    # Variables
    switchboards = {}  # Keys: Area Codes | Elements: Phone Numbers
    switch_connections = {}  # Keys: Area Codes | Elements: Connected Area Codes
    phone_calls = {} # Keys: Phone Numbers | Elements: Receiving phone number.
    program_running = True

    # While the program is running:
    print("Enter 'quit' to terminate.")
    while program_running:
        # The user enters a command here.
        # If the command they entered isn't in the list of COMMANDS, then it's invalid.
        command = input("Enter a command: ").split()
        command_main = command[0].lower()
        while command_main not in COMMANDS:
            print("Please enter a valid command.")
            command = input("Enter a command: ").split()
            command_main = command[0].lower()

        # The switch-add command allows the user to enter a new switchboard area code.
        if command_main == "switch-add":
            if len(command) == 2:
                # Allows the user to create a switchboard
                switch_add(switchboards, command[1], switch_connections)
            else:
                print("Invalid command length")

        elif command_main == "switch-connect":
            if len(command) == 3:
                switch_connect(switchboards, switch_connections, command[1], command[2])
            else:
                print("Invalid command length")

        elif command_main == "phone-add":
            if len(command) == 2:
                phone_add(switchboards, command[1], phone_calls)
            else:
                print("Invalid command length")

        elif command_main == "start-call":
            if len(command) == 3:
                if call_valid(switchboards, switch_connections, [command[1], command[2]], phone_calls):
                    start_call([command[1], command[2]], phone_calls)
                else:
                    print("That call cannot be made")
            else:
                print("Invalid command length")

        elif command_main == "end-call":
            if len(command) == 3:
                end_call(command[1], command[2], phone_calls, switchboards)
            else:
                print("Invalid command length")

        elif command_main == "display":
            display(switchboards, switch_connections, phone_calls)

        elif command_main == "network-save":
            print("Saving data.")
            save_network(switchboards, switch_connections)

        elif command_main == "network-load":
            print("Loading network")

            switchboards = {}
            switch_connections = {}
            phone_calls = {}

            load_network(switchboards, switch_connections, phone_calls)

        elif command_main == "quit":
            print("Quitting program")
            program_running = False
        else:
            print("invalid command.")

        print()
