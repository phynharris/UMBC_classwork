-- Jaylen Jenkins
-- FP31977

module Optimizer where

import LangTypes
import ExpTree

-- --------------------------------------------------------
-- Wrapper optimize function
-- Optimizing an expression tree does not change its type

optimize :: TyETree -> TyETree
optimize ( TT typ etree ) = TT typ (opt etree)

-- --------------------------------------------------------
-- Recursive opt function

opt :: ETree -> ETree

-- --------------------------------------------------------
-- Optimizations for NEG
-- --------------------------------------------------------

opt ( NEG (TT EInt lft) )

   | lft' == CONST 0   = CONST 0
   | CONST x <- lft'   = CONST (-x)

   where lft' = opt lft

-- --------------------------------------------------------
-- Optimizations for TIMES
-- --------------------------------------------------------

opt ( TIMES (TT EInt lft) (TT EInt rgt) )

   | lft' == CONST 1    = rgt'
   | rgt' == CONST 1    = lft'
   | lft' == CONST 0    = CONST 0
   | rgt' == CONST 0    = CONST 0
   | CONST x <- lft', CONST y <- rgt'   = CONST (x*y)
   | lft' == CONST (-1) = NEG (TT EInt rgt')
   | rgt' == CONST (-1) = NEG (TT EInt lft')
   | otherwise   = TIMES (TT EInt lft') (TT EInt rgt')

   where lft' = opt lft ; rgt' = opt rgt

-- --------------------------------------------------------
-- Optimizations for PLUS
-- --------------------------------------------------------

opt ( PLUS (TT EInt lft) (TT EInt rgt) )

   | lft' == CONST 0   = rgt'
   | rgt' == CONST 0   = lft'
   | CONST x <- lft', CONST y <- rgt'   = CONST (x+y)
   | otherwise   = PLUS (TT EInt lft') (TT EInt rgt')

   where lft' = opt lft ; rgt' = opt rgt
   
-- --------------------------------------------------------
-- Optimizations for MINUS
-- --------------------------------------------------------

opt ( MINUS (TT EInt lft) (TT EInt rgt) )

   | lft' == rgt'      = NEG (TT EInt rgt')
   | CONST 0 <- lft', CONST x <- rgt' = CONST (0-x)
   | rgt' == CONST 0   = lft'
   | CONST x <- lft', CONST y <- rgt'   = CONST (x-y)
   | otherwise   = MINUS (TT EInt lft') (TT EInt rgt')

   where lft' = opt lft ; rgt' = opt rgt

-- --------------------------------------------------------
-- Optimizations for DIVIDE
-- --------------------------------------------------------

opt ( DIVIDE (TT EInt lft) (TT EInt rgt) )

   | rgt' == CONST 1   = lft'
   | CONST 0 <- lft', CONST (-1) <- rgt'   = CONST 0
   | rgt' == CONST (-1)   = NEG (TT EInt lft')
   | CONST x <- lft', CONST y <- rgt'   = CONST (x `div` y)
   | otherwise   = DIVIDE (TT EInt lft') (TT EInt rgt')

   where lft' = opt lft ; rgt' = opt rgt

-- --------------------------------------------------------
-- Optimizations for AND
-- --------------------------------------------------------

opt ( AND (TT EBul lft) (TT EBul rgt) )

   | lft' == CONST (VBool True)   = rgt'
   | rgt' == CONST (VBool True)   = lft'
   | lft' == CONST (VBool False)  = CONST (VBool False)
   | rgt' == CONST (VBool False ) = CONST (VBool False)
   | otherwise   = AND (TT EBul lft') (TT EBul rgt)

   where lft' = opt lft ; rgt' = opt rgt

-- --------------------------------------------------------
-- Catch all case where no optimizations can be done

opt x = x
