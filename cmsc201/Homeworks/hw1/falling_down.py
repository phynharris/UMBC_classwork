"""
    File: falling_down.py
    Author: Jaylen Jenkins
    Date: 2/6/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Requests the user's planet and respective gravitational constant as well as an object's height.
        Afterwards, it calculates how long it will take the object to fall.

"""

location = input("What planet are you on? ")
grav_constant = float(input(f"What is the gravitational constant of {location}? "))
object_height = float(input("How high is the object? "))

seconds_falling = (2 * object_height / grav_constant) ** 0.5

print(f"From a height of {object_height}, it will take {seconds_falling} to hit the ground of {location}.")
