module ExpTree where

import LangTypes

data AddrMode = NYET
              | LocalVarMode Int
              | GlobalVarMode
              | LocalArrayMode Int
              | GlobalArrayMode
              | LocalArrayItemMode Int TyETree
              | GlobalArrayItemMode TyETree
              deriving (Show, Read, Eq)

-- Expression syntax tree for all possible operators
-- EError means error

-- Next time, allow error message with EError and empty tree option
--
-- data ETree
--   = NULL                        -- empty node, not error
--   | EError   String             -- error w/ message 
--   ...

data ETree
   = EError                      -- error
   | CONST    Int                -- number w/ value
   | RVALUE   String AddrMode    -- R-value of var or array + mode
   | LVALUE   String AddrMode    -- L-value of var or array + mode
   | PLUS     TyETree TyETree    -- addition
   | TIMES    TyETree TyETree    -- multiplication 
   | MINUS    TyETree TyETree    -- subtraction
   | DIVIDE   TyETree TyETree    -- division
   | AND      TyETree TyETree    -- logical AND
   | OR       TyETree TyETree    -- logical OR
   | NEG      TyETree            -- logical NOT or unary minus
   | ETGt     TyETree TyETree    -- comparison: >
   | ETGtEq   TyETree TyETree    -- comparison: >=
   | ETLt     TyETree TyETree    -- comparison: <
   | ETLtEq   TyETree TyETree    -- comparison: <=
   | ETEq     TyETree TyETree    -- comparison: == 
   | ETNeq    TyETree TyETree    -- comparison: != 
   | FUNC     String [TyETree]   -- function call w/ parameters
   deriving (Show, Read, Eq)


-- Typed expression syntax trees

data TyETree = TT EType ETree
   deriving (Show, Read, Eq)


-- handy error value for typed ETrees
--
ttError :: TyETree
ttError = TT NADA EError

