import Data.Char

data Pereche a b = MyP a b 
    deriving Show

newtype Lista a = MyL [a]
    deriving Show

class MyOp m where
    myOp :: (a -> b) -> (b -> a) -> m (Pereche a b) -> m (Pereche b a)

instance MyOp Lista where
    myOp f g (MyL l) = MyL (myOp' f g l)
        where
            myOp' _ _ [] = []
            myOp' f g ((MyP x y):t) = (MyP (f x) (g y)) : (myOp' f g t)


lp :: Lista (Pereche Int Char)
lp = MyL [MyP 97 'a', MyP 3 'b', MyP 100 'd']

lp2 :: Lista (Pereche Char Int)
lp2 = MyL [MyP 'd' 1, MyP 'a' 100]

-- myOp chr ord lp 
-- MyL [MyP 'a' 97,MyP '\ETX' 98,MyP 'd' 100]

-- myOp ord chr lp2
-- MyL [MyP 100 '\SOH',MyP 97 'd']  