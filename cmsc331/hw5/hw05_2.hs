module Lexer where
-- Jaylen Jenkins (fp31977)

import Text.Regex.PCRE
import Data.Char
import LangTypes
import Token

-- type synonym to get ~= to give us an array of matches captured by ( )

type MatchType1 = Bool 
type MatchType2 = String
type MatchType3 = (String,String,String)
type MatchType4 = (String,String,String,[String])


-- str usually has linefeeds and carriage returns (!!)
-- We have to use \A and \Z instead of ^ and $ in the regex patterns
-- Also, the \ in regex patterns must be escaped in Haskell strings



lexer :: String -> [ Token ]

lexer str 

   -- base case that shouldn't happen
   |  "" <- str
   =  [TkError]


   -- base case reached $$
   |  (_,_,after,[_]) <- ( str =~ "\\A(\\$\\$)" :: MatchType4 )
   =  [TkEOF]


   -- remove leading whitespace. \s is white space in PCRE

   |  (_,_,after,[_]) <- ( str =~ "\\A(\\s+)" :: MatchType4 )

   =  lexer after
   

   -- Look for two-character operators

   |  (_,_,after,[match]) <- ( str =~ "\\A([:][=]|[&][&]|[\\|][\\|])" :: MatchType4 )

   =  TkOp match : lexer after


   -- Look for two-character comparison operators

   |  (_,_,after,[match]) <- ( str =~ "\\A([<][=]|[>][=]|[!][=]|[=][=])" :: MatchType4 )

   =  TkComp match : lexer after


   -- Look for punctuation and delimiters

   |  (_,_,after,[match]) <- ( str =~ "\\A([:;\\\\,\\[\\]\\(\\)])" :: MatchType4 )

   =  TkPunc match : lexer after


   -- Look for arithmetic operators

   |  (_,_,after,[match]) <- ( str =~ "\\A([+*/~\\-])" :: MatchType4 )

   =  TkOp match : lexer after


    -- Look for comparison operators

   |  (_,_,after,[match]) <- ( str =~ "\\A([<>])" :: MatchType4 )

   =  TkComp match : lexer after
   

   -- Look for string literals

   |  (_,_,after,[match]) <- ( str =~ "\\A\"([^\"]*)\"" :: MatchType4 ) 

   =  TkStr match : lexer after


   -- Look for integer numbers. \s is white space in PCRE.

   |  (_,_,after,[match]) <- ( str =~ "\\A([0-9]+|[0-9]+[\\_][1][0])" :: MatchType4 )

   =  TkInt ( read match :: Int ) : lexer after


   -- Everything else is an identifier. \S is non-whitespace in PCRE.

   |  (_,_,after,[match]) <- ( str =~ "\\A(\\S+)" :: MatchType4 ) 

   =  TkId LocalVarId EInt match : lexer after


   -- Deal with errors
   |  otherwise

   =  TkError : lexer (tail str)

