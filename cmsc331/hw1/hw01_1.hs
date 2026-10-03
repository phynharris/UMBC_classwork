-- CMSC 331 Sections 03 & 5 Homework 01
-- Name (fp31977): Jaylen Jenkins (fp31977)

-- Average of x1 and x2
--
avg x1 x2 = (x1 + x2) / 2

-- Compute square root of x using Newton's method
-- Use x/4 as first approximation of the square root
--
sqRoot x =
   if x < 0
      then error "You can't take square root of a negative number!"
         else newton x (x/4)

-- Recursively compute square root of x
-- r is the current approximation
--
newton x r =
     -- Case 1: r is too small, recurse with larger r
             if x > r * r + 0.01 then
                newton x (avg r (x/r))

     -- Case 2: r is too large, recurse with smaller r
             else if x < r * r - 0.01 then
                     newton x (avg (x/r) r)

     -- Case 3: r is close enough
             else r

main = do
       putStr "Square root of 19 = "
       print (sqRoot 19)