"""
    File: distance.py
    Author: Jaylen Jenkins
    Date: 2/6/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program takes user input for coordinate points and uses the Euclidean distance formula tp
        calculate the distance between both points.
"""

x1 = float(input("Enter an x-value for 'point one': "))
y1 = float(input("Enter a y-value for 'point one': "))
x2 = float(input("Enter a second x-value for 'point 2': "))
y2 = float(input("Enter a second y-value for 'point 2': "))

distance = (((x2 - x1) ** 2) + ((y2 - y1) ** 2)) ** 0.5

print(f"The distance between ({x1}, {y1}) and ({x2}, {y2}) is {distance}")