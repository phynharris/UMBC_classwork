module HW03_1 where
-- Jaylen Jenkins (fp31977)

addcomma :: String -> String
addcomma "" = ""
addcomma (c:[]) = c:[]
addcomma s = (head s:[]) ++ "," ++ addcomma (tail s)