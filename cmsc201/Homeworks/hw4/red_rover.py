"""
    File: red_rover.py
    Author: Jaylen Jenkins
    Date: 2/27/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This simulates a game with two teams: "Red" and "Blue".
        The player must put the same number of participants on each team. Then, they may choose to start.

        Once the game has started, they must play both sides.
            The player will select a participant to 'make it', and if they do, they stay on their team.
            Else, they join the other team.
                This continues until there is one participant on either team.
"""

if __name__ == "__main__":
    red_team = []
    blue_team = []
    continue_picking = True
    person_exists = False
    turn = 1

    # While loop for putting people onto teams.
    while continue_picking:

        if turn % 2 == 1:

            print("\r")

            # Print statement shows up when there is two or more people on red team.
            if len(red_team) >= 2:
                print("Type 'start' to play the game.")

            # Requests to know who is on the red team and appends them to the list of red_team.
            player_name = input("Who should be added to the red team? ")

            # If the player's name is either start or display, the following occurs.
            while (player_name == "start" or player_name == "display") and continue_picking:
                #Invalid name error
                if player_name == "start" and len(red_team) < 2:
                    player_name = input(f"\nCannot yet start. Must have at least two people on each team.\n"
                                        f"Who should be added to the red team? ")
                #Invalid name error
                elif player_name == "display":
                    player_name = input(f"\nName cannot be display.\n"
                                        f"Who should be added to the red team? ")
                #Starts game
                else:
                    continue_picking = False

            if player_name != "start":
                red_team.append(player_name)

            turn += 1

        else:
            # Requests to know who is on the blue team and appends them to the list of blue_team.
            player_name = input("Who should be added to the blue team? ")

            # If the player's name is either start or display, an invalid name errors occurs.
            while player_name == "start" or player_name == "display":
                if player_name == "start":
                    player_name = input(f"\nCannot yet start. Must have at least two people on each team.\n"
                                        f"Who should be added to the blue team? ")
                elif player_name == "display":
                    player_name = input(f"\nName cannot be display.\n"
                                        f"Who should be added to the blue team? ")

            blue_team.append(player_name)
            turn += 1


    game_over = False
    turn = 1

    # While the game is not over, game runs.
    while not game_over:
        person_exists = False

        if turn % 2 == 1:
            print("\nType 'display' to show current team members.")
            
            # Asks the user which player to send across.
            send_over = input("Who should red team send over? ")
            
            # Displays the team members on Red Team.
            while send_over == "display":
                print("\nRed Team Members:", ", ".join(red_team))
                send_over = input("Who should red team send over? ")

            # If the entered player is not on the red team, then the player must enter a different name.
            while send_over not in red_team:
                if send_over != "display":
                    send_over = input("That player is not on Red Team.\n"
                                      "Who should Red Team send over? ")
                else:
                    print("\nRed Team Members:", ", ".join(red_team))
                    send_over = input("Who should red team send over? ")

            make_it = input(f"Did {send_over} make it? ").lower()
            
            # If the player made it, they stay on their own team.
            if make_it == "yes":
                print(f"{send_over} stays on Red Team.")
            # Else they move to the enemy's team.
            else:
                red_team.remove(send_over)
                blue_team.append(send_over)
                print(f"{send_over} has moved to the Blue Team.")


            turn += 1
        else:
            print("\nType 'display' to show current team members.")
            # Asks the user which player to send across.
            send_over = input("Who should Blue Team send over? ")

            # Displays the team members on Blue Team.
            while send_over == "display":
                print("\nBlue Team Members:", ", ".join(blue_team))
                send_over = input("Who should Blue Team send over? ")

            # If the entered player is not on the blue team, then the player must enter a different name.
            while send_over not in blue_team:
                if send_over != "display":
                    send_over = input("That player is not on Blue Team.\n"
                                      "Who should Blue team send over? ")
                else:
                    print("\nBlue Team Members:", ", ".join(blue_team))
                    send_over = input("Who should Blue Team send over? ")

            make_it = input(f"Did {send_over} make it? ").lower()

            # If the player made it, they stay on their own team.
            if make_it == "yes":
                print(f"{send_over} stays on Blue Team.")
            # Else they move to the enemy's team.
            else:
                blue_team.remove(send_over)
                red_team.append(send_over)
                print(f"{send_over} has moved to the Red Team.")

            turn += 1

        # Determines the loser based on if the length of either team is 1. Prints appropriate response.
        if len(red_team) == 1 or len(blue_team) == 1:
            print("")
            game_over = True

            if len(red_team) == 1:
                print("Red Team has been reduced to one member.\n"
                      "Blue Team is the victor!!!")
            else:
                print("Blue Team has been reduced to one member.\n"
                      "Red Team is the victor!!!")
