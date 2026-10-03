"""
    File: twitter_ats.py
    Author: Jaylen Jenkins
    Date: 3/14/2025
    Section: 025
    Email: fp31977@umbc.edu
    Description:
        User must enter a prompt tweet.
        It will keep track of every word with an @ and a #.
        It will print out everyone at-ed and every hashtag.
"""

def twitter_ats(the_tweet):
    tweet_split = the_tweet.split()
    at_list = []
    hash_list = []

    for i in range(len(tweet_split)):
        if tweet_split[i][0] == "@":
            at_stripped = "".join(tweet_split[i].split("@"))
            at_list.append(at_stripped)

        if tweet_split[i][0] == "#":
            hash_stripped = "".join(tweet_split[i].split("#"))
            hash_list.append(hash_stripped)

    return [at_list, hash_list]



if __name__ == "__main__":
    stripped_ats = []
    stripped_hashs = []

    tweet = ""

    while tweet != "quit":
        tweet = input("What are the @s and #s in your tweet? ")

        if tweet != "quit":
            at_hash_list = twitter_ats(tweet)

            for at in at_hash_list[0]:
                stripped_ats.append(at)

            for hashtag in at_hash_list[1]:
                stripped_hashs.append(hashtag)

            print("Users @ed are:", ", ".join(stripped_ats))
            print("Hashtags are:", ", ".join(stripped_hashs))
