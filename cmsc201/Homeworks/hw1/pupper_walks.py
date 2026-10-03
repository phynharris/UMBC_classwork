"""
    File: pupper_walks.py
    Author: Jaylen Jenkins
    Date: 2/6/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Ask the user for the name of their dog, how many times they walk their dog, how far, and how long.
        Afterwards, print out how many hours and miles they've spent walking their dog.
"""

weeks_p_year = 52.0
hours_p_day = 60

#Prompts
dog_name = input("What is your dog's name? ")
walk_p_week = float(input("How many times do you walk your dog per week? "))
distance = float(input("How far do you walk your dog (mi)?: "))
minutes = float(input("How many minutes does it take you to walk one mile? "))

#Math
hours = distance * minutes / hours_p_day
hours_p_week = hours * walk_p_week
hours_p_year = weeks_p_year * hours_p_week
miles_p_week = distance * walk_p_week
miles_p_year = weeks_p_year * miles_p_week

#Output
print(f"You have walked {hours_p_year} hours per year with {dog_name} for {miles_p_year} miles!")
