import Text.Read
import Data.Char
import qualified Data.Map
import ExpTree
import PostOrder


-- ---------------------------------------------------------------

do1line :: (Int, String) -> IO ()

do1line (num,line) = do

   let tytr = (read line) :: TyETree

   putStrLn "===================================================="
   putStr   $ "Line #" ++ (show num) ++ ": "
   putStrLn $ postOrder tytr
   putStr   "\n"


-- ---------------------------------------------------------------
-- Main program does the I/O
--

main = do

   input <- getContents
   mapM_ do1line (zip [1..] (lines input))

