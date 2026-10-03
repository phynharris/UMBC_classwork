( ---- begin iosteam.fs ---- )

( Buffer for user input )
VARIABLE _buffer 80 allot

: readInt ." ? " _buffer 80 accept
  _buffer swap s>number drop
;


: print?  ( n -- )
  if
    ." true "
  else
    ." false "
  endif
;

: print# ( n -- ) 0 .r ; 

: printHex ( n -- ) hex. ;


( ---- end iosteam.fs ---- )
