module PostOrder where

import LangTypes
import ExpTree

postOrder :: TyETree -> String

postOrder (TT tp tr)

    | tp == NADA = "NADA "

    | EError  <-tr  = "EError "

    | tp == EInt, CONST n <- tr = show n ++ " "

    | tp == EBul, CONST n <- tr 
    = case n of
         -1 -> "true "
         0  -> "false "
         _  -> (show n) ++ " "

    | RVALUE nm (LocalVarMode _) <- tr 
    = case tp of
          NADA -> nm ++ "! "
          EBul -> nm ++ "? "
          EInt -> nm ++ " "

    | RVALUE nm GlobalVarMode <- tr 
    = "&" ++ case tp of
          NADA -> nm ++ "! "
          EBul -> nm ++ "? "
          EInt -> nm ++ " "

    | RVALUE nm (LocalArrayItemMode  _ tytr) <- tr 
    =  (postOrder tytr) ++ nm ++
       case tp of
          NADA -> "![] "
          EBul -> "?[] "
          EInt -> "[] "

    | RVALUE nm (GlobalArrayItemMode   tytr) <- tr
    =  (postOrder tytr) ++ "&" ++ nm ++
       case tp of
          NADA -> "![] "
          EBul -> "?[] "
          EInt -> "[] "

    | RVALUE nm _ <- tr = nm ++ "!!!"  -- not implemented

    | LVALUE nm _ <- tr = nm ++ "!!!"  -- no LVALUE in expression

    | PLUS   lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "+ "
    | TIMES  lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "* "
    | MINUS  lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "- "
    | DIVIDE lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "/ "

    | AND    lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "&& "
    | OR     lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "|| "

    | NEG tr' <- tr = (postOrder tr') ++ "~ "

    | ETGt   lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "> "
    | ETGtEq lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ ">= "
    | ETLt   lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "< "
    | ETLtEq lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "<= "
    | ETEq   lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "== "
    | ETNeq  lft rgt <- tr = (postOrder lft) ++ (postOrder rgt) ++ "!= "

    | FUNC nm tytrs <- tr = concat (map postOrder tytrs) ++ "@" ++ nm
    -- | FUNC nm tytrs <- tr = nm
    | otherwise
    
    = "( function calls not implemented! ) "

