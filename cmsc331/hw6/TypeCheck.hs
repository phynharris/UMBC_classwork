module TypeCheck where

import LangTypes
import ExpTree

type Report = [(String,TyETree)]
typeOK = ([] :: Report)


typeCheck :: TyETree -> Report

typeCheck root@(TT tp tr) 

    | tp == NADA = [("Type is NADA",root)]

    | EError  <-tr  = [("ETree is EError",root)]
    | CONST _ <- tr = typeOK

    | RVALUE nm (LocalArrayItemMode  _ tytr) <- tr = checkIndex nm tytr
    | RVALUE nm (GlobalArrayItemMode   tytr) <- tr = checkIndex nm tytr
    | RVALUE _ _ <- tr = typeOK

    | LVALUE _ _ <- tr = [("No L-values in experssion!",root)]

    | PLUS   lft rgt <- tr = checkArithmeticOp "PLUS"   lft rgt
    | TIMES  lft rgt <- tr = checkArithmeticOp "TIMES"  lft rgt
    | MINUS  lft rgt <- tr = checkArithmeticOp "MINUS"  lft rgt
    | DIVIDE lft rgt <- tr = checkArithmeticOp "DIVIDE" lft rgt

    | AND    lft rgt <- tr = checkLogicOp "AND" lft rgt
    | OR     lft rgt <- tr = checkLogicOp "OR"  lft rgt

    | NEG _ <- tr = typeOK  -- can't make my parser make this error

    | ETGt   lft rgt <- tr = checkIntComparison ">"  lft rgt
    | ETGtEq lft rgt <- tr = checkIntComparison ">=" lft rgt
    | ETLt   lft rgt <- tr = checkIntComparison "<"  lft rgt
    | ETLtEq lft rgt <- tr = checkIntComparison "<=" lft rgt

    | ETEq   lft rgt <- tr = checkAnyComparison "==" root lft rgt
    | ETNeq  lft rgt <- tr = checkAnyComparison "!=" root lft rgt

    | FUNC nm tytrs <- tr = checkParameters nm tytrs

-- -------------------------------------------------------------------

checkIndex :: String -> TyETree -> Report

checkIndex name tytr  

   | TT EInt _ <- tytr 
   = rprt

   | TT EBul _ <- tytr 
   = ("Index for array " ++ name ++ " cannot be EBul" , tytr) : rprt

   | TT NADA _ <- tytr 
   = ("Index for array " ++ name ++ " cannot be NADA" , tytr) : rprt

   where rprt = typeCheck tytr


-- -------------------------------------------------------------------

checkArithmeticOp :: String -> TyETree -> TyETree -> Report

checkArithmeticOp op left right

    | TT EBul _ <- left
    = ("Left subtree of " ++ op ++ " cannot be EBul", left) : rprt

    | TT EBul _ <- right
    = ("Right subtree of " ++ op ++ " cannot be EBul", right) : rprt

    | TT NADA _ <- left
    = ("Left subtree of " ++ op ++ " cannot be NADA", left) : rprt

    | TT NADA _ <- right
    = ("Right subtree of " ++ op ++ " cannot be NADA", right) : rprt

    where rprt = typeCheck left


-- -------------------------------------------------------------------

checkLogicOp :: String -> TyETree -> TyETree -> Report

checkLogicOp op left right

    | TT EInt _ <- left
    = ("Left subtree of " ++ op ++ " cannot be EInt", left) : rprt

    | TT EInt _ <- right
    = ("Right subtree of " ++ op ++ " cannot be EInt", right) : rprt

    | TT NADA _ <- left
    = ("Left subtree of " ++ op ++ " cannot be NADA", left) : rprt

    | TT NADA _ <- right
    = ("Right subtree of " ++ op ++ " cannot be NADA", right) : rprt

    where rprt = typeCheck left


-- -------------------------------------------------------------------

checkIntComparison :: String -> TyETree -> TyETree -> Report

checkIntComparison op left right

    | TT EBul _ <- left
    = ("Left subtree of " ++ op ++ " cannot be EBul", left) : rprt

    | TT EBul _ <- right
    = ("Right subtree of " ++ op ++ " cannot be EBul", right) : rprt

    | TT NADA _ <- left
    = ("Left subtree of " ++ op ++ " cannot be NADA", left) : rprt

    | TT NADA _ <- right
    = ("Right subtree of " ++ op ++ " cannot be NADA", right) : rprt

    where rprt = typeCheck left


-- -------------------------------------------------------------------

checkAnyComparison :: String -> TyETree -> TyETree -> TyETree -> Report

checkAnyComparison op root left right

    | TT NADA _ <- left
    = ("Left subtree of " ++ op ++ " cannot be NADA", left) : rprt

    | TT NADA _ <- right
    = ("Right subtree of " ++ op ++ " cannot be NADA", right) : rprt

    where rprt = typeCheck root

-- -------------------------------------------------------------------

checkParameters :: String -> [TyETree] -> Report 

checkParameters name tytrs = typeOK

