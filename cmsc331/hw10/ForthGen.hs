{-# LANGUAGE TypeSynonymInstances #-}
{-# LANGUAGE FlexibleInstances #-}


module ForthGen where
-- Jaylen Jenkins (fp31977)

import Data.Char
import LangTypes
import SynTree -- syntax tree "base class"
import ExpTree   -- expressions
import CodeTree  -- code



-- ----------------------------------------------------------------
-- TyETree is an instance of SynTree and here's what compile does


instance SynTree TyETree where
   compile (TT NADA _ ) = "( empty ) "
   compile (TT _ etr) = compile etr


-- ----------------------------------------------------------------
-- ETree is also  an instance of SynTree and here's what compile does

instance SynTree ETree where

   compile (CONST n) = (show n) ++ " "

   compile (PLUS   tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "+ "
   compile (MINUS  tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "- "
   compile (TIMES  tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "* "
   compile (DIVIDE tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "/ "

   compile (RVALUE name (LocalVarMode offset)) 
      = "_EP @ " ++ (show offset) ++ " CELLS + @ ( " ++ name ++ " ) "

   compile (RVALUE name (LocalArrayMode offset)) 
      = "_EP @ " ++ (show offset) ++ " CELLS + @ ( " ++ name ++ " ) "

   compile (RVALUE name (LocalArrayItemMode offset tytr)) 
      =   "_EP @ " ++ (show offset) ++ " CELLS + @ ( " ++ name ++ " )\n "
      ++  (compile tytr) ++ "rangeCheck CELLS + @\n"

   compile (RVALUE name GlobalVarMode) = name ++ " @ "

   compile (RVALUE name GlobalArrayMode) = name ++ " "

   compile (RVALUE name (GlobalArrayItemMode tytr)) 
      = name ++ " " ++  (compile tytr) ++ "rangeCheck CELLS + @ "

   compile (ARRSIZE name (LocalArrayMode offset)) 
      =   "_EP @ " ++ (show offset) ++ " CELLS + @ @ ( size of local array " ++ name ++ " )\n "

   compile (ARRSIZE name GlobalArrayMode) 
      =   name ++ " @ ( size of global array " ++ name ++ " )\n "

   compile (FUNC fname tytrlist)
       = (compSTL tytrlist) ++ fname ++ " "

   compile (ETLt   tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "< "
   compile (ETLtEq tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "<= "
   compile (ETEq   tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "= "
   compile (ETNeq  tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "<> "
   compile (ETGtEq tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ ">="
   compile (ETGt   tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "> " 
   compile (AND    tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "AND "
   compile (OR     tytr1 tytr2) = (compile tytr1) ++ (compile tytr2) ++ "OR "

   compile (NEG (TT EBul etr)) = (compile etr) ++ "INVERT "
   compile (NEG (TT EInt etr)) = (compile etr) ++ "NEGATE "


-- ----------------------------------------------------------------

-- CTree is an instance of SynTree and here is what compile does

instance SynTree CTree where

   compile NoCode = "( no op ) "

   compile (GVARDEF _ name) = "( Global ) VARIABLE " ++ name ++ "\n"

   compile (GARRAYDEF _ name size) 
      =   "( Global ) VARIABLE " ++ name ++ " "
      ++  (show (size+1)) ++ " CELLS ALLOT\n"
      --  store array size
      ++  (show size) ++ " " ++ name ++ " !\n"

   compile (LARRAYDEF _ offset tytr) 
      =   "( Local Array ) " 
      --
      --  Compute array size, allocate on PL stack, store size in A[0], store location in A
      --
      --  Example with size = 10, offset = 2
      --     10 _SP @ over      \ set up size and stack location: (                   -- size  addr size   )
      --     1+                 \ bump up storage for count:      ( size  addr  size  -- size  addr size'  )
      --     CELLS - dup        \ compute new stack addr twice:   ( size  addr  size' -- size  addr' addr' )
      --     _SP !              \ allocte                         ( size  addr' addr' -- size  addr'       )
      --     tuck               \ save new stack addr:            ( size  addr'       -- addr' size addr'  )
      --     !                  \ store array size in A[0]        ( addr' size addr'  -- addr'             )
      --     _EP @ 2 CELLS + !  \ store addr' in local var        ( addr'             --                   ) 
      -- 
      ++  compile tytr ++  "_SP @ over 1+ CELLS - dup _SP ! tuck ! \n"
      ++  "_EP @ " ++ (show offset) ++ " CELLS + !\n" 

   compile (FDEF fname clist numParams frameSize) =

     -- add one for storing old EP 
     let frameSize' = frameSize + 1 in 

         -- Note: two wrappers are needed so PL stack 
         -- gets taken down properly when the inner wrapper
         -- exits.

         "\n\\ Allow forward reference for recursion \n" 
         ++ "defer " ++ fname ++ "\n"
         ++ "\\ Define function _" ++ fname ++ " \n" 
         ++ ": _" ++ fname ++ "\n" 
         -- compile function body
         ++ (compSTL clist) 
         ++ ";\n\n"
         ++ "\n( wrapper function __" ++ fname ++ " )\n"
         ++ ": __" ++ fname ++ "\n" 
         --
         ++ "\\ allocate space on the PL stack. Save old EP, set new EP \n"
         --
         -- Example with 5 for frameSize' 
         --    _SP dup @ 5 CELLS -  \ new stack top: ( -- sp addr )
         --    dup rot !            \ update SP:     ( sp addr -- addr )
         --    _EP over over        \ set up:        ( addr -- addr ep addr ep )
         --    @ swap !             \ save old EP:   ( addr ep addr ep -- addr ep )
         --    !                    \ set new EP:    ( addr ep -- )\n"
         --
         ++ "_SP dup @ " ++ (show frameSize') ++ " CELLS - dup rot ! _EP over over @ swap ! !\n"
         --
         ++ "\\ copy Forth parameters to PL stack \n"
         --
         -- Example: call foo(a,b,c) with a = 17, b = 23, c = 31
         -- first parameter's offset is 1
         --    _EP @      \ get ep:       ( 17 23 31              -- 17 23 31 ep          )
         --    CELL+      \ offset of c:  ( 17 23 31 ep           -- 17 23 31 c_ofs       ) 
         --    tuck       \ save offset:  ( 17 23 31 c_ofs        -- 17 23 c_ofs 31 c_ofs )
         --    !          \ store c:      ( 17 23 c_ofs 31 c_ofst -- 17 23 c_ofs          )
         --    CELL+      \ offset of b:  ( 17 23 c_ofs           -- 17 23 b_ofs          ) 
         --    tuck       \ save offset:  ( 17 23 b_ofs           -- 17 b_ofs 23 b_ofs    )
         --    !          \ store b:      ( 17 b_ofs 23 b_ofs     -- 17 b_ofs             )
         --    CELL+      \ offset of a:  ( 17 b_ofs              -- 17 a_ofs             ) 
         --    tuck       \ save offset:  ( 17 a_ofs              -- a_ofs 17 a_ofs       )
         --    !          \ store a:      ( a_ofs 17 a_ofs        -- a_ofs                )
         --    drop       \ clean up:     ( a_ofs                 --                      )
         --
         ++ "_EP @ " ++ (concat [ "CELL+ tuck ! " | i <- [1..numParams] ]) ++ "drop \n\n"
         --
         ++ "\\ call real function \n"
         ++ "_"++fname++"\n\n"
         --
         ++ "\\ deallocate PL stack and restore old EP \n"
         --
         -- Example: _EP@ = 200 _SP@ = 168  old_EP@ = 300  old_SP@ = 240
         -- Note: old_EP stored in location 200
         --       old_SP = 200 + 5*8 = 240
         --
         --    _EP dup @ dup    \ get ep 2 times:   ( -- ep 200 200 )
         --    5 CELLS +        \ compute old_sp:   ( ep 200 200 -- ep 200 240 )
         --    _SP !            \ sp := 240         ( ep 200 240 -- ep 200 ) 
         --    @                \ get old_ep        ( ep 200 -- ep 300 )
         --    swap !           \ ep := old_ep      ( ep 300 -- )
         --
         ++ "_EP dup @ dup " ++ (show frameSize') ++ " CELLS + _SP ! @ swap ! \n"
         --
         ++ ";\n\n"
         --
         ++ "\\ Resolve forward reference \n" 
         ++ "' __" ++ fname ++ " IS " ++ fname ++ "\n\n"

   compile (ASSIGN ( LVALUE name (LocalVarMode offset) ) tytr) 
      =   (compile tytr) 
      ++  "_EP @ " ++ (show offset) ++ " CELLS + ! ( " ++ name ++ " )\n"

   compile (ASSIGN ( LVALUE name (LocalArrayMode offset) ) tytr )
      =   (compile tytr) 
      ++  "_EP @ " ++ (show offset) ++ " CELLS + @ ( " ++ name ++ " )\n "
      ++  "copyArray\n" 

   compile (ASSIGN ( LVALUE name (LocalArrayItemMode offset tytr1) ) tytr2) 
      =   (compile tytr2)
      ++  "_EP @ " ++ (show offset) ++ " CELLS + @ ( " ++ name ++ " )\n "
      ++  (compile tytr1) ++ "rangeCheck CELLS + !\n"

   compile (ASSIGN (LVALUE name GlobalVarMode) tytr) 
      = (compile tytr) ++ name ++ " !\n"

   compile (ASSIGN (LVALUE name GlobalArrayMode) tytr )
      =   (compile tytr) 
      ++  name ++ " copyArray\n" 

   compile (ASSIGN (LVALUE name (GlobalArrayItemMode tytr1)) tytr2) 
      =   (compile tytr2) 
      ++  name ++ " "
      ++  (compile tytr1) ++ "rangeCheck CELLS + !\n"

   compile (PROC pname tytrlst) 
      = (compSTL tytrlst) ++ pname ++ "\n"

   compile (RETURN expr) = "( return ) " ++ (compile expr) ++  "exit\n"

   compile (PRINTEXPR (TT EBul etr)) = (compile etr) ++ "print? "
   compile (PRINTEXPR (TT EInt etr)) = (compile etr) ++ "print# "
   compile (PRINTEXPR (TT EBulPtr etr)) = (compile etr) ++ "printHex "
   compile (PRINTEXPR (TT EIntPtr etr)) = (compile etr) ++ "printHex "
   
   compile (PRINTLNEXPR (TT EBul etr)) = (compile etr) ++ "print? CR "
   compile (PRINTLNEXPR (TT EInt etr)) = (compile etr) ++ "print# CR "
   compile (PRINTLNEXPR (TT EBulPtr etr)) = (compile etr) ++ "printHex CR "
   compile (PRINTLNEXPR (TT EIntPtr etr)) = (compile etr) ++ "printHex CR "

   compile (PRINTSTR label str) = ".\" " ++ str ++ "\" ( " ++ (show label) ++ " )\n" 
   compile (PRINTLNSTR label str) = ".\" " ++ str ++ "\" ( " ++ (show label) ++ " ) CR \n"

   compile (IFTHEN label test if_clist) 
      =   (compile test) ++ "IF ( " ++ (show label) ++ " ) \n" 
      ++  (compSTL if_clist) 
      ++  "\nENDIF ( " ++ (show label) ++ " )\n"

   compile (IFTHENELSE label test if_clist else_clist) 
      =   (compile test) ++ "IF ( " ++ (show label) ++ " ) \n"
      ++  (compSTL if_clist) ++ "ELSE ( " ++ (show label) ++ " ) \n"
      ++  (compSTL else_clist)
      ++ "\nENDIF ( " ++ (show label) ++ " )\n"

   compile (WHILE label test clist) 
      =   "BEGIN ( " ++ (show label) ++ " ) " 
      ++  (compile test) ++ "WHILE ( " ++ (show label) ++ " ) \n" 
      ++  (compSTL clist)
      ++  "\nREPEAT ( " ++ (show label) ++ " )\n"

   compile (DOUNTIL label clist1 test clist2) 
      =   "BEGIN ( " ++ (show label) ++ " ) " 
      ++  (compSTL clist1)
      ++  (compile test) ++ "INVERT WHILE ( " ++ (show label) ++ " ) \n" 
      ++  (compSTL clist2)
      ++  "\nREPEAT ( " ++ (show label) ++ " )\n"

   compile (FOR label initial test increment clist)
      = (compile initial)
      ++ "BEGIN ( " ++ (show label) ++ " ) "
      ++ (compile test) ++ "WHILE ( " ++ (show label) ++ " ) \n"
      ++ (compSTL clist)
      ++ (compile increment)
      ++  "\nREPEAT ( " ++ (show label) ++ " )\n" 

   compile _ = "( Internal Error: umatched CodeTree node! ) "
