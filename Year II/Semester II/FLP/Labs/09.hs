data PCFTerm = Var String | Lam String PCFTerm | App PCFTerm PCFTerm | Zero | Suc PCFTerm | IfZ PCFTerm PCFTerm String PCFTerm | Fix String PCFTerm

instance Show PCFTerm where
    show (Var v) = v
    show (Lam x t) = "\\" ++ x ++ ".(" ++ show t ++ ")"
    show (App m n) = "(" ++ show m ++ ")(" ++ show n ++ ")"
    show Zero = "0"
    show (Suc n) = "S(" ++ show n ++ ")"
    show (IfZ a b c d) = "If(" ++ show a ++ " == 0) then " ++ show b ++ " else (" ++ show d ++ ")[" ++ c ++ " gets replaced]"
    show (Fix f t) = "Fix " ++ f ++ " " ++ show t

-- union of two sets represented as lists
union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]

-- variables of a PCF term
var :: PCFTerm -> [String]
var (Var s) = [s]
var (Lam v t) = union2 [v] (var t)
var (App m n) = union2 (var m) (var n)
var Zero = []
var (Suc t) = var t
var (IfZ z tr w fs) = union2 (union2 (var z) (var tr)) (union2 [w] (var fs))
var (Fix w t) = union2 [w] (var t)

-- free variables of a PCF term
fv :: PCFTerm -> [String]
fv (Var v) = [v]
fv (Lam x m) = [y | y <- fv m, y /= x]
fv (App m n) = union2 (fv m) (fv n)
fv Zero = []
fv (Suc t) = fv t
fv (IfZ z tr w fs) = union2 (fv z) . union2 (fv tr) $ [x | x <- fv fs, x /= w]
fv (Fix w t) = [x | x <- fv t, x /= w]

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- fresh variable for a PCF term
freshforterm :: PCFTerm -> String
freshforterm t = head [x | x <- freshvarlist, notElem x (var t)]

-- the substitution operation for PCF terms
subst :: PCFTerm -> String -> PCFTerm -> PCFTerm
subst (Var x) y t
    | x == y        = t
    | otherwise     = Var x
subst (Lam x s) y t
    | x == y        = Lam x s
    | elem x (fv t) = let z = freshforterm (Lam y (App s t)) in Lam z (subst (subst s x (Var z)) y t)
    | otherwise     = Lam x (subst s y t)
subst (App s u) y t = App (subst s y t) (subst u y t)
subst Zero _ _      = Zero
subst (Suc s) y t   = Suc (subst s y t)
subst (IfZ n s w u) y t
    | w == y        = IfZ (subst n y t) (subst s y t) w u
    | elem w (fv t) = let z = freshforterm (Fix y (App u t)) in IfZ (subst n y t) (subst s y t) z (subst (subst u w (Var z)) y t)
    | otherwise     = IfZ (subst n y t) (subst s y t) w (subst u y t)
subst (Fix x s) y t
    | x == y        = Fix x s
    | elem x (fv t) = let z = freshforterm (Fix y (App s t)) in Fix z (subst (subst s x (Var z)) y t)
    | otherwise     = Fix x (subst s y t)

-- eager isValue
isValueE :: PCFTerm -> Bool
isValueE Zero = True
isValueE (Lam x m) = True
isValueE (Suc m) = isValueE m
isValueE _ = False

-- eager beta reduction in one step
beta1E :: PCFTerm -> [PCFTerm]
beta1E (Var v) = []
beta1E (Lam x m) = []
beta1E (App (Lam x m) n)
    | isValueE n = [subst m x n]
    | otherwise = map (App (Lam x m)) . beta1E $ n
beta1E (App m n) = map (\x -> App x n) . beta1E $ m
beta1E Zero = []
beta1E (Suc m)
    | isValueE m = []
    | otherwise = map Suc . beta1E $ m
beta1E (IfZ Zero n _ _) = [n]
beta1E (IfZ (Suc m) t w p)
    | isValueE (Suc m) = [subst p w m]
    | otherwise = map (\x -> IfZ x t w p) . beta1E . Suc $ m
beta1E (IfZ m t w p) = map (\x -> IfZ x t w p) . beta1E $ m
beta1E (Fix w m) = [subst m w (Fix w m)]

-- checks whether a term is in normal form
nfE :: PCFTerm -> Bool
nfE = null . beta1E

data TermTree = TermTree PCFTerm [TermTree]
    deriving Show

-- the beta-reduction tree of a lambda term
reductreeE :: PCFTerm -> TermTree
reductreeE t = TermTree t (map reductreeE (beta1E t))

--depth-first traversal of all the leaves in a term tree
df_leaves :: TermTree -> [PCFTerm]
df_leaves (TermTree t []) = [t]
df_leaves (TermTree _ l) = concatMap df_leaves l

-- the left-most outer-most reduction of a term
reduceE :: PCFTerm -> PCFTerm
reduceE = head . df_leaves . reductreeE

-- natural numbers in PCF
number :: Int -> PCFTerm
number 0 = Zero
number n = Suc (number (n-1))

-- conversion from PCF back to natural numbers
backnr :: PCFTerm -> Int
backnr Zero = 0
backnr (Suc n) = (backnr n) + 1

-- PCF term for addition
tadd :: PCFTerm
tadd = Fix "fadd" . Lam "x" . Lam "y" . IfZ y x "w" . Suc . App (App fadd x) $ w
    where y = Var "y"
          x = Var "x"
          w = Var "w"
          fadd = Var "fadd"

testadd = backnr (reduceE (App (App tadd (number 2)) (number 3)))

-- PCF term for subtraction
tsub :: PCFTerm
tsub = Fix "fsub" . Lam "x" . Lam "y" . IfZ y x "v" . IfZ x Zero "w" . App (App fsub w) $ v
    where x = Var "x"
          y = Var "y"
          w = Var "w"
          v = Var "v"
          fsub = Var "fsub"

testsub1 = backnr (reduceE (App (App tsub (number 15)) (number 8)))

testsub2 = backnr (reduceE (App (App tsub (number 7)) (number 8)))

-- PCF term for GCD
tgcd :: PCFTerm
tgcd = Fix "fgcd" . Lam "x" . Lam "y" . IfZ x y "w" . IfZ y (Suc w) "v" . IfZ (App (App tsub v) w) (App (App fgcd . App (App tsub w) $ v) . Suc $ v) "u" . App (App fgcd (Suc w)) . Suc $ u
    where x = Var "x"
          y = Var "y"
          w = Var "w"
          v = Var "v"
          u = Var "u"
          fgcd = Var "fgcd"

testgcd = backnr (reduceE (App (App tgcd (number 30)) (number 36)))

-- PCF term for minimization
tmu :: PCFTerm
tmu = Lam "f" . App (Fix "mini" . Lam "n" . IfZ (App f n) n "_" . App mini . Suc $ n) $ Zero
    where n = Var "n"
          f = Var "f"
          mini = Var "mini"

testmu1 = backnr (reduceE (App tmu (Lam "x" (App (App tsub (number 15)) (Var "x")))))
testmu2 = backnr (reduceE (App tmu (Lam "x" (App (App tadd (number 15)) (Var "x"))))) -- should not terminate