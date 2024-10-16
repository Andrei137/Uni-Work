data LambdaTerm = Var String | Lam String LambdaTerm | App LambdaTerm LambdaTerm
    deriving (Show, Eq)

-- union of two sets represented as lists
union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]

-- variables of a lambda term
var :: LambdaTerm -> [String]
var (Var v) = [v]
var (Lam v f) = union2 [v] (var f)
var (App a b) = union2 (var a) (var b)

-- free variables of a lambda term
fv :: LambdaTerm -> [String]
fv (Var v) = [v]
fv (Lam v f) = [x | x <- var f, x /= v]
fv (App a b) = union2 (fv a) (fv b)

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- fresh variable for a term
freshforterm :: LambdaTerm -> String
freshforterm t = head . filter (`notElem` (var t)) $ freshvarlist

-- the substitution operation for lambda terms
subst :: LambdaTerm -> String -> LambdaTerm -> LambdaTerm
subst (Var v) x t
    | x == v = t
    | otherwise = Var v
subst (App p q) x t = App (subst p x t) (subst q x t)
subst (Lam v p) x t
    | v == x = Lam v p
    | elem v (fv t) = Lam z . subst (subst p v . Var $ z) x $ t
    | otherwise = Lam v . subst p x $ t
        where z = freshforterm . Lam x . App t $ p

test_subst = subst (Lam "x" (App (Var "y") (Var "x"))) "y" (Var "x")

-- beta reduction in one step
beta1 :: LambdaTerm -> [LambdaTerm]
beta1 (Var x) = []
beta1 (App (Lam x m) n) = [subst m x n] ++ (map (\y -> App y n) . map (Lam x) $ beta1 m) ++ (map (App (Lam x m)) $ beta1 n)
beta1 (Lam x m) = map (Lam x) . beta1 $ m
beta1 (App p q) = (map (\x -> App x q) . beta1 $ p) ++ (map (App p) . beta1 $ q)

-- checks whether a term is in normal form
nf :: LambdaTerm -> Bool
nf t = (beta1 t) == []

data TermTree = TermTree LambdaTerm [TermTree]
    deriving Show

-- the beta-reduction tree of a lambda term
reductree :: LambdaTerm -> TermTree
reductree t = TermTree t . map reductree . beta1 $ t

-- depth-first traversal of all the nodes in a term tree
df_all :: TermTree -> [LambdaTerm]
df_all (TermTree t l) = t:(concat . map df_all $ l)

-- just the leaves
df_leaves :: TermTree -> [LambdaTerm]
df_leaves (TermTree lf []) = [lf]
df_leaves (TermTree _ l) = concat . map df_leaves $ l

-- the left-most outer-most reduction of a term
reduce :: LambdaTerm -> LambdaTerm
reduce (Var x) = Var x
reduce (Lam x t) = Lam x . reduce $ t
reduce (App (Lam x l) r) = reduce (subst l x r)
reduce (App p q)
    | r == p = App p . reduce $ q
    | otherwise = reduce (App r q)
        where r = reduce p

term1 = App (App (Lam "x" (Lam "y" (App (Var "x") (Var "y")))) (Var "z")) (Var "w")
term2 = App (Lam "x" (App (Lam "y" (Var "x")) (Var "z"))) (Var "w")

test_beta1 = df_leaves (reductree term1)
test_beta2 = df_leaves (reductree term2)

-- a branch of given length in a tree
branch :: Int -> TermTree -> Maybe [LambdaTerm]
branch 0 _ = Just []
branch 1 (TermTree t _) = Just [t]
branch n (TermTree t l) = case next of
                            [] -> Nothing
                            ((Just l):_) -> Just (t:l)
    where next = filter notNothing . map (branch (n - 1)) $ l
          notNothing Nothing = False
          notNothing _ = True
    

testbranch1 = branch 2 (reductree term1)

testbranch2 = branch 3 (reductree term1)

term_o = Lam "x" (App (Var "x") (Var "x"))
term_O = App term_o term_o

testO = reduce term_O -- should not terminate

term_b = App (App (Lam "x" (Lam "y" (Var "y"))) term_O) (Var "z")

testb = reduce term_b -- should terminate

testbranch3 = branch 10 (reductree term_b)

-- Church numeral of a number
church :: Int -> LambdaTerm
church n = Lam "f" . Lam "x" . funcComp $ n
    where funcComp 0 = Var "x"
          funcComp n = App (Var "f") (funcComp (n - 1))

-- convert from Church numeral back to number
backch :: LambdaTerm -> Int
backch (Lam _ (Lam _ dn)) = countChurch dn
    where countChurch (Var _) = 0
          countChurch (App _ dm) = 1 + (countChurch dm)

-- lambda term for successor
tsucc :: LambdaTerm 
tsucc = Lam "n" . Lam "f" . Lam "x" . App (Var "f") . App (App (Var "n") (Var "f")) $ (Var "x")

testsucc = backch ((reduce (App tsucc (church 7))))

-- lambda term for addition
tadd :: LambdaTerm
tadd = Lam "n" . Lam "m" . Lam "f" . Lam "x" . App (App (Var "n") (Var "f")) $ (App (App (Var "m") (Var "f")) (Var "x"))

testadd = backch ((reduce (App (App tadd (church 7)) (church 8))))

