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
  swap              \ tgt src
  over @ over @     \ tgt src #tgt #src
  min               \ tgt src count
  BEGIN
    ?dup 0> WHILE   \ tgt src count
    -rot            \ count tgt src 
    CELL+           \ count tgt src' 
    dup @           \ count tgt src' src[i]
    rot CELL+       \ count src' src[i] tgt'
    tuck            \ count src' tgt' src[i] tgt' 
    !               \ count src' tgt'
    swap rot        \ tgt' src' count
    1-              \ tgt' src' count'
  REPEAT
  drop drop
;

: rangeCheck ( addr index -- addr index )
  dup 1 < abort" array index less than 1" 
  over @ over < abort" array index exceeds size" 
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
defer printArray
\ Define function _printArray 
: _printArray
1 _EP @ 2 CELLS + ! ( i )
BEGIN ( 0 ) _EP @ 2 CELLS + @ ( i ) _EP @ 1 CELLS + @ @ ( size of local array A )
 <= WHILE ( 0 ) 
_EP @ 1 CELLS + @ ( A )
 _EP @ 2 CELLS + @ ( i ) rangeCheck CELLS + @
print# ."  " ( 1 )

_EP @ 2 CELLS + @ ( i ) 1 + _EP @ 2 CELLS + ! ( i )


REPEAT ( 0 )
." " ( 2 ) CR 
;


( wrapper function __printArray )
: __printArray
\ allocate space on the PL stack. Save old EP, set new EP 
_SP dup @ 3 CELLS - dup rot ! _EP over over @ swap ! !
\ copy Forth parameters to PL stack 
_EP @ CELL+ tuck ! drop 

\ call real function 
_printArray

\ deallocate PL stack and restore old EP 
_EP dup @ dup 3 CELLS + _SP ! @ swap ! 
;

\ Resolve forward reference 
' __printArray IS printArray


\ Allow forward reference for recursion 
defer oneTest
\ Define function _oneTest 
: _oneTest
( Local Array ) 5 _SP @ over 1+ CELLS - dup _SP ! tuck ! 
_EP @ 7 CELLS + !
( Local Array ) 20 _SP @ over 1+ CELLS - dup _SP ! tuck ! 
_EP @ 6 CELLS + !
( Local Array ) 5 _SP @ over 1+ CELLS - dup _SP ! tuck ! 
_EP @ 5 CELLS + !
( Local Array ) _EP @ 1 CELLS + @ ( n ) _SP @ over 1+ CELLS - dup _SP ! tuck ! 
_EP @ 4 CELLS + !
( Local Array ) 5 _SP @ over 1+ CELLS - dup _SP ! tuck ! 
_EP @ 3 CELLS + !
." Before calling _printArray" ( 3 ) CR 
." _SP : " ( 4 )
stackFramePtr @ printHex
." " ( 5 ) CR 
." _EP : " ( 6 )
environmentPtr @ printHex
." " ( 7 ) CR 
777 _EP @ 7 CELLS + @ ( G1 )
 1 rangeCheck CELLS + !
777 _EP @ 7 CELLS + @ ( G1 )
 2 rangeCheck CELLS + !
777 _EP @ 7 CELLS + @ ( G1 )
 3 rangeCheck CELLS + !
777 _EP @ 7 CELLS + @ ( G1 )
 4 rangeCheck CELLS + !
777 _EP @ 7 CELLS + @ ( G1 )
 5 rangeCheck CELLS + !
999 _EP @ 5 CELLS + @ ( G2 )
 1 rangeCheck CELLS + !
999 _EP @ 5 CELLS + @ ( G2 )
 2 rangeCheck CELLS + !
999 _EP @ 5 CELLS + @ ( G2 )
 3 rangeCheck CELLS + !
999 _EP @ 5 CELLS + @ ( G2 )
 4 rangeCheck CELLS + !
999 _EP @ 5 CELLS + @ ( G2 )
 5 rangeCheck CELLS + !
333 _EP @ 3 CELLS + @ ( G3 )
 1 rangeCheck CELLS + !
333 _EP @ 3 CELLS + @ ( G3 )
 2 rangeCheck CELLS + !
333 _EP @ 3 CELLS + @ ( G3 )
 3 rangeCheck CELLS + !
333 _EP @ 3 CELLS + @ ( G3 )
 4 rangeCheck CELLS + !
333 _EP @ 3 CELLS + @ ( G3 )
 5 rangeCheck CELLS + !
101 _EP @ 6 CELLS + @ ( A )
 1 rangeCheck CELLS + !
102 _EP @ 6 CELLS + @ ( A )
 2 rangeCheck CELLS + !
103 _EP @ 6 CELLS + @ ( A )
 3 rangeCheck CELLS + !
104 _EP @ 6 CELLS + @ ( A )
 4 rangeCheck CELLS + !
105 _EP @ 6 CELLS + @ ( A )
 5 rangeCheck CELLS + !
