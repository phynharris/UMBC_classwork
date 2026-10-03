## Euclid's algorithm for greatest common divisor
   implemented with a while loop
##

@gcd ( a , b )
   # local variables
   temp 
   done?

begin

   if b == 0 then 
      done? := true ;
   else
      done? := false ;
   endif 

   while ~ done? do 
      print "a = " ;
      print a ;
      print ", b = " ;
      println b ;

      temp := b ; # save b

      b := @mod(a,b) ;
      a := temp ;

      if b == 0 then 
         done? := true ;
      else
         done? := false ;
      endif 

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
