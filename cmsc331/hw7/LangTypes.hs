module LangTypes where

-- expression types for degree, integer and Boolean 
-- NADA means no type

data EType = NADA | EInt | EBul  
             deriving (Show, Read, Eq)


-- different kinds of local variable, global variable or function name
-- RIEN means error

data IdKind = RIEN 
            | LocalVarId 
            | GlobalVarId 
            | LocalArrayId 
            | GlobalArrayId 
            | FPId           -- function or procedure
            deriving (Show, Read, Eq)

