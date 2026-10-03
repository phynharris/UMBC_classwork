"""
    File: uno.py
    Author: Jaylen Jenkins
    Date: 4/20/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program simulates a simplified version of the card game Uno.
"""
import random

# Default Globals
COLORS = ['Red', 'Green', 'Blue', 'Yellow']
CARD_COLOR = 'color'
CARD_NUMBER = 'number'
CARD_SPECIAL = 'special'
COLOR_SPECIALS = ['Skip', 'DrawTwo']
WILD_SPECIALS = ['Wild', 'WildDrawFour']

# My Globals
NUMBERS = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
STARTING_HAND = 7


"""
    Part of starter code. Creates the deck.
"""
def create_deck():
    deck = [
        {CARD_COLOR: the_color,
         CARD_NUMBER: i % 10,
         CARD_SPECIAL: ''
         }
        for i in range(20)
        for the_color in COLORS
    ]
    for special in COLOR_SPECIALS:
        for the_color in COLORS:
            special_card = {
                CARD_COLOR: the_color,
                CARD_NUMBER: -1,
                CARD_SPECIAL: special
            }
            deck.append(dict(special_card))
            deck.append(dict(special_card))
    for special in WILD_SPECIALS:
        special_card = {
            CARD_COLOR: '',
            CARD_NUMBER: -1,
            CARD_SPECIAL: special
        }
        for i in range(4):
            deck.append(dict(special_card))

    return deck

"""
    Desc:
        - Converts a card into something that's easy to read.
    Accepts:
        - card: The card being simplified.
    Returns:
        - simplified_card: An easy-to-read-version the card. 
"""
def simplify(card):
    # Lists
    simplified_card = ""

    # Whether or not the current card has a color is checked first.
    # If it does, it is added to the simplified_card string.
    if card["color"] != "":
        simplified_card += card["color"]
        # Then, it checks if it has a number other than -1.
        # If it does, then that number is tacked onto the simplified_card string too.
        if card["number"] != -1:
            simplified_card += str(card["number"])
        # If it does not have a number, then it tacks on the card's "special" instead.
        else:
            simplified_card += card["special"]
    # If the card doesn't have a color, then it is converted to a string w/o anything extra.
    else:
        simplified_card += card["special"]
    return simplified_card

"""
    Desc:
        - Deals the cards out to the players.
    Accepts:
        - deck: The list of the deck of cards.
        - p_hand: The current hand being added to.
        - card: The card being removed.
    Returns:
        - Nothing
"""
def first_deal(deck, p_hand, card):
    # Appends the first card in the deck to the respective player's hand and then removes it from the deck.
    p_hand.append(card)
    deck.remove(card)

"""
    Desc:
        - Sets ups the deck and deals the cards.
    Accepts:
        - hands: The list of the players' hands.
        - the_deck: The draw pile/deck, a list.
    Returns: 
        - Nothing
"""
def game_setup(hands, the_deck):
    # Shuffles the deck.
    random.shuffle(the_deck)
    
    # Vars
    p1_hand = hands[0]
    p2_hand = hands[1]

    # Gives each player 7 cards.
    for i in range(STARTING_HAND):
        first_deal(the_deck, p1_hand, the_deck[0])
        first_deal(the_deck, p2_hand, the_deck[0])

"""
    Desc:
        - Determines the index of the action the user played.
    Accepts:
        - action: The action the user chose, if it wasn't draw.
        - hand: The simplified version of the players cards.
    Returns:
        - i: The location of the action in their hand.
"""
def determine_index(action, hand):
    # Locates where the action is in their hand
    for i in range(len(hand)):
        if action == hand[i]:
            return i

"""
    Desc:
        - Determines the card that the user played by comparing their simple_hand's index to their complex_hand's index.
    Accepts:
        - action: The card they are playing.
        - hand: The simplified version of their hand.
        - complex_hand: The complex version of their hand.
    Return:
        - action: action is returned in a complex form.
"""
def determine_action(action, hand, complex_hand):
    # Determines where the action is in their hand
    index = determine_index(action, hand)

    # Compares the action's index to the respective place in the complex_hand
    action = complex_hand[index]

    return action

