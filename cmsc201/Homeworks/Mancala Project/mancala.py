"""
FILENAME: mancala.py
Author: Jaylen Jenkins
Date: 3/26/2025
Section: 25
E-Mail: fp31977@umbc.edu
Description:
     This program simulates the tabletop game Mancala.
"""

BLOCK_WIDTH = 6
BLOCK_HEIGHT = 5
BLOCK_SEP = "*"
SPACE = ' '


def draw_board(top_cups, bottom_cups, mancala_a, mancala_b):
    """
    draw_board is the function that you should call in order to draw the board.
        top_cups and bottom_cups are lists of strings.  Each string should be length BLOCK_WIDTH and each list should be of length BLOCK_HEIGHT.
        mancala_a and mancala_b should be 2d lists of strings.  Each string should be BLOCK_WIDTH in length, and each list should be 2 * BLOCK_HEIGHT + 1
    :param top_cups: This should be a list of strings that represents cups 1 to 6 (Each list should be at least BLOCK_HEIGHT in length, since each string i\
n the list is a line.)
    :param bottom_cups: This should be a list of strings that represents cups 8 to 13 (Each list should be at least BLOCK_HEIGHT in length, since each stri\
ng in the list is a line.)
    :param mancala_a: This should be a list of 2 * BLOCK_HEIGHT + 1 in length which represents the mancala at position 7.
    :param mancala_b: This should be a list of 2 * BLOCK_HEIGHT + 1 in length which represents the mancala at position 0.
    """
    board = [[SPACE for _ in range((BLOCK_WIDTH + 1) * (len(top_cups) + 2) + 1)] for _ in range(BLOCK_HEIGHT * 2 + 3)]
    for p in range(len(board)):
        board[p][0] = BLOCK_SEP
        board[p][len(board[0]) - 1] = BLOCK_SEP

    for q in range(len(board[0])):
        board[0][q] = BLOCK_SEP
        board[len(board) - 1][q] = BLOCK_SEP

    # draw midline
    for p in range(BLOCK_WIDTH + 1, (BLOCK_WIDTH + 1) * (len(top_cups) + 1) + 1):
        board[BLOCK_HEIGHT + 1][p] = BLOCK_SEP

    for i in range(len(top_cups)):
        for p in range(len(board)):
            board[p][(1 + i) * (1 + BLOCK_WIDTH)] = BLOCK_SEP

    for p in range(len(board)):
        board[p][1 + BLOCK_WIDTH] = BLOCK_SEP
        board[p][len(board[0]) - BLOCK_WIDTH - 2] = BLOCK_SEP

    for i in range(len(top_cups)):
        draw_block(board, i, 0, top_cups[i])
        draw_block(board, i, 1, bottom_cups[i])

    draw_mancala(0, mancala_a, board)
    draw_mancala(1, mancala_b, board)

    print('\n'.join([''.join(board[i]) for i in range(len(board))]))

def draw_mancala(fore_or_aft, mancala_string, the_board):
    """
        Draw_mancala is a helper function for the draw_board function.
    :param fore_or_aft: front or back (0, or 1)
    :param mancala_data: a list of strings of length 2 * BLOCK_HEIGHT + 1 each string of length BLOCK_WIDTH
    :param the_board: a 2d-list of characters which we are creating to print the board.
    """
    #mancala_string.replace('\n', ' ' * BLOCK_WIDTH)
    mancala_string = replace_newlines(mancala_string)
    mancala_data = [mancala_string[k * BLOCK_WIDTH: (k + 1) * BLOCK_WIDTH] for k in range(BLOCK_HEIGHT)]

    if fore_or_aft == 0:
        for i in range(len(mancala_data)):
            data = mancala_data[i][0: BLOCK_WIDTH].rjust(BLOCK_WIDTH)
            for j in range(len(mancala_data[0])):
                the_board[1 + i][1 + j] = data[j]
    else:
        for i in range(len(mancala_data)):
            data = mancala_data[i][0: BLOCK_WIDTH].rjust(BLOCK_WIDTH)
            for j in range(len(mancala_data[0])):
                the_board[1 + i][len(the_board[0]) - BLOCK_WIDTH - 1 + j] = data[j]

