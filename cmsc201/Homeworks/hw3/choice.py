"""
    File: choice.py
    Author: Jaylen Jenkins
    Date: 2/18/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        This program simulates an n choose k equation. It takes values of n and k from the user and takes the
        factorial of each of them. It also takes the factorial of n - k, resulting in n!/(k! * (n - k)!).
"""

if __name__ == "__main__":
    print("The following prompts are the n and k values for an n choose k equation.")
    n = int(input("What value is n (Total number of elements)? "))
    k = int(input("What value is k (The number of elements to select)? "))
    n_fac = n
    k_fac = k
    nk_fac = n - k

    # Takes the factorial of n. If it's equal to 0, then n_fac equals 1.
    if n != 0:
        for x in range(n - 1):
            n_fac *= (n - x - 1)
    else:
        n_fac = 1

    # Takes the factorial of k. If it's equal to 0, then k_fac equals 1.
    if k != 0:
        for x in range(k - 1):
            k_fac *= (k - x - 1)
    else:
        k_fac = 1

    # Takes the factorial of the difference n and k. If it's equal to 0, then nk_fac equals 1.
    if nk_fac != 0:
        for x in range(n - k - 1):
            nk_fac *= (n - k - x - 1)
    else:
        nk_fac = 1

    # Takes the factorial of n and divides it by the factorial of k multiplied by the factorial of n - k.
    n_choose_k = int(n_fac/(k_fac*nk_fac))
    print(f"{n} choose {k} is {n_choose_k}")
