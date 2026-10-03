module SortaRandom where
import Data.Time

-- get "random" value from system clock
--
getMSec :: IO Int
getMSec = do
   now <- getCurrentTime
   -- miliseconds since midnight
   return $ round (1000 * (utctDayTime now))


-- return "random" number between 1 and max 
--
getRandom :: Int -> IO Int
getRandom max = do
   msec <- getMSec
   return ( (msec `mod` max) + 1 )

