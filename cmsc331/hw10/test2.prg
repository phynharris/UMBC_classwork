
# homebrewed mod function

@modulus (m , n) 
   remainder quotient
begin
   quotient := m / n ;
   remainder := m - n * quotient ;
   return remainder ;
end


# Euclid's algorithm for greatest common divisor 
# implemented recursively

@gcd (a, b) 
   m
begin
   print "a = " ;
   print a ;
   print ", b = " ;
   println b ;
   if b == 0 then 
      return a ;
   else 
      m := @modulus(a, b) ;
      return @gcd(b, m) ;
   end
end


_main () 
  answer
begin
  answer := @gcd(72,30) ;
  println "" ;
  print "answer = " ;
  println answer ;
end
