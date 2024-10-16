-- 1
pos :: Int -> Bool
pos x = if (x >= 0) then True else False

fct :: Maybe Int -> Maybe Bool
fct mx = mx >>= (\x -> Just (pos x))

fct' :: Maybe Int -> Maybe Bool
fct' mx = do
    x <- mx
    return (pos x)

-- 2
addM :: Maybe Int -> Maybe Int -> Maybe Int
addM Nothing _ = Nothing
addM _ Nothing = Nothing
addM (Just x) (Just y) = Just (x + y)

addM' :: Maybe Int -> Maybe Int -> Maybe Int
addM' mx my = 
    mx >>= (\x -> (my >>= (\y -> return (x + y))))

addM'' :: Maybe Int -> Maybe Int -> Maybe Int
addM'' mx my = do
    x <- mx
    y <- my
    return (x + y)

-- 3
cartesian_product :: Maybe Int -> Maybe Int -> Maybe (Int, Int)
cartesian_product xs ys = xs >>= ( \x -> (ys >>= \y-> return (x,y)))

cartesian_product' :: Maybe Int -> Maybe Int -> Maybe (Int, Int)
cartesian_product' xs ys = do
    x <- xs
    y <- ys
    return (x, y)

prod :: (Maybe Int -> Maybe Int -> Maybe Int) -> [Maybe Int] -> [Maybe Int] -> [Maybe Int]
prod f xs ys = [f x y | x <- xs, y <- ys]

prod' :: (Maybe Int -> Maybe Int -> Maybe Int) -> [Maybe Int] -> [Maybe Int] -> [Maybe Int]
prod' f xs ys = do
    x <- xs
    y <- ys
    return (f x y)

(***) :: Maybe Int -> Maybe Int -> Maybe Int
(***) Nothing _ = Nothing
(***) _ Nothing = Nothing
(***) (Just a) (Just b) = Just (a * b)

myGetLine :: IO String
myGetLine = getChar >>= \x ->
      if x == '\n' then
          return []
      else
          myGetLine >>= \xs -> return (x:xs)

myGetLine' :: IO String
myGetLine' = do 
    x <- getChar
    if x == '\n' then
        return []
    else do
        xs <- myGetLine'
        return (x:xs)

-- 4
prelNo noin = sqrt noin

ioNumber = do
     noin  <- readLn :: IO Float
     putStrLn $ "Intrare\n" ++ (show noin)
     let  noout = prelNo noin
     putStrLn $ "Iesire"
     print noout

ioNumber' =     
    (readLn :: IO Float) >>= 
    \noin -> 
    putStrLn ("Intrate\n" ++ (show noin)) >>
    let noout = prelNo noin in
    putStrLn "Iesire" >> 
    print noout

-- 5
{-
newtype WriterS a = Writer { runWriter :: (a, String) } 

instance Monad WriterS where
    return va = Writer (va, "")
    ma >>= k = let (va, log1) = runWriter ma
                   (vb, log2) = runWriter (k va)
               in  Writer (vb, log1 ++ log2)


instance  Applicative WriterS where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)       

instance  Functor WriterS where              
    fmap f ma = pure f <*> ma     

tell :: String -> WriterS () 
tell log = Writer ((), log)
  
logIncrement :: Int -> WriterS Int
logIncrement x = do
    tell ("increment:" ++ show x ++ "--")
    return (x + 1)

logIncrement2 :: Int -> WriterS Int
logIncrement2 x = do
    y <- logIncrement x
    logIncrement y

logIncrementN :: Int -> Int -> WriterS Int
logIncrementN x n = do
    if n == 1 then
        logIncrement x
    else do
        y <- logIncrement x
        logIncrementN y (n - 1)
-}

newtype WriterLS a = Writer { runWriter :: (a, [String]) }

instance Monad WriterLS where
    return va = Writer (va, [])
    ma >>= k = let 
                    (va, log1) = runWriter ma
                    (vb, log2) = runWriter (k va)
               in 
                    Writer (vb, log1 ++ log2)

instance Applicative WriterLS where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)  

instance  Functor WriterLS where              
    fmap f ma = pure f <*> ma

tell :: String -> WriterLS () 
tell log = Writer ((), [log])
  
logIncrement :: Int -> WriterLS Int
logIncrement x = do
    tell ("increment:" ++ show x)
    return (x + 1)

logIncrement2 :: Int -> WriterLS Int
logIncrement2 x = do
    y <- logIncrement x
    logIncrement y

logIncrementN :: Int -> Int -> WriterLS Int
logIncrementN x n = do
    if n == 1 then
        logIncrement x
    else do
        y <- logIncrement x
        logIncrementN y (n - 1)

-- 6
data Person = Person { name :: String, age :: Int }

showPersonN :: Person -> String
showPersonN (Person name a) = 
    "NAME: " ++ name
showPersonA :: Person -> String
showPersonA (Person n age) = 
    "AGE: " ++ show age

showPerson :: Person -> String
showPerson p = 
    "(" ++ showPersonN p ++ ", " ++ showPersonA p ++ ")"

newtype Reader env a = Reader { runReader :: env -> a }

instance Monad (Reader env) where
    return x = Reader (\_ -> x)
    ma >>= k = Reader f
        where f env = let a = runReader ma env
                      in runReader (k a) env

instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance Functor (Reader env) where              
  fmap f ma = pure f <*> ma    

mshowPersonN :: Reader Person String
mshowPersonN = Reader showPersonN
mshowPersonA :: Reader Person String
mshowPersonA = Reader showPersonA
mshowPerson ::  Reader Person String
mshowPerson = Reader showPerson