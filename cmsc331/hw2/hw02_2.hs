module HW02_2 where
-- Jaylen Jenkins (fp31977)

middleHalf :: [xs] -> [xs]
middleHalf xs
    | length(xs) <= 2 = xs
    | length(xs) `mod` 4 == 0 = take (length(xs) `div` 2) (drop (length(xs) `div` 4) xs)
    | otherwise = take (length(xs) `div` 2) (drop (length(xs) `div` 4) xs)