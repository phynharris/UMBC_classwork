import HW03_1

main = do
   putStr "\nTesting addcomma:\n"
   putStrLn $ "Add commas to \"abcdef\": "
   putStrLn $ addcomma "abcdef"
   putStrLn $ "Add commas to \"\": "
   putStrLn $ addcomma ""
   putStrLn $ "Add commas to \"x\": "
   putStrLn $ addcomma "x"
   putStrLn $ "Add commas to \"Vampire Weekend\": "
   putStrLn $ addcomma "Vampire Weekend"


