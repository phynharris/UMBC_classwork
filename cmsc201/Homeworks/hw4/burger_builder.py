"""
    File: FILENAME.py
    Author: Jaylen Jenkins
    Date: 2/27/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program lets the user create a burger.
        They must start with the bottom bun, and may add as many toppings as they like.
        Once they input top bun, it displays the type of burger they have and each unique ingredient.
"""

if __name__ == "__main__":
    burger_list = []
    ingredients_list = []
    single_ingredients_list = []
    is_cheese_burger = False
    ingredient_match = False
    burger_counter = 0
    counter = 0

    # This segment requests the user's first ingredient. It must be the bottom bun.
    ingredient = (input("What is the first ingredient for your burger? ")).lower()
    if ingredient == "bun":
        ingredient = "bottom bun"

    while ingredient != "bottom bun":
        print("You need to start with the bottom bun, silly. ")
        ingredient = (input("What is the first ingredient for your burger? ")).lower()
        if ingredient == "bun":
            ingredient = "bottom bun"

    # Bottom Bun is appended
    burger_list.append(ingredient)

    # Loop will execute until user enters 'top bun'.
    # They will continue adding ingredients to their burger, until the condition is met.
    while ingredient != "top bun":
        ingredient = (input("What are you adding next? ")).lower()
        if ingredient == "bun":
            ingredient = "top bun"

        burger_list.append(ingredient)

    for ingredient in burger_list:
        # Checks if there is cheese in the burger.
        if ingredient == "cheese":
            is_cheese_burger = True

        # Checks if there is 'burger' in the burger and counts how many times 'burger' appears.
        if ingredient == "burger":
            burger_counter += 1

    # If the burger has cheese, it is a cheeseburger.
    if is_cheese_burger:
        burger = "cheeseburger"
    else:
        burger = "hamburger"

    # Creates a new 'ingredients_list' that excludes meat, cheese, and the buns.
    for ingredient in burger_list:
        if (ingredient != "burger" and ingredient != "top bun"
                and ingredient != "cheese" and ingredient != "bottom bun"):
            ingredients_list.append(ingredient)

    # This code creates a new list that puts one of each condiment/topping into the new toppings list.
    for ingredient_num1 in range(len(ingredients_list)):
        ingredient = ingredients_list[ingredient_num1]
        # Automatically appends the first ingredient.
        if ingredient_num1 == 0:
            single_ingredients_list.append(ingredients_list[ingredient_num1])
        else:
            # Compares each subsequent ingredient to every ingredient inside of 'single_ingredients_list'
            ingredient_match = False
            for ingredient_num2 in range(ingredient_num1):
                if ingredients_list[ingredient_num2] != ingredient and ingredient_match == False:
                    ingredient_match = False
                elif ingredients_list[ingredient_num2] == ingredient:
                    ingredient_match = True
            
            # Ingredient is only appended to the list if it is not already in the list.
            if ingredient_match == False:
                single_ingredients_list.append(ingredients_list[ingredient_num1])

    # Checks if there are condiments/toppings on the burger and prints the appropriate statement.
    if len(single_ingredients_list) > 0:
        ingredients_string = ", ".join(single_ingredients_list)
        print(f"You have a {burger_counter}-{burger} with {ingredients_string}. ")
    else:
        print(f"You have a {burger_counter}-{burger} with no condiments. ")
