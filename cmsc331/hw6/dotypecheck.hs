import Text.Read
import Data.Char
import qualified Data.Map
import ExpTree
import TypeCheck
import PostOrder


-- ---------------------------------------------------------------

print1Error :: (String,TyETree) -> IO ()

print1Error (msg,tytr) = do
   putStrLn "   -------------------------------------------------"
   putStr   "   *** Error: "
   putStrLn msg
   putStr   "   "
   -- print    tytr
   -- putStr   "\n"
   putStrLn $ postOrder tytr

-- ---------------------------------------------------------------

do1line :: (Int, String) -> IO ()

do1line (num,line) = do

   let tytr = (read line) :: TyETree
   let errorList = typeCheck tytr

   putStrLn "===================================================="
   putStr   $ "Line #" ++ (show num) ++ ": "
   putStrLn $ postOrder tytr
   putStrLn "===================================================="

   if null errorList then
      putStrLn "   No type errors found."
   else 
      mapM_ print1Error errorList

   putStr   "\n\n"


-- ---------------------------------------------------------------
-- Main program does the I/O
--

main = do

   input <- getContents
   mapM_ do1line (zip [1..] (lines input))

