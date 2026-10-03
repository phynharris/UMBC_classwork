import HW03_2 

main = do
   print $ rmax [3,9,2,8,7,1,9,9,6]
   print $ rmax ([]::[Int])
   print $ rmax [1001,9,4,13,2]
   print $ rmax [1001,9,4002,13,4002]
   print $ rmax [1001]
   print $ rmax ["Fido","Ginger","Rover","Rover"]
