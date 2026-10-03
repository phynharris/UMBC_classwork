module HW04_5 where
-- Jaylen Jenkins (fp31977)

worth :: String -> Int
worth s
    | "" <- s = 0
    | str <- s, head str == 'a', head (tail str) == 'b', length str >= 5 && length str <= 9 = 13
    | str <- s, head str == 'x', head (tail str) == 'y' || head (tail str) == 'z' = 5 + worth (tail (tail str))
    | str <- s, s == "q" = 9
    | otherwise = 0