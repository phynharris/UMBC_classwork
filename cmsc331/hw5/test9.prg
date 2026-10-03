##
This is a non-sensical program just to test the lexical analyzer
##

global &stop?   
global &counter
global &Zarray[29]


@getThis ( n, A ) 
   result 
   i j k
begin

   &counter := &counter + 1 ;
   result := 0 ;
   for i := 0 ; i <= 17 ; i := i+1 do
      j := i ;
      do

         j = n - A[i] ;
         k = A[100-j] + 13 ; 

      until j > i ;
         
         result := result +  ( A[j] + A[k] ) / 2 ;

      repeat  
   end 

   return result ;

end


_main() 
begin
   &stop? := false ;
   &counter := 0 ;
   if getThis ( 31, Zarray ) > 4 then
      println "Case 1" ;
   elsif getThis (107, Zarray) < 47 then
      println "Case 2" ;
   else
      println "Case 3" ;
      
   &stop? := true ;   
   return ;
end