def draw_block(the_board, pos_x, pos_y, block_string):
    """
        Draw block is a helper function for the draw_board function.
    :param the_board: the board is the 2d grid of characters we're filling in
    :param pos_x: which cup it is
    :param pos_y: upper or lower
    :param block_data: the list of strings to put into the block.
    """
    #block_string = block_string.replace('\n', ' ' * BLOCK_WIDTH)
    block_string = replace_newlines(block_string)
    block_data = [block_string[k * BLOCK_WIDTH: (k + 1) * BLOCK_WIDTH] for k in range(BLOCK_HEIGHT)]

    for i in range(BLOCK_HEIGHT):
        data = block_data[i][0:BLOCK_WIDTH].rjust(BLOCK_WIDTH)
        for j in range(BLOCK_WIDTH):
            the_board[1 + pos_y * (BLOCK_HEIGHT + 1) + i][1 + (pos_x + 1) * (BLOCK_WIDTH + 1) + j] = data[j]

def replace_newlines(block_string):
    new_string = ''
    for i, c in enumerate(block_string):
        if c == '\n':
            if i % BLOCK_WIDTH == 0:
                new_string += ' ' * BLOCK_WIDTH
            else:
                # Prints something, I don't think I need? Will probably delete later
                #print(BLOCK_WIDTH, i % BLOCK_WIDTH)
                new_string += ' ' * (BLOCK_WIDTH - (len(new_string) % BLOCK_WIDTH))
        else:
            new_string += c
    return new_string

# This function gets the players names.
# It takes in the current index
# It returns the given inputted player's name.
def get_player(index):
    name = input(f"What is player {index + 1}'s name? ")

    return name

# Used for the string stone values in the mancala cups.
# Takes in an integer list of stones
# Returns a string list of stones
def stones_to_strings(stones_list):
    for i in range(len(stones_list)):
        stone_string = str(stones_list[i])
        # If the number of stones is a single digit, then this adds a 0 to the front.
        if len(stone_string) == 1:
            stone_string = "0" + stone_string

        stones_list[i] = stone_string

    return stones_list

# This function makes sure that the player has chosen an appropriate cup to move.
# This accepts the current turn and the int values of the stones.
# It returns either a boolean False or the requested cup int.
def cup_validator(turn, cup_val, cur_player):
    picked = int(input(f"{cur_player}, which cup are you taking from? "))

    # If the value selected is outside of 1~13, then the input is invalid
    if not(0 < picked <= 13):
        return False
    # If the cup they picked has nothing in it, then the input is invalid
    elif cup_val[picked] == 0:
        return False
    # If it is player 2's turn, then they may not pick any of the cups 1~7
    elif turn == 1 and picked in [1, 2, 3, 4, 5, 6, 7]:
        return False
    # If it is player 1's turn, then they may not pick any of the cups 7~13
    elif turn == 0 and picked in [7, 8, 9, 10, 11, 12, 13]:
        return False
    else:
        return picked

# Determines where the stones are placed
# Accepts the cup that the player picked, that is its current placement.
# Returns where the stones are currently "hovering" over.
def determine_placement(cur_placement):

    if cur_placement != 13:
        cur_placement += 1
    elif cur_placement == 13:
        cur_placement = 0

    print(cur_placement)

    return cur_placement

# Moves the stones to the appropriate place
# Accepts the current turn, the selected cup, and the total list of stones in each cup.
# This returns the final placement of the stone occurred.
def move_stones(players_turn, picked_cup, stone_score):
    move_range = stone_score[picked_cup] # The stones will only move as far for as many as there were in the selected cup.
    placement = picked_cup
    stone_score[picked_cup] = 0

    while move_range > 0:
        placement = determine_placement(placement)

        if players_turn == 0:
            if placement != 0:
                stone_score[placement] += 1

        if players_turn == 1:
            if placement != 7:
                stone_score[placement] += 1

        move_range -= 1

    return placement


