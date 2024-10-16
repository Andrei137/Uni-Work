newtype AM a = AM {getAM :: (Maybe a, String)}
    deriving Show

instance Monad AM where
    return x = AM (Just x, "")
    ma >>= k = let (va, log1) = getAM ma in
               case va of
                    Nothing -> AM (Nothing, log1)
                    Just a -> let (AM (mb, log2)) = k a in 
                              AM (mb, log1 ++ log2)

instance Functor AM where
    fmap f ma = f <$> ma

instance Applicative AM where
    pure = return
    mf <*> ma = do
        f <- mf
        f <$> ma 

testAM :: AM Int
testAM = ma >>= f
    where
        ma = AM (Just 7, "ana are mere ")
        f x = AM (if even x then Just x else Nothing, "si pere!")

testAM' :: AM Int
testAM' = ma >>= f
    where
        ma = AM (Just 8, "ana are mere ")
        f x = AM (if even x then Just x else Nothing, "si prune!")

-- testAM
-- AM {getAM = (Nothing,"ana are mere si pere!")}

-- testAM'
-- AM {getAM = (Just 8,"ana are mere si prune!")}