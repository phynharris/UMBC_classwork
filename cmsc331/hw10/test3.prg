## Euclid's algorithm for greatest common divisor
   implemented with a while loop
## 

extern @mod(m,n)

@gcd (a , b)
   m temp
begin
   while b != 0 do 
      print "a = " ;
      print a ;
      print ", b = " ;
      println b ;

      temp := b ;
      # use FORTH's mod function
      b := @mod(a,b) ;
      a := temp ;
   end 
   return a ;
end


_main () 
  answer
begin
  answer := @gcd(72,30) ;
  print "answer = " ;
  println answer ;
end
