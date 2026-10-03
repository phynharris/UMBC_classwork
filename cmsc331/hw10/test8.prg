extern @readInt()

_main()
  Fib[20]
  i
  n
begin

  Fib[1] := 1 ;
  Fib[2] := 1 ;

  for i := 3 ; i <= 20 ; i := i+1 do
     Fib[i] := Fib[i-2] + Fib[i-1] ;
  end

  print "Enter a number: " ;
  n := @readInt() ;
  println "" ;
  
  print "The Fibonacci number of " ;
  print n ;
  print " is " ;
  print Fib[n] ;
  println "" ; 

end
