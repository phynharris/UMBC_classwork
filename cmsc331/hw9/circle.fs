\ draw n x n box of o's

: box ( n -- )      \ n
    dup dup \ n rows cols
    BEGIN \ foreach row
	over \ n rows cols rows
	0 > WHILE \ n rows cols
	    
	    CR .s CR \ uncomment to debug
	    BEGIN \ foreach column
		dup \ n rows cols cols
		CR .s CR
		0 > WHILE \ n rows cols
		    111 emit \ 111 = ASCII o
		    1- \ n rows cols'
	    REPEAT
	    CR .s CR \ uncomment to debug
	    CR drop \ n rows
	    
	    1- \ n rows'
	    over \ n rows' cols
    REPEAT
    drop drop drop \ empty stack
;