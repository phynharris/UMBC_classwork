import Text.Read
import Data.Char
import ExpTree
import PostOrder
import Optimizer

-- 
doopt :: [TyETree] -> IO()

doopt [] = return ()

doopt (tytr:tytrs) = do

   putStr "original tree: "
   putStrLn $ show tytr
   putStr "\n"

   putStr "original postorder: "
   putStrLn $ postOrder tytr
   putStr "\n"

   let opttytr = optimize(tytr)

   putStr "optimized tree: "
   putStrLn $ show opttytr
   putStr "\n"

   putStr "optimized postorder: "
   putStrLn $ postOrder opttytr
   putStr "\n"

   putStrLn "---------------------------------------------------------"

   doopt tytrs

-- Main program does the I/O
--
main = do

   input <- getContents
   let tytrs = ( (read input) :: [TyETree] ) in
      doopt tytrs
   return()
