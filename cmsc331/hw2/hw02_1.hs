module HW02_1 where
-- Jaylen Jenkins (fp31977)

secondLast :: [xs] -> xs
secondLast xs = if length xs >= 2 then last (take ((length xs) - 1) xs) else error "Exception: List must have at least two elements."