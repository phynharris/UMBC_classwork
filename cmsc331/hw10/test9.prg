extern _printHex (addr)
extern &stackFramePtr
extern &environmentPtr

_printArray ( A )
  i
begin
  for i:=1 ; i <= ^A ; i:=i+1 do
     print A[i] ;
     print " " ;
  end
  println "" ;
end

_oneTest (n)
  G1[5]
  A[20]
  G2[5]
  B[n]
  G3[5]
  i
begin
  println "Before calling _printArray" ;
  print "_SP : " ;
  _printHex(&stackFramePtr) ;
  println "" ;
  print "_EP : " ;
  _printHex(&environmentPtr) ;
  println "" ;

  G1[1] := 777 ;
  G1[2] := 777 ;
  G1[3] := 777 ;
  G1[4] := 777 ;
  G1[5] := 777 ;

  G2[1] := 999 ;
  G2[2] := 999 ;
  G2[3] := 999 ;
  G2[4] := 999 ;
  G2[5] := 999 ;

  G3[1] := 333 ;
  G3[2] := 333 ;
  G3[3] := 333 ;
  G3[4] := 333 ;
  G3[5] := 333 ;

  A[ 1] := 101 ;
  A[ 2] := 102 ;
  A[ 3] := 103 ;
  A[ 4] := 104 ;
  A[ 5] := 105 ;

  A[ 6] := 106 ;
  A[ 7] := 107 ;
  A[ 8] := 108 ;
  A[ 9] := 109 ;
  A[10] := 110 ;

  A[11] := 111 ;
  A[12] := 112 ;
  A[13] := 113 ;
  A[14] := 114 ;
  A[15] := 115 ;

  A[16] := 116 ;
  A[17] := 117 ;
  A[18] := 118 ;
  A[19] := 119 ;
  A[20] := 120 ;

  print "G1: " ;
  _printArray(G1) ;

  print "A: " ;
  _printArray(A) ;

  print "G2: " ;
  _printArray(G2) ;

  println "After calling _printArray" ;
  print "_SP : " ;
  _printHex(&stackFramePtr) ;
  println "" ;
  print "_EP : " ;
  _printHex(&environmentPtr) ;
  println "" ;

  i := 1 ;
  do until i > ^B ;
     B[i] := 770000 + i ;
     i := i + 1 ;
  loop

  B := A ;

  print "G2: " ;
  _printArray(G2) ;

  print "B: " ;
  _printArray(B) ;

  print "G3: " ;
  _printArray(G3) ;
end


_main()
begin
  println "-------------------------------------" ;
  println "Testing B := A" ;
  println "A[20] B[20]" ;
  println "-------------------------------------" ;
  _oneTest(20) ;
  println "" ;
  println "" ;

  println "-------------------------------------" ;
  println "Testing B := A" ;
  println "A[20] B[13]" ;
  println "-------------------------------------" ;
  _oneTest(13) ;
  println "" ;
  println "" ;

  println "-------------------------------------" ;
  println "Testing B := A" ;
  println "A[20] B[27]" ;
  println "-------------------------------------" ;
  _oneTest(27) ;
  println "" ;
  println "" ;

end
