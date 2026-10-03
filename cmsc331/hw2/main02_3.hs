
-- CMSC 331 Homework 2 Question #3 Test Program

import HW02_3

main = do
   putStr "\nTesting piggy1:\n" 
   print $ map piggy1 ["","o","no","big","bad","wolf","blows","my","house","down","!"]
   
   putStr "\nTesting piggy2:\n" 
   print $ map piggy2 ["","o","no","big","bad","wolf","blows","my","house","down","!"]
   
   putStr "\nTesting piggy3:\n" 
   print $ map piggy3 ["","o","no","big","bad","wolf","blows","my","house","down","!"]
   
