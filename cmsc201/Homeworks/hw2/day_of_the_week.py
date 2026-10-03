"""
    File: day_of_the_week.py
    Author: Jaylen Jenkins
    Date: 2/13/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program asks the user to input a day (1-30), then it will calculate if that day is a Monday, Tuesday,
        Wednesday, etc. based on September 2023.
        Additionally, it will also put the appropriate suffix (st, nd, rd, and th).
"""

print("Wanna know which day of the week goes with each of the 1-30 days of September 2023?"
      "For reference, September 1st is a Friday and SeSeptember 16 is a Saturday.")

day = 0
suffix = "th"

while 0 >= day or day > 30:
    day = int(input("What day (1-30) is it? "))
    day_string = str(day)

if day != 11 and day != 12 and day != 13:
    for letter in day_string:
        if letter == "1":
            suffix = "st"
        elif letter == "2":
            suffix = "nd"
        elif letter == "3":
            suffix = "rd"
        else:
            suffix = "th"

if day % 7 == 1:
    print(f"September {day}{suffix} is a Friday.")
elif day % 7 == 2:
    print(f"September {day}{suffix} is a Saturday.")
elif day % 7 == 3:
    print(f"September {day}{suffix} is a Sunday.")
elif day % 7 == 4:
    print(f"September {day}{suffix} is a Monday.")
elif day % 7 == 5:
    print(f"September {day}{suffix} is a Tuesday.")
elif day % 7 == 6:
    print(f"September {day}{suffix} is a Wednesday.")
elif day % 7 == 0:
    print(f"September {day}{suffix} is a Thursday.")
