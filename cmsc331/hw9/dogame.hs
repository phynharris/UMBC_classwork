import PlayAGame
import SortaRandom

-- Jaylen Jenkins (fp31977)

main = do
         putStrLn "Would you like to play a game?"
         putStrLn "Let's play I'm thinking of a number..." 
         n <- getRandom 100
         n <- playAGame n 0
         putStrLn $ "You found the number in " ++ (show n) ++ " guesses"
