"""
    File: gandalf.py
    Author: Jaylen Jenkins
    Date: 2/12/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        A questionairre that asks the most important question: which LOTR character are you?
        This program uses a lot of if and elif statements to decide who you are.
"""

race = input("Are you human, elf, maiar, hobbit, or dwarf? ")
if race.lower() == "human":
    king = input("Are you the King of Gondor? ")
    if king.lower() == "yes":
        print("You are Aragorn son of Arathorn.")
    else:
        thief = input("Did you try to steal the ring from Frodo? ")
        if thief.lower == "yes":
            print("You are Boromir.")
        else:
            print("You are Theoden... probably.")
elif race.lower() == "elf":
    matrix = input("Were you in the matrix? ")
    if matrix.lower() == "yes":
        print("You are Elrond.")
    else:
        print("You are Legolas.")
elif race.lower() == "maiar":
    good = input("Are you good? ")
    if good.lower() == "yes":
        print("You are Gandalf.")
    else:
        ring = input("Did you forge the One Ring? ")
        if ring.lower() == "yes":
            print("You are Sauron.")
        else:
            print("You are Saruman.")
elif race.lower() == "hobbit":
    carrier = input("Did you carry the One Ring? ")
    if carrier.lower() == "yes":
        print("You are Frodo Baggins.")
    else:
        gardener = input("Are you a gardener? ")
        if gardener.lower() == "yes":
            print("You are Samwise.")
        else:
            print("You are Merry or Pippin.")
elif race.lower() == "dwarf":
        print("You are Gimli son of Gloin.")
else:
    print("You're just some orc - a nobody.")
