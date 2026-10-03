module SynTree where

-- all instances of SynTree type must implement function compile

class SynTree a where
   compile :: a -> String


-- default implementation to compile list of SynTrees

compSTL :: SynTree a => [a] -> String
compSTL [] = ""
compSTL stlist = compile (head stlist) ++ compSTL(tail stlist)
