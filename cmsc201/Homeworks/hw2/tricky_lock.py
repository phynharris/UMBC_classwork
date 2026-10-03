"""
    File: tricky_lock.py
    Author: Jaylen Jenkins
    Date: 2/12/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program gives the player a little bit of a puzzle. They must open a combination lock held by two conditions.
        1) You pick two numbers between 1 and 25 that equal 36.
        2) You must have two switches in the 'up' position.
        There are four outcomes that can be summed up with false/false, true/false, false/true, and true/true.
"""

#minimal variable initialization
num1 = 0
num2 = 0

print("""In front of you is a lock.
To open this lock, you must satisfy two requirements.
1) You pick two numbers between 1 and 25 that equal 36.
2) You must have two switches in the 'up' position.
""")

# Prompts the player to enter a value 1-25 for the first and second numbers on the lock.
while 0 >= num1 or num1 > 25:
    num1 = int(input("What is the first number you enter into the lock? "))

while 0 >= num2 or num2 > 25:
    num2 = int(input("What is the second number you enter into the lock? "))

# Prompts the user to flip three switches.
switch1 = input("Switch the first switch up or down? ")
switch2 = input("Switch the second switch up or down? ")
switch3 = input("Switch the third switch up or down? ")


# The following if/else statements determine if the conditions have been met.
if num1 + num2 == 36:
    condition1 = True
else:
    condition1 = False

if switch1 == "up":
    switch1 = True
else:
    switch1 = False

if switch2 == "up":
    switch2 = True
else:
    switch2 = False

if switch3 == "up":
    switch3 = True
else:
    switch3 = False

if switch1 + switch2 + switch3 == 2:
    condition2 = True
else:
    condition2 = False

# Outputs
if condition1 + condition2 == 0:
    print("The lock does not budge.")

if condition1 + condition2 == 1:
    print("The lock jiggles. It's close to being open, but not quite.")

if condition1 + condition2 == 2:
    print("You got the lock open! Good job!")

