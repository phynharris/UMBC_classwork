"""
    File: favorite_game.py
    Author: Jaylen Jenkins
    Date: 2/6/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program asks for information about the user's favorite game (title, # of players, and minutes played).
        Afterwards, it changes minutes to hours and prints the necessary information to a string.
"""

fav_game = input("What is your favorite game? ")
num_players = int(input("How many players can play the game? "))
minutes = float(input("How many minutes have you played this game? "))
hours = minutes/60

print(f"Your favorite game is {fav_game}, which has {num_players}, and you have played this game for {hours} hours.")
