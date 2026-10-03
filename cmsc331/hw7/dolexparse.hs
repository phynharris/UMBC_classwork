-- version 1.00001 added line break when successfully parsed

import Text.Read
import Data.Char
import Token
import Lexer
import ExpTree
import PostOrder
import ExpParser


-- 
do1 :: String -> IO ()

do1 line = do

   let tokens = lexer (line ++ "\n$$")
   let (flag,rest,tytr) = parseE tokens

   if not flag then 
      do
      putStrLn "Syntax Error encountered!!"
      putStr "Post order: "
      putStrLn $ postOrder tytr
      putStr "parsed expression tree: "
      putStrLn $ show tytr 
      putStr "\n"
   else
      if rest == [TkEOF] then
         -- Successfully parsed entire input!
         do
         putStr   "Post order: "
         putStrLn $ postOrder tytr
         putStrLn $ show tytr 
         putStr   "\n"

      else
         do
         putStrLn "Trailing tokens not parsed:"
         putStrLn $ show rest
         putStr "parsed expression tree: "
         putStr "Post order: "
         putStrLn $ postOrder tytr
         putStrLn $ show tytr
         putStr "\n"


-- ---------------------------------------------------------------
-- Main program does the I/O
--

main = do

   input <- getContents
   mapM_ do1 (lines input)
