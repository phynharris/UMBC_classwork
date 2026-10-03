"""
    File: di.py
    Author: Jaylen Jenkins
    Date: 2/22/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program counts the number of diphthongs in a word. It will also exclude the vowel after a qu.
        Ex. Quite has zero diphthongs, but quiet has one.
"""
if __name__ == "__main__":
    word = input("Please enter a word: ").lower()
    diphthong = 0
    letter = []
    previous_letter_exists = False

    """
    q & u == True/False == False
    q & !u == True/True == True
    !q & u == False/False == False
    !q & !u == False/True == False
    """

    # A for loop that has a range of the length of the given word.
    for i in range(len(word)):
        letter = word[i]

        # If the index is greater than 0, that means word[i] has a letter that comes before it.
        if i > 0:
            previous_letter_exists = True
            previous_letter = word[i - 1]

        # If the index is not equal to the length of the word minus one, then the following will occur:
        if i != len(word) - 1:
            following_letter = word[i + 1]

            #  Checks if letter is a vowel
            if (letter == "a" or letter == "e" or letter == "i" or
                    letter == "o" or letter == "u" or letter == "y"):

                # Checks if the next letter is a vowel. If it is a vowel, then that means there is a diphthong.
                if (following_letter == "a" or following_letter == "e" or following_letter == "i" or
                    following_letter == "o" or following_letter == "u" or following_letter == "y"):
                        diphthong += 1

            # If a previous letter exists, then it checks if the current letter is a "u", and if the one before it
            # is a "q".
                # If that is the case, then it checks if diphthongs is greater than 0. It will subtract one from
                # the number of diphthongs if that is the case.
            if(previous_letter_exists == True):
                if (letter == "u" and previous_letter == "q"):
                    if diphthong > 0:
                        diphthong -= 1


    print("Diphthongs:", diphthong)
    if diphthong == 1:
        print(f"There is {diphthong} diphthong in that word. ")
    else:
        print(f"There are {diphthong} diphthongs in that word. ")
