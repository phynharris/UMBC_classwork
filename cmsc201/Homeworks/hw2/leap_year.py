"""
    File: leap_year.py
    Author: Jaylen Jenkins
    Date: 2/12/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Requests the user to input a year. It then takes its mod by 400, then 100, then 4 to determine if it is a
        leap year.
"""

year = int(input("Wanna know if a particular year is a leap year? Enter one here and find out: "))

if year % 400 == 0:
    print("That year is a leap year.")
elif year % 100 == 0:
    print("That year is not a leap year.")
elif year % 4 == 0:
    print("That year is a leap year.")
else:
    print("That year is not a leap year.")
