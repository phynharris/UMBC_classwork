import HW04_5

main = do
  let str = "abc"
  putStr "the worth of \"" 
  putStr str 
  putStr "\" is "
  print $ worth str

  let str="abcdef"
  putStr "the worth of \"" 
  putStr str 
  putStr "\" is "
  print $ worth str

  let str="xyzzy"
  putStr "the worth of \"" 
  putStr str 
  putStr "\" is "
  print $ worth str

  let str="xyxyq"
  putStr "the worth of \"" 
  putStr str 
  putStr "\" is "
  print $ worth str

  let str="xyxyxyabcdef"
  putStr "the worth of \"" 
  putStr str 
  putStr "\" is "
  print $ worth str
