x     := 345_8 ;
x     := 0F3_16 ;
&y    := 1abcd_14 ;
X[4]  := 10101010_2 ;
&Y[7] := 0MMM_24 ;

z := 789_8  ;    # digit exceeds base
z := 0FF_15 ;    # digit exceeds base
z := 0FF_38 ;    # base too high
z := 000_1  ;    # base too low
z := FF_16  ;    # Needs leading 0