"""
    Desc:
       - Removes the played card from their hand
       - If they played a Wild or WildDrawFour, then they get to change the color.
    Accepts:
        - action: A dict containing the action the player did.
        - complex_hand: The user's hand made up of dicts.
    Returns:
        - action: The action the user did.
"""
def play_card(action, complex_hand, player):
    # Removes the action from their hand
    complex_hand.remove(action)

    if action["special"][:4] == "Wild":
        # Allows the user to change the color if they play a wild type card.
        # Must be RYGB
        print(f"\n{player}, what are you changing the color to? ")
        action["color"] = input("What color are you changing it to? ").lower()
        while action["color"] not in ["red", "blue", "green", "yellow"]:
            print("Error. That is not a valid color.")
            action["color"] = input("What color are you changing it to? ").lower()

        # Converts the color they picked into title case.
        if action["color"] == "red":
                action["color"] = "Red"
        if action["color"] == "blue":
                action["color"] = "Blue"
        if action["color"] == "yellow":
                action["color"] = "Yellow"
        if action["color"] == "green":
                action["color"] = "Green"

    return action

"""
    Desc:
        - If the opponent is forced to draw cards, that is done here.
    Accepts:
        - top_card: The top card on the draw pile
        - player: The player forced to draw the cards
        - index: The ith card they need to draw
    Returns:
        - Nothing
"""
def draw_x_cards(top_card, player, hand, index):
    # Vars
    drawn_cards = []

    # For as large as the index is [2 or 4], the opponent will draw that many.
    for i in range(index):
        hand.append(top_card[0])
        drawn_cards.append(simplify(top_card[0]))
        del top_card[0]
    print(f"Oh nein! You've been forced to draw cards, {player}.")
    print(f"You've drawn {", ".join(drawn_cards)}.")

"""
    Desc:
        - When a ["special"] card is played, this function acts out the effects.
    Accepts:
        - draw: {list} The draw pile.
        - action: {dict} The action the user did.
        - player: The other player.
        - hand: {list} The other player's hand.
        - turn: The current turn meter.
"""
def play_special(draw, action, player, hand, turn):
    # Skip cards reduce the turn meter by 1.
    if action == "Skip":
        print(f"{player}, your turn has been skipped! ")
        return turn - 1
    # DrawTwos reduce the turn meter by one and add two cards to the opponents hand.
    elif action == "DrawTwo":
        index = 2
        draw_x_cards(draw, player, hand, index)
        return turn - 1
    # WildDrawFours reduce the turn meter by one and add four cards to the opponents hand.
    # Their color-change effect is played elsewhere.
    elif action == "WildDrawFour":
        index = 4
        draw_x_cards(draw, player, hand, index)
        return turn - 1

    return turn

"""
    Desc:
        - When the player chooses to play a card, the below runs.
    Accepts:
        - action: The card being played/action being performed.
        - discard: The most recently discarded card.
        - empty_dis: A boolean for if the discard pile is empty or not. 
        - draw: The list of cards in the draw pile
        - player: The player whose turn it currently is.
        - other: The player whose turn it isn't
        - other_hand: The other player's [complex] list of cards.
        - turn: The turn count.
        - complex_hand: The complex version of the player's hand
    Returns:
        - action: The card being played/action being performed.
        - discard: The card that was most recently discarded.
        - turn: The turn count.
"""
def playing_card(action, discard, empty_dis, draw, player, other, other_hand, turn, complex_hand):
    # If the player plays a special card and it's color or types matches or it's a wild, it is played.
    # This will also play if the card is special and the discard pile is empty.
    if (action["special"] and (((action["special"] == discard["special"] or action["color"] == discard["color"])
                                or action["special"][:4] == "Wild") or empty_dis)):
        # Plays the effect of the special card (DrawTwo, DrawFour, and Skip)
        # Turn takes the effect of the skip action.
        turn = play_special(draw, action["special"], other, other_hand, turn)

        # Sets discard to the card they played.
        # Performs the Wild's color-change effect.
        discard = play_card(action, complex_hand, player)

    # If the card is not special, then it will compare the played card's number and color to that of the discard.
    # If there is a match, it is played.
    # Additionally, if there is nothing in the discard pile, then the card is played.
    elif action["color"] == discard["color"] or action["number"] == discard["number"] or empty_dis:
        discard = play_card(action, complex_hand, player)

    # Else the card is not playable.
    else:
        print("You cannot play that card. ")
        action = ""

    return [action, discard, turn]

