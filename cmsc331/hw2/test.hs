piggy2 :: String -> Bool
piggy2 s
    | head s == 'o' = True
        | last (take 2 s) == 'o' = True
	    | otherwise = False

piggy3 :: String -> Bool
piggy3 ('o':_) = True
piggy3 (_:'o':_) = True
piggy3 _ = False