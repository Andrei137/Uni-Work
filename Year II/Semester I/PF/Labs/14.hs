import Data.List

-- 1
data Point = Pt [Int]
    deriving Show

data Arb = Empty | Node Int Arb Arb
    deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

instance ToFromArb Point where
    toArb (Pt l) = toArb' $ sort l
        where
        toArb' [] = Empty
        toArb' (h:t) = Node h Empty (toArb' t)

    fromArb a = Pt (fromArb' a)
        where
        fromArb' Empty = []
        fromArb' (Node x left right) = fromArb' left ++ [x] ++ fromArb' right

-- 2
getFromInterval :: Int -> Int -> [Int] -> [Int]
getFromInterval _ _ [] = []
getFromInterval x y (h:t)
    | x <= h && h <= y = h : getFromInterval x y t
    | otherwise = getFromInterval x y t

getFromInterval' :: Int -> Int -> [Int] -> [Int]
getFromInterval' x y l = do
    z <- l
    if x <= z && z <= y then [z] else []

-- 3
newtype ReaderWriter env a = RW {getRW :: env -> (a,String)}

instance Monad (ReaderWriter env) where
    return va = RW $ \_ -> (va, "")
    ma >>= k = RW $ \r -> let (va, log1) = getRW ma r
                              (vb, log2) = getRW (k va) r
                          in (vb, log1 ++ log2)

{-
instance Applicative (ReaderWriter env) where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)

instance Functor (ReaderWriter env) where
    fmap f ma = pure f <*> ma

tell :: String -> ReaderWriter env ()
tell log = RW $ \_ -> ((), log)

logIncrement :: Int -> ReaderWriter Int Int
logIncrement x = do
    tell ("increment:" ++ show x ++ "--")
    return (x + 1)

logIncrement2 :: Int -> ReaderWriter Int Int
logIncrement2 x = do
    y <- logIncrement x
    logIncrement y

logIncrementN :: Int -> Int -> ReaderWriter Int Int
logIncrementN x n = do
    if n == 1 then
        logIncrement x
    else do
        y <- logIncrement x
        logIncrementN y (n - 1)

-- getRW (logIncrementN 2 4) 0
-}
