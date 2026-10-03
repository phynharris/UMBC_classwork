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
    2dup @ swap @ <> abort" array size mismatch"
    0                
    BEGIN
	over over @ <= 
    WHILE
	    >r >r             
	    r@ over cells + @ 
	    r> over cells + ! 
	    r>                
	    1 +              
    REPEAT
    drop drop drop
;

: rangeCheck ( addr index -- addr index )
    2dup
    swap @
    >=
    over 0 < or
    abort" bad array size"
;


( ---- end preamble.fs ---- )
