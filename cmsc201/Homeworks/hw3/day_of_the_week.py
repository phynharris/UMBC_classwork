"""
    File: day_of_the_week.py
    Author: Jaylen Jenkins
    Date: 2/22/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Identical to the previous day_of_the_week assignment, however, this program makes use of a list
        to determine which day of the week it is. Far more efficient than if-statements.
            The program takes the day of the month and (based on September 2023), gives back the day of the week.
"""

if __name__ == "__main__":

    # If September 16 is a Saturday, that means %2 = Saturday. Therefore, I shall make element 2 Saturday.
    day_otw = ["Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"]
    suffix = "th"

    sept_day = int(input("Enter a day (1-30) for September 2023: "))

    if sept_day <= 0 or sept_day > 30:
        print("Invalid Day.")
    else:
        day_mod = sept_day % 7
        day_string = str(sept_day)

        # If the day is not 11, 12, or 13, then the appropriate suffix is given to those that need it.
        if sept_day != 11 and sept_day != 12 and sept_day != 13:
            for letter in day_string:
                if letter == "1":
                    suffix = "st"
                elif letter == "2":
                    suffix = "nd"
                elif letter == "3":
                    suffix = "rd"
                else:
                    suffix = "th"

        print(f"September {sept_day}{suffix}, 2023, is a {day_otw[day_mod]}.")
