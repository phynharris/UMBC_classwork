module CodeTree where

import LangTypes
import ExpTree

-- Syntax tree for code for each statement type

data CTree = 

   -- empty code, not necessarily an error
   --
   NoCode                                     

   -- Global variable declaration with type and name
   --
   | GVARDEF EType String                       
   

   -- Global array declaration with type, name and size
   --
   | GARRAYDEF EType String Int 


   -- Local array declaration with type, offset and size 
   --
   | LARRAYDEF EType Int TyETree 


   -- Function definiton
   --
   | FDEF String [CTree] Int Int       

   -- Assignment statement 
   -- ETree should be (LVALUE name mode)
   -- AddressingMode could be local/global and variable/array item.
   --
   | ASSIGN ETree TyETree  

   -- Procedure call with name of the procedure and  list of parameters.
   --
   | PROC String [TyETree]   

   -- Return a typed expression, not used in HW06.
   --
   | RETURN TyETree 

   -- Print typed expression with and without newline.
   --
   | PRINTLNEXPR TyETree
   | PRINTEXPR TyETree

   -- Print literal string with and without newline.
   -- The Int field is a unique identifier for labels, not used in HW06.
   --
   | PRINTLNSTR Int String
   | PRINTSTR Int String 

   -- if statement without an else part
   -- The Int field is a unique identifier for labels, not used in HW06.
   -- The TyETree field is the Boolean condition.
   -- The [CTree] field is the body of the then part.
   --
   | IFTHEN Int TyETree [CTree]

   -- if statement with an else part analogous to above
   -- The second [CTree] field is the body of the else part.
   --
   | IFTHENELSE Int TyETree [CTree] [CTree]

   -- while loop
   -- The Int field is a unique identifier for labels, not used in HW06.
   -- The TyETree field is the Boolean condition.
   -- The [CTree] field is the body of the loop.
   --
   | WHILE Int TyETree [CTree]                

   -- do-until loop
   -- The Int field is a unique identifier for labels, not used in HW06.
   -- First [CTree] field is body of loop between do and until
   -- The TyETree field is the Boolean condition.
   -- Second [CTree] field is body of loop between until and loop
   --
   | DOUNTIL Int [CTree] TyETree [CTree]                

   -- for loop
   -- for loop
   -- The Int field is a unique identifier for labels, not used in HW06.
   -- The first CTree field is the initial assignment.
   -- The TyETree field is the Boolean condition.
   -- The second CTree field is the "increment" assignment.
   -- The [CTree] field is the body of the loop.
   --
   | FOR Int CTree TyETree CTree [CTree]        -- for loop

   -- Error + message
   | CError String

   deriving (Show, Read, Eq)
