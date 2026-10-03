import Text.Read

-- Simple action that returns a String value in IO context
--
action1 :: IO String
action1 = do

   -- do block can have a sequence of actions
   putStrLn "\nEntering action1 ..."
   putStrLn "... leaving action1\n"

   -- return puts String value in IO context
   return "string from action1"


-- Simple action that returns an Int value in IO context
-- also demonstrates use of let
--
action2 :: Int -> IO Int
action2 n = do
   putStrLn "\nEntering action2 ..."

   -- use let to bind pure values
   -- scope of m is until the end of do block
   --
   let m = 2 * n   

   putStrLn $ "n = " ++ (show n)
   putStrLn "... leaving action2\n"

   -- return puts Int value in IO context
   return m


-- double is a pure function, not an action
--
double :: Int -> Int
double n = n + n
    

-- Next action shows that you can return nothing using ()
-- also demonstrates alternate use of let
--
action3 :: Int -> IO ()
action3 n = do

   -- use "in" with "let" if you want, 
   -- but don't forget the "do"
   -- scope of m is designated by indentation
   --
   let m = double n in do  
      putStrLn "\nEntering action3 ..."
      putStrLn $ "n = " ++ (show n)
      putStrLn $ "m = " ++ (show m)

   -- now outside let block, but still in outer do block

   -- next line would be a syntax error, because m is out of scope
   -- putStrLn $ "m = " ++ (show m)

   putStrLn "... leaving action3\n"

   -- next return is unnecessary but shows syntax to return nothing
   return ()



-- Next action is recursive!
--
action4 :: Int -> IO String

-- can use pattern matching as usual
action4 0 = return "0"

action4 n = do
   let str1 = (show n)
   let m = n -1

   -- recursive call to action4
   str2 <- action4 m

   return (str1 ++ " " ++ str2)


-- actions can get input
action5 :: IO ()
action5 = do
   putStrLn "\nEntering action5 ..."
   putStrLn "Enter a number:"
   str <- getLine
   putStrLn $ "str = " ++ str

   -- Yes, we can have case statements in do blocks
   -- Use readMaybe to turn String into Int, maybe
   --
   case readMaybe str :: Maybe Int of

      -- if readMaybe failed to turn str into an Int value
      --
      Nothing -> putStrLn "That's not a number!"

      -- if readMaybe was succsessful, Int value wrapped in Just
      --
      Just n  -> do
         putStr "number entered is: "   
         print n
         let m = double n
         putStr "double that value is: "
         print m

   putStrLn "... leaving action5\n"
   -- no need to return ()         
   -- return ()


main = do
   -- do block allows sequence of actions

   -- return value from an action must be bound by <-
   str1 <- action1
   putStrLn $ "str1 = " ++ str1
   putStrLn ""

   -- return value from a pure function is bound by "let"
   -- Note: there's no "in" after the "let"
   let t = double 3
   putStrLn $ "t = " ++ (show t)

   -- can use if statements inside do but result must be an action
   if (t `mod` 2 == 1) then
      putStrLn "t is odd"

   -- else part has several actions, so need to start a new do block
   else do
      putStrLn "t is even"
      putStrLn "get another t"
      let t = double 4
      putStrLn $ "t = " ++ (show t)

      -- don't need "do" if only one action
      if (t `mod` 2 == 1) then
         putStrLn "t is odd"
      else
         putStrLn "t is even, again"

   -- Normal scoping rules apply, 
   -- This t is not the t in the else block above
   -- This t is the original t from before the if statements
   putStrLn $ "reprint: t = " ++ (show t)

   -- actions can take parameters, this action returns an Int 
   x <- action2 4
   putStrLn $ "x = " ++ (show x)

   -- can also ignore the return value from an action
   action2 8

   -- actions can return nothing
   action3 5

   -- actions can be recursive!
   putStrLn "Calling recursive action4 ..."
   str2 <- action4 5
   putStrLn $ "str2 = " ++ str2


   -- IO actions can use other IO actions like getLine
   -- (of course, they can! We've been using putStrLn all along.)
   action5
