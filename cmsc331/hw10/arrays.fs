CREATE X 9999 ,
CREATE A 7 , 101 , 102 , 103 , 104 , 105 , 106 , 107 ,
CREATE B 7 , 201 , 202 , 203 , 204 , 205 , 206 , 207 ,
CREATE C 5 , 301 , 302 , 303 , 304 , 305 ,
CREATE Y 8888 ,

: dumpA
  A
  ." size = " dup @ . CR
  ." A[1] = " cell+ dup @ . CR
  ." A[2] = " cell+ dup @ . CR
  ." A[3] = " cell+ dup @ . CR
  ." A[4] = " cell+ dup @ . CR
  ." A[5] = " cell+ dup @ . CR
  ." A[6] = " cell+ dup @ . CR
  ." A[7] = " cell+ dup @ . CR
  drop
;

: dumpB
  B
  ." size = " dup @ . CR
  ." B[1] = " cell+ dup @ . CR
  ." B[2] = " cell+ dup @ . CR
  ." B[3] = " cell+ dup @ . CR
  ." B[4] = " cell+ dup @ . CR
  ." B[5] = " cell+ dup @ . CR
  ." B[6] = " cell+ dup @ . CR
  ." B[7] = " cell+ dup @ . CR
  drop
; 

: dumpC
  C
  ." size = " dup @ . CR
  ." C[1] = " cell+ dup @ . CR
  ." C[2] = " cell+ dup @ . CR
  ." C[3] = " cell+ dup @ . CR
  ." C[4] = " cell+ dup @ . CR
  ." C[5] = " cell+ dup @ . CR
  drop
;
