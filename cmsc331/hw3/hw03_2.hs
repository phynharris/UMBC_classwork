module HW03_2 where
-- Jaylen Jenkins (fp31977)

rmax :: Ord a => [a] -> [a]
rmax [] = []
rmax (a:[]) = []
rmax a
    | head a == head(tail a) = rmax (tail a)
    | head a:[] < tail a = head a:[] ++ rmax (tail a)
    | head a:[] >= tail a =  head(tail a):[] ++ (rmax (head a:[] ++ tail(tail a)))
    | otherwise = []