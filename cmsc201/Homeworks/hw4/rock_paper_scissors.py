"""
    File: rock_paper_scissors.py
    Author: Jaylen Jenkins
    Date: 2/27/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Uses Random to allow the player to play rock, paper, scissors against the computer.
"""

import sys
from random import choice, seed

if len(sys.argv) >= 2:
    seed(sys.argv[1])

if __name__ == "__main__":
    weapon = ''
    
    #Game continues until player tells it to end.
    while weapon != "stop":

        the_choice = choice(["rock", "paper", "scissors"])
    
    
        # User enters rock, paper, scissors, or stop. They must pick one of those four.
        weapon = input("Pick rock, paper or scissors, or pick stop to end: ").lower()
        while not (weapon == "scissors" or weapon == "paper" or weapon == "rock" or weapon == "stop"):
            weapon = input("\nError. Invalid input.\n"
                           "Pick rock, paper or scissors, or pick stop to end: ").lower()
    
    
        # Outcomes
        if weapon == "rock" and the_choice == "rock":
            print(f"Computer throws {the_choice}.")
            print("Rock VS Rock. Draw\n")

        elif weapon == "rock" and the_choice == "paper":
            print(f"Computer throws {the_choice}.")
            print("Paper beats rock. You lose.\n")

        elif weapon == "rock" and the_choice == "scissors":
            print(f"Computer throws {the_choice}.")
            print("Rock beats scissors. You win!\n")

        elif weapon == "paper" and the_choice == "paper":
            print(f"Computer throws {the_choice}.")
            print("Paper VS Paper. Draw\n")

        elif weapon == "paper" and the_choice == "rock":
            print(f"Computer throws {the_choice}.")
            print("Paper beats rock. You win!\n")

        elif weapon == "paper" and the_choice == "scissors":
            print(f"Computer throws {the_choice}.")
            print("Scissors beats paper. You lose.\n")

        elif weapon == "scissors" and the_choice == "scissors":
            print(f"Computer throws {the_choice}.")
            print("Scissors VS Scissors. Draw\n")

        elif weapon == "scissors" and the_choice == "rock":
            print(f"Computer throws {the_choice}.")
            print("Rock beats scissors. You lose.\n")

        elif weapon == "scissors" and the_choice == "paper":
            print(f"Computer throws {the_choice}.")
            print("Scissors beats paper. You win!\n")
