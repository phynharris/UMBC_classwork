module HW02_3 where
-- Jaylen Jenkins (fp31977)

piggy1 :: String -> Bool
piggy1 s = if s == "" then False else if head s == 'o' || last (take 2 s) == 'o' then True else False

piggy2 :: String -> Bool
piggy2 s
    | s == "" = False
    | head s == 'o' = True
    | last (take 2 s) == 'o' = True
    | otherwise = False

piggy3 :: String -> Bool
piggy3 ('o':_) = True
piggy3 (_:'o':_) = True
piggy3 _ = False