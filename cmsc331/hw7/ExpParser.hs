-- Jaylen Jenkins (FP31977)

module ExpParser where

import LangTypes
import Token
import ExpTree

{-

A recursive descent parser for the grammar:

  E -> T Ttl

  Ttl -> + T Ttl 
       | - T Ttl 
       | "&&" T Ttl 
       | "||" T Ttl
       | epsilon

  T -> F Ftl

  Ftl -> * F Ftl 
       | / F Ftl 
       | <    F
       | "<=" F 
       | >    F 
       | ">=" F 
       | "==" F 
       | "!=" F 
       | epsilon

  F -> id 
     | val 
     | ~ F 
     | ( E ) 
     | arr [ E ]
     | fn EL 
   
-}


-- ---------------------------------------------------------------------------
-- constant to represent empty TyETree

ttNull :: TyETree
ttNull = TT NADA (CONST 0)


-- ---------------------------------------------------------------------------

-- wrapper function that calls parseE 
-- and checks if E can generate the entire string

parse :: [Token] -> (Bool, TyETree)

parse tks 

   |  (True, tks, tytr) <- parseE tks 
   =  ( [TkEOF] == tks,  tytr )

   |  otherwise
   =  ( False, ttError )


-- ---------------------------------------------------------------------------

--  E -> T Ttl

parseE :: [Token] -> (Bool, [Token], TyETree)

parseE [] 
   = ( False, [TkEOF], ttError )

parseE tks
   |  (True,tks1,tytr1) <- parseT tks 
   ,  (True,tks2,tytr2) <- parseTtl tks1 tytr1
   =  (True,tks2,tytr2)

   | otherwise
   =  ( False, tks, ttError )


-- ---------------------------------------------------------------------------

makeExpr :: Token -> TyETree -> TyETree -> (Bool, TyETree)

makeExpr tkop left right 
   | TkOp "+"  <- tkop  = (True,  TT EInt (PLUS  left right))
   | TkOp "-"  <- tkop  = (True,  TT EInt (MINUS left right))
   | TkOp "||" <- tkop  = (True,  TT EBul (OR    left right))
   | TkOp "&&" <- tkop  = (True,  TT EBul (AND   left right))
   | otherwise          = (False, ttNull)
   

-- ---------------------------------------------------------------------------

--  Ttl -> + T Ttl | - T Ttl | "||" T Ttl | "&&" T Ttl | epsilon

parseTtl :: [Token] -> TyETree -> (Bool, [Token], TyETree)

parseTtl [] left = (True,[],left)

parseTtl (tkop:tks) left
   | ( True, tks1, right ) <- parseT tks 
   , ( True, tks2, tail  ) <- parseTtl tks1 right
   , ( True, tytr) <- makeExpr tkop left tail 
   = ( True, tks2, tytr)

   | otherwise
   = (True, tkop:tks, left)


-- ---------------------------------------------------------------------------

--  T -> F Ftl

parseT :: [Token] -> (Bool, [Token], TyETree)

parseT tks
   |  (True,tks1,tytr1) <- parseF tks
   =  parseFtl tks1 tytr1

   | otherwise
   =  (False, tks, ttError)


-- ---------------------------------------------------------------------------

makeTerm :: Token -> TyETree -> TyETree -> (Bool, TyETree)

makeTerm tkop left right 
   | TkOp "*"  <- tkop  = (True,  TT EInt (TIMES  left right))
   | TkOp "/"  <- tkop  = (True,  TT EInt (DIVIDE left right))
   | otherwise = (False, ttNull)


-- ---------------------------------------------------------------------------

makeComp :: Token -> TyETree -> TyETree -> (Bool, TyETree)

makeComp tkcmp left right 
   | TkComp "<"  <- tkcmp = (True,  TT EBul (ETLt   left right))
   | TkComp "<=" <- tkcmp = (True,  TT EBul (ETLtEq left right))
   | TkComp "==" <- tkcmp = (True,  TT EBul (ETEq   left right))
   | TkComp "!=" <- tkcmp = (True,  TT EBul (ETNeq  left right))
   | TkComp ">=" <- tkcmp = (True,  TT EBul (ETGtEq left right))
   | TkComp ">"  <- tkcmp = (True,  TT EBul (ETGt   left right))
   | otherwise = (False, ttNull)


-- ---------------------------------------------------------------------------

--  Ftl -> * F Ftl | / F Ftl | comp F | epsilon

parseFtl :: [Token] -> TyETree -> (Bool, [Token], TyETree)


parseFtl [] left = (True,[],left)


parseFtl (tkop@(TkOp _):tks) left
   | ( True, tks1, right ) <- parseF tks 
   , ( True, tks2, tail  ) <- parseFtl tks1 right
   , ( True, tytr ) <- makeTerm tkop left tail
   = ( True, tks2, tytr)

   | otherwise
   = ( True, tkop:tks, left )


parseFtl (tkcmp@(TkComp _):tks) left
   | ( True, tks1, right ) <- parseF tks
   , ( True, tytr ) <- makeComp tkcmp left right
   = ( True, tks1, tytr)

   | otherwise
   = ( True, tkcmp:tks, left )

parseFtl tks left = ( True, tks, left )


-- ---------------------------------------------------------------------------

--  F -> id | val | ~ F | ( E ) | fid EL | arr [ E ]

parseF :: [Token] -> (Bool, [Token], TyETree)

parseF [] = (False,[],ttError)

parseF (tk:tks)
   | TkId LocalVarId tp nm  <- tk 
   = (True, tks, TT tp (RVALUE nm (LocalVarMode 0)))

   | TkId GlobalVarId tp nm  <- tk 
   = (True, tks, TT tp (RVALUE nm GlobalVarMode))
   
   | TkInt num  <- tk 
   = (True, tks, TT EInt (CONST num))

   | TkBul True <- tk 
   = (True, tks, TT EBul (CONST (0-1)))

   | TkBul False <- tk
   = (True, tks, TT EBul (CONST 0))

   | TkOp "~" <- tk
   , (True, tks1, tytr1@(TT tp1 tr1)) <- parseF tks
   = (True, tks1, TT tp1 (NEG tytr1))
   
   | TkPunc "(" <- tk
   , (True,tks1,tytr1) <- parseE tks
   , (TkPunc ")" : tks2) <- tks1
   = (True, tks2, tytr1)

   | TkPunc "[" <- tk
   , (True,tks1,tytr1) <- parseE tks
   , (TkPunc "]" : tks2) <- tks1
   = (True, tks2, tytr1)

   | otherwise
   = (False, tk:tks, ttError)


-- ---------------------------------------------------------------------------
