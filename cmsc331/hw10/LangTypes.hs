module LangTypes where

-- expression types for degree, integer and Boolean 
-- NADA means no type

data EType = NADA | EInt | EBul | EIntPtr | EBulPtr
             deriving (Show, Read, Eq)

toPtr :: EType -> EType
toPtr NADA    = NADA
toPtr EInt    = EIntPtr
toPtr EBul    = EBulPtr
toPtr EIntPtr = EIntPtr
toPtr EBulPtr = EBulPtr

fromPtr :: EType -> EType
fromPtr NADA    = NADA
fromPtr EInt    = EIntPtr
fromPtr EBul    = EBulPtr
fromPtr EIntPtr = EInt
fromPtr EBulPtr = EBul

-- different kinds of local variable, global variable or function name
-- RIEN means error

data IdKind = RIEN 
            | LocalVarId 
            | GlobalVarId 
            | LocalArrayId 
            | GlobalArrayId 
            | FPId           -- function or procedure
            deriving (Show, Read, Eq)