106 _EP @ 6 CELLS + @ ( A )
 6 rangeCheck CELLS + !
107 _EP @ 6 CELLS + @ ( A )
 7 rangeCheck CELLS + !
108 _EP @ 6 CELLS + @ ( A )
 8 rangeCheck CELLS + !
109 _EP @ 6 CELLS + @ ( A )
 9 rangeCheck CELLS + !
110 _EP @ 6 CELLS + @ ( A )
 10 rangeCheck CELLS + !
111 _EP @ 6 CELLS + @ ( A )
 11 rangeCheck CELLS + !
112 _EP @ 6 CELLS + @ ( A )
 12 rangeCheck CELLS + !
113 _EP @ 6 CELLS + @ ( A )
 13 rangeCheck CELLS + !
114 _EP @ 6 CELLS + @ ( A )
 14 rangeCheck CELLS + !
115 _EP @ 6 CELLS + @ ( A )
 15 rangeCheck CELLS + !
116 _EP @ 6 CELLS + @ ( A )
 16 rangeCheck CELLS + !
117 _EP @ 6 CELLS + @ ( A )
 17 rangeCheck CELLS + !
118 _EP @ 6 CELLS + @ ( A )
 18 rangeCheck CELLS + !
119 _EP @ 6 CELLS + @ ( A )
 19 rangeCheck CELLS + !
120 _EP @ 6 CELLS + @ ( A )
 20 rangeCheck CELLS + !
." G1: " ( 8 )
_EP @ 7 CELLS + @ ( G1 ) printArray
." A: " ( 9 )
_EP @ 6 CELLS + @ ( A ) printArray
." G2: " ( 10 )
_EP @ 5 CELLS + @ ( G2 ) printArray
." After calling _printArray" ( 11 ) CR 
." _SP : " ( 12 )
stackFramePtr @ printHex
." " ( 13 ) CR 
." _EP : " ( 14 )
environmentPtr @ printHex
." " ( 15 ) CR 
1 _EP @ 2 CELLS + ! ( i )
BEGIN ( 16 ) _EP @ 2 CELLS + @ ( i ) _EP @ 4 CELLS + @ @ ( size of local array B )
 > INVERT WHILE ( 16 ) 
770000 _EP @ 2 CELLS + @ ( i ) + _EP @ 4 CELLS + @ ( B )
 _EP @ 2 CELLS + @ ( i ) rangeCheck CELLS + !
_EP @ 2 CELLS + @ ( i ) 1 + _EP @ 2 CELLS + ! ( i )

REPEAT ( 16 )
_EP @ 6 CELLS + @ ( A ) _EP @ 4 CELLS + @ ( B )
 copyArray
." G2: " ( 17 )
_EP @ 5 CELLS + @ ( G2 ) printArray
." B: " ( 18 )
_EP @ 4 CELLS + @ ( B ) printArray
." G3: " ( 19 )
_EP @ 3 CELLS + @ ( G3 ) printArray
;


( wrapper function __oneTest )
: __oneTest
\ allocate space on the PL stack. Save old EP, set new EP 
_SP dup @ 8 CELLS - dup rot ! _EP over over @ swap ! !
\ copy Forth parameters to PL stack 
_EP @ CELL+ tuck ! drop 

\ call real function 
_oneTest

\ deallocate PL stack and restore old EP 
_EP dup @ dup 8 CELLS + _SP ! @ swap ! 
;

\ Resolve forward reference 
' __oneTest IS oneTest


\ Allow forward reference for recursion 
defer main
\ Define function _main 
: _main
." -------------------------------------" ( 20 ) CR 
." Testing B := A" ( 21 ) CR 
." A[20] B[20]" ( 22 ) CR 
." -------------------------------------" ( 23 ) CR 
20 oneTest
." " ( 24 ) CR 
." " ( 25 ) CR 
." -------------------------------------" ( 26 ) CR 
." Testing B := A" ( 27 ) CR 
." A[20] B[13]" ( 28 ) CR 
." -------------------------------------" ( 29 ) CR 
13 oneTest
." " ( 30 ) CR 
." " ( 31 ) CR 
." -------------------------------------" ( 32 ) CR 
." Testing B := A" ( 33 ) CR 
." A[20] B[27]" ( 34 ) CR 
." -------------------------------------" ( 35 ) CR 
27 oneTest
." " ( 36 ) CR 
." " ( 37 ) CR 
;


( wrapper function __main )
: __main
\ allocate space on the PL stack. Save old EP, set new EP 
_SP dup @ 1 CELLS - dup rot ! _EP over over @ swap ! !
\ copy Forth parameters to PL stack 
_EP @ drop 

\ call real function 
_main

\ deallocate PL stack and restore old EP 
_EP dup @ dup 1 CELLS + _SP ! @ swap ! 
;

\ Resolve forward reference 
' __main IS main


