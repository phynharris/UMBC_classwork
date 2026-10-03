if __name__ == "__main__":
    ice_cream_flavors = ["vanilla", "strawberry", "chocolate"]
    toppings = ["carame", "marshmallow", "gummy bears"]

    print("\n")
    for j in range(len(toppings)):
        if j == 0 or j == 2:
            for i in range(len(ice_cream_flavors)):
                print(f"{ice_cream_flavors[j]} is really good with {toppings[i]}")
            else:
                print("strawberry is fine on its own")
                j += 1
