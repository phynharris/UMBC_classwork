module Token where

import LangTypes

data Token 

   -- literal constants
   = TkInt   Int        -- int literal     
   | TkBul   Bool       -- boolean true or false
   | TkStr   String     -- literal string

   -- identifiers
   --    global variables start with &
   --    booleans end with ?
   --    functions start with @
   --    procedures start with _

   | TkId IdKind EType String

   -- more
   | TkKW    String     -- keyword
   | TkOp    String     -- unary or binary operator
   | TkComp  String     -- comparison operator
   | TkPunc  String     -- punctuation 

   -- special cases
   | TkError            -- error found
   | TkEOF              -- end of file

   deriving (Show, Eq, Read)

