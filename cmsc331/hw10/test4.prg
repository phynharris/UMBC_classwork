extern @readInt()

_main()
  x
begin
  print "Enter a number" ;
  x := @readInt() ;

  println "" ;
  if x > 33 then
     println "x is bigger than 33" ;
  elsif x > 25 then
     println "x is between 26 and 33" ;
  elsif x > 17 then
     println "x is between 18 and 25" ;
  elsif x > 9 then
     println "x is between 10 and 17" ;
  else
     println "x is less than 10" ;
  end
  
end

