module PlayAGame where

-- Jaylen Jenkins (fp31977)

import Text.Read


playAGame :: Int -> Int -> IO Int
playAGame target tries = do
    putStrLn "Enter a number between 0 and 100 (inclusive):"
    str <- getLine
    case readMaybe str :: Maybe Int of

        Nothing -> do
            putStrLn "That is not a number!"
            playAGame target tries

        Just n -> do
            if n < 0 || n > 100 then do
                putStrLn "Pick a number *between* 0 and 100 (inclusive)"
                playAGame target tries
            else if n == target then do
                let m = tries + 1
                putStrLn "You guessed the number correctly"
                return m
            else if n < target then do
                let m = tries + 1
                putStrLn "You should guess higher."
                playAGame target m
            else do
                let m = tries + 1
                putStrLn "You should guess lower."
                playAGame target m