"""
    Desc:
        - The main portion of the game that has the player take their turn.
        - They may either play a card they have or draw a new card.
    Accepts:
        - player: The player whose turn it currently is.
        - hand: The simplified version of the player's hand
        - complex_hand: The complex version of the player's hand
        - discard: The most recently discarded card.
        - draw: The list of cards in the draw pile
        - other: The player whose turn it isn't
        - other_hand: The other player's [complex] list of cards.
        - turn: The turn count.
    Returns:
        - discard: The card that was most recently discarded.
        - turn: The turn counter.
"""
def take_turn(player, hand, complex_hand, discard, draw, other, other_hand, turn):
    # Intro
    print(f"\n{player}, it's your turn! ")

    # Vars & Print Statements
    action = ""
    empty_dis = True

    # Determines if the discard pile is empty.
    if discard["number"] != -2:
        empty_dis = False
        simple_discard = simplify(discard)
        print("This is the top discarded card:", simple_discard)

    print("These are your cards:", ", ".join(hand))

    # From here, the user will have to select an action to perform.
    # If their action is invalid, they must try something else.
    while not action:
        action = input("What are you doing? ")

        # If the user chooses to draw a card, then the zeroth card in the draw list is given to the player.
        if action.lower() == "draw":
            drawn_card = draw[0]
            complex_hand.append(drawn_card)
            print(f"You drew a {simplify(drawn_card)}")
            del draw[0]

            # Gives the player the option to play the card they drew.
            play_draw = input("Type 'pass' to pass playing this card. ")

            # If the card cannot be played, then nothing will happen.
            if play_draw.lower() != "pass":
                action = drawn_card
                results = playing_card(action, discard, empty_dis, draw, player, other, other_hand, turn, complex_hand)
                discard = results[1]
                turn = results[2]

            action = "Drawn"

        # If the action is in their hand, then it is played.
        elif action in hand:
            # Gets the complex version of the card they choose to play.
            action = determine_action(action, hand, complex_hand)

            # Does the action and gets the results from that action.
            results = playing_card(action, discard, empty_dis, draw, player, other, other_hand, turn, complex_hand)
            action = results[0]
            discard = results[1]
            turn = results[2]

        # If the user enters a card they don't have or nonsense, then they are told to re-enter an action.
        else:
            print("That is an invalid play. ")
            action = ""

    return [discard, turn]

"""
    Desc:
        - Main function for running the game.
    Accepts:
        - p1: Player 1's name.
        - p2: Player 2's name.
    Returns:
        - Nothing
"""
def run_game(players):
    # Lists
    hands = [[],[]]
    draw_pile = create_deck()
    discard = {"color": "", "number": -2, "special": ""}

    # Variables
    turn = 0

    # Shuffles the deck and deals the players their cards.
    game_setup(hands, draw_pile)

    # While neither player 1's hand, player 2's hand, nor the draw_pile's hand are empty, the game runs.
    while hands[0] and hands[1] and draw_pile:
        # Variables of the current player, their hand, the other player, and their hand.
        player = players[turn % 2]
        other_player = players[(turn + 1) % 2]
        hand = hands[turn % 2]
        other_hand = hands[(turn + 1) % 2]

        # Converts the current player's hand into something that is easy to read.
        hand_simple = [""] * len(hand)
        for i in range(len(hand)):
            hand_simple[i] = simplify(hand[i])

        # Function that allows a player to perform an action.
        outcome = take_turn(player, hand_simple, hand, discard, draw_pile, other_player, other_hand, turn)
        discard = outcome[0]
        turn = outcome[1]
        
        turn += 1

    # Determines game end.
    # If the current player's hand is empty, then they win.
    # If the draw pile is empty, then it is a tie.
    if not hand:
        print(f"Congratulations, {player}, you've won!")
    elif not draw_pile:
        print(f"{", ".join(players)}, you have tied.")


"""
    Desc:
        - The main function of the game that gathers the seed and player names.
"""
if __name__ == '__main__':
    # Gets the seed from the player.
    the_seed = input('What seed do you want to use for the game? ')
    random.seed(the_seed)

    # Gets player names.
    player_one = input("Player 1, what is your name? ")
    player_two = input("Player 2, what is your name? ")

    # Runs the game
    run_game([player_one, player_two])
