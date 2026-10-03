# File:    scramble.py
# Started: by Dr. Gibson (updated by Kristin McLaughlin)
# Author:  Jaylen Jenkins
# Date:    5/2/2025
# Section: 25
# E-mail:  fp31977@umbc.edu
# Description:
#   This file contains python code that computes all of
#   the possible combinations of a string's characters.

########################################################################
# permute() is a recursive function that scrambles a string
# Input:    currentScramble; the scrambled word so far
#           lettersLeft;     the letters left to scramble
# Output:   None;            prints out each scramble as it's completed
def permute(currentScramble, lettersLeft):

    # BASE CASE: __________
    if len(lettersLeft) == 0:
        # print out the ______ variable to see the result
        print(currentScramble)

    # RECURSIVE CASE:
    else:
        # for each letter still available for scrambling
        for i in range(len(lettersLeft)):
            letter = lettersLeft[i]

            # create a copy of the string without that letter
            # (this code removes the FIRST instance of the letter)
            # (for example: if string was "2010", now it's "210")
            j = 0
            while j < len(lettersLeft):
                if lettersLeft[j] == letter:
                    newLettersLeft = lettersLeft[:j] + lettersLeft[j+1:]
                    # set i past the end of the string to jump out of the loop
                    j = len(lettersLeft)
                j += 1

            # add the letter we removed from letters_left
            # to the current scrambled word, call it new_scramble
            newScramble = currentScramble + letter

            # RECURSIVE CALL: use the new variables for this call
            # permute() takes in currentScramble, lettersLeft
            permute(newScramble, newLettersLeft)

def main():

    print("Welcome to the Scrambler!")
    word = input("Please enter a string to scramble: ")

    # call the recursive function here
    # permute() takes in currentScramble, lettersLeft
    permute("", word)

    print("Thank you for using the Scrambler!\n")

main()



