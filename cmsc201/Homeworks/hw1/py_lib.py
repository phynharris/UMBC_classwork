"""
    File: py_lib.oy
    Author: Jaylen Jenkins
    Date: 2/6/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        The following program simulates a Mad Libs. The player will be asked to enter an adjective, two nouns
        and a verb. It will then create fill in the blanks of a story with the entered words.
"""

adjective = input("Please enter an adjective: ")
noun = input("Please enter a noun: ")
event_noun = input("Please enter an event_noun: ")
verb = input("Please enter a verb: ")

print(f"""This is going to be a/an {adjective} semester.  
We are going to learn a lot about {noun}, and probably cause few {event_noun}.  
When you're coding remember to {verb}.""")
