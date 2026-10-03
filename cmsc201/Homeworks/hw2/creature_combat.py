"""
    File: creature_combat.py
    Author: Jaylen Jenkins
    Date: 2/12/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program prompts the user to enter the names and stats of two monsters.
        Depending on the remaining toughness of the monsters, four scenarios can play out:
        They both win, they both lose, or one or the other wins while the other loses.
"""
# What do the secret words mean? I saw cowboy and catenary here, and I also remember seeing adventurous and
# some other "a" word in another one.

# Prompts the user to enter monsters' names & stats.
monster1 = input("What is the the name of the first monster? ")
monster2 = input("What is the name of the second monster? ")

#Calculates the remaining toughness of either monster
power1 = int(input(f"What is the [power] of {monster1}? "))
max_toughness1 = int(input(f"What is the [toughness] of {monster1}? "))
power2 = int(input(f"What is the [power] of {monster2}? "))
max_toughness2 = int(input(f"What is the [toughness] of {monster2}? "))

#if either monster's toughness is below 0, it is set to 0.
toughness1 = max_toughness1 - power2
if toughness1 < 0:
    toughness1 = 0

toughness2 = max_toughness2 - power1
if toughness2 < 0:
    toughness2 = 0

print()
print("FIGHT!!!")
print(f"{monster1} attacks {monster2} for {power1} damage, and {monster2} retaliates for {power2} damage.")
print(f"{monster1}'s health is taken down from {max_toughness1} to {toughness1}.")
print(f"{monster2}'s health is taken down from {max_toughness2} to {toughness2}.")

#Based on the fight, four scenarios can play out.
if toughness1 <= 0 and toughness2 <= 0:
    print(f"Both {monster1} and {monster2} have been defeated!")
    print("...Let's call it a draw.")

if toughness1 <= 0 and toughness2 > 0:
    print(f"{monster1} has been defeated.")
    print(f"{monster2} is still standing. {monster2} is the victor!")

if toughness1 > 0 and toughness2 <= 0:
    print(f"{monster2} has been defeated.")
    print(f"{monster1} is still standing. {monster1} is the victor!")

if toughness1 > 0 and toughness2 > 0:
    print(f"Both {monster1} and {monster2} have survived.")
    print("Lame.")

