( ---- begin preamble.fs ---- )

( Stack for Local Variables )
20000 CONSTANT _StackSize
VARIABLE _TheStack _StackSize CELLS ALLOT

( Initialize Stack & Environment pointers ) 

VARIABLE _SP
VARIABLE _EP
_TheStack _StackSize CELLS + dup _SP ! _EP !


( make aliases for access in PL )

' _SP alias stackFramePtr
' _EP alias environmentPtr


( helper functions )

\ copy array at src address to array at tgt
\ size of arrays at src[0] and tgt[0]

: copyArray ( src tgt -- )
  drop drop
;

: rangeCheck ( addr index -- addr index )
;


( ---- end preamble.fs ---- )

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


\ Allow forward reference for recursion 
defer main
\ Define function _main 
: _main
( Local Array ) 20 _SP @ over 1+ CELLS - dup _SP ! tuck ! 
_EP @ 3 CELLS + !
1 _EP @ 3 CELLS + @ ( Fib )
 1 rangeCheck CELLS + !
1 _EP @ 3 CELLS + @ ( Fib )
 2 rangeCheck CELLS + !
3 _EP @ 2 CELLS + ! ( i )
BEGIN ( 0 ) _EP @ 2 CELLS + @ ( i ) 20 <= WHILE ( 0 ) 
_EP @ 3 CELLS + @ ( Fib )
 _EP @ 2 CELLS + @ ( i ) 2 - rangeCheck CELLS + @
_EP @ 3 CELLS + @ ( Fib )
 _EP @ 2 CELLS + @ ( i ) 1 - rangeCheck CELLS + @
+ _EP @ 3 CELLS + @ ( Fib )
 _EP @ 2 CELLS + @ ( i ) rangeCheck CELLS + !
_EP @ 2 CELLS + @ ( i ) 1 + _EP @ 2 CELLS + ! ( i )

REPEAT ( 0 )
." Enter a number" ( 1 )
readInt _EP @ 1 CELLS + ! ( n )
." " ( 2 ) CR 
." The Fibonacci number of " ( 3 )
_EP @ 1 CELLS + @ ( n ) print# ."  is " ( 4 )
_EP @ 3 CELLS + @ ( Fib )
 _EP @ 1 CELLS + @ ( n ) rangeCheck CELLS + @
print# ." " ( 5 ) CR 
;


( wrapper function __main )
: __main
\ allocate space on the PL stack. Save old EP, set new EP 
_SP dup @ 4 CELLS - dup rot ! _EP over over @ swap ! !
\ copy Forth parameters to PL stack 
_EP @ drop 

\ call real function 
_main

\ deallocate PL stack and restore old EP 
_EP dup @ dup 4 CELLS + _SP ! @ swap ! 
;

\ Resolve forward reference 
' __main IS main


