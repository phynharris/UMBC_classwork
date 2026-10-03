\ draw a n x n triangle of *

: triangle ( n -- )      \ n
    dup dup              \ n rows cols
    BEGIN                \ foreach row
	over             \ n rows cols rows
	0 > WHILE        \ n rows cols

	   \ CR .s CR \ uncomment to debug
	    over         \ Duplicate the second element on the stack
	    -            \ Take the difference of copied element and (new) second element
	    1+           \ Add 1 to their difference — this acts as the new iterator
	    BEGIN            \ foreach column
		dup          \ n rows cols col
		0 > WHILE    \ n rows cols
		    42 emit  \ 42 = ASCII *
		    1-       \ n rows cols'
	    REPEAT
	    \ CR .s CR \ uncomment to debug
	    CR drop \ n rows
	    
	    1-      \ n rows'
	    over    \ n rows' cols
    REPEAT
    drop drop drop  \ empty stack
;
