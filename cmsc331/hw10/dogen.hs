import Text.Read
import Data.Char
import SynTree
import CodeTree
import ForthGen

-- Main program does the I/O
--
main = do

   input <- getContents
   let clist = (read input) :: [CTree]
      in do

      -- putStrLn "include preamble.fs"
      preamble <- readFile "preamble.fs"
      putStrLn preamble

      -- putStrLn "( Stack for Local Variables )"
      -- putStrLn "VARIABLE _EP"
      -- putStrLn "VARIABLE _LV 10000 CELLS ALLOT"
      -- putStrLn "10000 _EP !\n\n"
      -- putStrLn "\n"

      -- putStrLn "include iostream.fs"
      iofuncs <- readFile "iostream.fs"
      putStrLn iofuncs

      putStrLn $ compSTL clist
      -- putStrLn "\n\nmain bye"
