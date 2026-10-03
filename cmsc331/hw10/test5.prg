_triangle1 ( n ) 
  i j 
begin
   for i := 1 ; i <= n ; i := i+1 do
      for j := 1 ; j <= i ; j := j+1 do
         print "*" ;
      end 
      println "" ;
   end 
end


_triangle2 ( n ) 
  i j 
begin
   i := 1 ;
   while (i <=n) do
      for j := 1 ; j <= i ; j := j+1 do
         print "*" ;
      end 
      println "" ;
   i := i + 1 ;
   end 
end


_triangle3 ( n ) 
  i j 
begin
   for i := 1 ; i <= n ; i := i+1 do
      j := 1 ;
      while j <= i do
         print "*" ;
         j := j + 1 ;
      end 
      println "" ;
   end 
end


_main () 
begin
   println "Calling triangle1() with nested for loops:" ;
   _triangle1(8) ;
   _triangle1(11) ;

   println "Calling triangle2() with for loop in while loop:" ;
   _triangle2(7) ;
   _triangle2(5) ;

   println "Calling triangle3() with while loop in for loop:" ;
   _triangle3(3) ;
   _triangle3(6) ;
end
