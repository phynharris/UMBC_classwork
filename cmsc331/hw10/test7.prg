extern &stackFramePtr
extern &environmentPtr


_printArray(X)
   i
begin
   for i:=1 ; i <= ^X ; i:=i+1 do
      print X[i];
      print " " ;
   end
   println "" ;
end


# merge A[p..q] and A[q+1..r]
_merge (A,p,q,r) 
   B[r-p+1]
   i j k
begin
   i := p ;    # index in A[p..q]
   j := q+1 ;  # index in A[q+1..r]
   k := 1 ;    # index in B[0..]

   while ( (i <= q) && (j <= r) ) do

      if A[i] <= A[j] then
         B[k] := A[i] ;
         i := i + 1 ;
         k := k + 1 ;
      else
         B[k] := A[j] ;
         j := j + 1 ;
         k := k + 1 ;
      end

   end

   # copy remaining items from A[p..q], if any
   while i <= q do
      B[k] := A[i] ;
      i := i + 1 ;
      k := k + 1 ;
   end

   # copy remaining items from A[q+1..r], if any
   while j <= r do
      B[k] := A[j] ;
      j := j + 1 ;
      k := k + 1 ;
   end

   # copy B[] back to A[]
   i := p ;
   k := 1 ;
   while i <= r do
      A[i] := B[k] ;
      i := i + 1 ;
      k := k + 1 ;
   end 

end  # merge


# MergeSort array A[p..r]
#
_mergeSort(A,p,r)
   q
begin
   # print "MergeSort " ;
   # print p ;
   # print " " ;
   # println r ;

   if r <= p then return ; end

   q := (p+r)/2 ;
   _mergeSort(A,p,q) ;
   _mergeSort(A,q+1,r) ;
   _merge(A,p,q,r) ;
end


_main()
   C[5] D[50] E[5]
begin
   
   C[1] := 1011 ; C[2] := 1012 ; C[3] := 1013 ; C[4] := 1014 ; C[5] := 1015 ;
   E[1] := 2021 ; E[2] := 2022 ; E[3] := 2023 ; E[4] := 2024 ; E[5] := 2025 ; 

   D[1] := 10 ; D[2] := 31 ; D[3] := 23 ; D[4] := 30 ;
   D[5] := 44 ; D[6] := 13 ; D[7] := 37 ; D[8] := 34 ; D[9] := 32 ;
   D[10] := 24 ; D[11] := 28 ; D[12] := 47 ; D[13] := 45 ; D[14] := 4 ;
   D[15] := 6 ; D[16] := 17 ; D[17] := 11 ; D[18] := 29 ; D[19] := 18 ;
   D[20] := 8 ; D[21] := 5 ; D[22] := 26 ; D[23] := 12 ; D[24] := 20 ;
   D[25] := 40 ; D[26] := 42 ; D[27] := 1 ; D[28] := 15 ; D[29] := 16 ;
   D[30] := 14 ; D[31] := 49 ; D[32] := 35 ; D[33] := 46 ; D[34] := 2 ;
   D[35] := 36 ; D[36] := 22 ; D[37] := 7 ; D[38] := 39 ; D[39] := 9 ;
   D[40] := 33 ; D[41] := 50 ; D[42] := 41 ; D[43] := 48 ; D[44] := 43 ;
   D[45] := 19 ; D[46] := 3 ; D[47] := 25 ; D[48] := 27 ; D[49] := 21 ;
   D[50] := 38 ; 

   println "Original arrays: " ;
   print "C: " ; _printArray(C)  ;
   print "D: " ; _printArray(D) ;
   print "E: " ; _printArray(E)  ;
   println "" ;

   println "Before calling _mergeSort:" ;
   print "_SP = " ;
   println &stackFramePtr ;
   print "_EP = " ;
   println &environmentPtr ;
   println "" ;

   _mergeSort(D,1,^D) ;

   println "after calling _mergeSort(): " ;
   print "_SP = " ;
   println &stackFramePtr ;
   print "_EP = " ;
   println &environmentPtr ;
   println "" ;

   print "C: " ; _printArray(C)  ;
   print "D: " ; _printArray(D) ;
   print "E: " ; _printArray(E)  ;
   println "" ;

end