# This function switches whose turn it is
# It accepts the names of the players, the int list of cups/stones and the string list of cups/stones
# This returns nothing.
def take_turn(player, cups, cup_strings):
    # Variables
    counter = 0
    game_over = False

    while not game_over:
        # Variables
        stone_counter = 0
        p1_stone_counter = 0
        p2_stone_counter = 0

        if counter % 2 == 0:
            cur_player = player[0]
        elif counter % 2 == 1:
            cur_player = player[1]

        print(f"It's {cur_player}'s turn! ")

        # Draws the board at the start of a player's turn.
        draw_board([f" Cup:   01  Stones{cup_strings[1]}  ", f" Cup:   02  Stones{cup_strings[2]}  ", f" Cup:   03  Stones{cup_strings[3]}  ",
                    f" Cup:   04  Stones{cup_strings[4]}  ", f" Cup:   05  Stones{cup_strings[5]}  ", f" Cup:   06  Stones{cup_strings[6]}  "],
                   [f" Cup:   13  Stones{cup_strings[13]}  ", f" Cup:   12  Stones{cup_strings[12]}  ", f" Cup:   11  Stones{cup_strings[11]}  ",
                    f" Cup:   10  Stones{cup_strings[10]}  ", f" Cup:   09  Stones{cup_strings[9]}  ", f" Cup:   08  Stones{cup_strings[8]}  "],
                   f"P2\n{player[1]}\n\nStones{cup_strings[0]}  ", f"P1\n{player[0]}\n\nStones{cup_strings[7]}  ")

        # Checks the validity of the move
        cup_valid = cup_validator(counter % 2, cups, cur_player)
        while not cup_valid:
            print("Error. You cannot pick from that cup.")
            cup_valid = cup_validator(counter % 2, cups, cur_player)

        # Moves the stones and determines where the last stone was placed.
        final_placement = move_stones(counter % 2, cup_valid, cups)

        # Changes the displayed strings to reflect the move.
        cup_strings = stones_to_strings(list(cups))

        # If the player placed their last stone in a mancala, then they get to go again.
        if final_placement != 0 and final_placement != 7:
            counter += 1
        else:
            print("You landed in your mancaal!)

        # These two for-loops check if the player's cups are empty.
        # If all of one player's cups are empty, then the game ends.
        for stone in cups[1:7]:
            if stone == 0:
                p1_stone_counter += 1

        for stone in cups[8:14]:
            if stone == 0:
                p2_stone_counter += 1

        if p1_stone_counter == 6 or p2_stone_counter == 6:
            game_over = True

    # Uses the previous turn to determine the winner and prints the board once more before terminating the program.
    winner = player[counter % 2]
    print(f"The game has ended.\n"
          f"{winner} is the victor.")
    draw_board([f" Cup:   01  Stones{cup_strings[1]}  ", f" Cup:   02  Stones{cup_strings[2]}  ",f" Cup:   03  Stones{cup_strings[3]}  ",
                f" Cup:   04  Stones{cup_strings[4]}  ", f" Cup:   05  Stones{cup_strings[5]}  ", f" Cup:   06  Stones{cup_strings[6]}  "],
               [f" Cup:   13  Stones{cup_strings[13]}  ", f" Cup:   12  Stones{cup_strings[12]}  ", f" Cup:   11  Stones{cup_strings[11]}  ",
                f" Cup:   10  Stones{cup_strings[10]}  ", f" Cup:   09  Stones{cup_strings[9]}  ", f" Cup:   08  Stones{cup_strings[8]}  "],
               f"P2\n{player[1]}\n\nStones{cup_strings[0]}  ", f"P1\n{player[0]}\n\nStones{cup_strings[7]}  ")

# Main run game function where many of the variables are declared and initialized.
# Accepts and returns nothing.
def run_game():
    # Lists
    stones =    [DEFAULT_MANCALA, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES,
                 DEFAULT_MANCALA, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES, DEFAULT_STONES]
    player_name = ["", ""]

    # Variables
    stones_strings = stones_to_strings(list(stones))

    # Gets the names of the players
    for i in range(2):
        player_name[i] = get_player(i)

    # Decides which player's turn it is.
    take_turn(player_name, stones, stones_strings)


if __name__ == "__main__":
    # Global Variables
    DEFAULT_STONES = 4
    DEFAULT_MANCALA = 0

    # Run the game
    run_game()
