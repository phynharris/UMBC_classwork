"""
    File: minor_key.py
    Author: Jaylen Jenkins
    Date: 3/12/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        Takes a note from the user and returns it as it should look if it is valid.
"""

# Converts flat notes into flat notes.
def helper(initial_note):

    note_split = initial_note.split()

    # The entered note should be either 1 or two elements.
    while 0 >= len(note_split) >= 3:
        new_note = input(f"\nError. Invalid note.\n"
                         f"Enter one of the following notes ({" ".join(MUSICAL_NOTES)}): ").upper()

    if len(note_split) == 2:

        # If the second element in the note_split is not FLAT, then it will ask the user to enter a new note.
        # Then it will put the new note back through the helper function.
        if note_split[1] != "FLAT":
            new_note = input(f"\nError. Invalid note.\n"
                             f"Enter one of the following notes ({" ".join(MUSICAL_NOTES)}): ").upper()
            initial_note = helper(new_note)
            note_split = initial_note

        # Converts "FLAT" to the flat symbol.
        if len(note_split) == 2:
            if note_split[1] == "FLAT":
                note_split[1] = "\u266d"

    merged_note = "".join(note_split)

    return merged_note


def helper_2(test_note):

    # Receives the note from helper.
    # If that note is not in MUSICAL_NOTES, then they are taken back to helper.
    while test_note not in MUSICAL_NOTES:
        new_note = input(f"\nError. Invalid note.\n"
                         f"Enter one of the following notes ({" ".join(MUSICAL_NOTES)}): ").upper()

        test_note = helper(new_note)

    return test_note


if __name__ == "__main__":
    program = ""

    while program != "quit":
        MUSICAL_NOTES = ["C", "D", "D\u266d", "E", "E\u266d", "F", "G\u266d", "G", "A\u266d", "A", "B\u266d", "B"]

        print()

        # Gets the note from the user and splits it.
        note = input(f"Enter one of the following notes ({", ".join(MUSICAL_NOTES)}): ").upper()

        # Takes the given note, and if it is flat, enters the flat symbol beside the note.
        corrected_flat = helper(note)

        # Checks if the note is valid
        corrected_note = helper_2(corrected_flat)

        print(corrected_note)

        # Asks if the user wants to continue the program.
        program = input("\nEnter 'quit' to quit program. ").lower()
