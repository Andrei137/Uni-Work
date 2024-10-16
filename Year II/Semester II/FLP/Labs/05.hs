data Term = Variable String | FuncSym String [Term]
    deriving (Eq, Show)

union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]
    
union :: (Eq a) => [[a]] -> [a]
union = foldr union2 []

-- returns all variables of a term
var :: Term -> [String]
var (Variable x) = [x]
var (FuncSym f ts) = union (map var ts)

-- substitutes, in a term, a variable by another term
subst :: Term -> String -> Term -> Term
subst (Variable x) s t
    | x == s = t
    | otherwise = (Variable x) 
subst (FuncSym f ts) s t = FuncSym f (map (\x -> subst x s t) ts)

data Equ = Equ Term Term
    deriving (Eq, Show)

data StepResult = FailureS | Stopped | SetS [Equ]
    deriving (Eq, Show)

step1 :: [Equ] -> StepResult
step1 [] = Stopped
step1 ((Equ (FuncSym f t1) (FuncSym g t2)):es)
    | f == g = SetS ((func t1 t2) ++ es) 
    | otherwise = case (step1 es) of
                  SetS fs -> SetS ((Equ (FuncSym f t1) (FuncSym g t2)):fs)
                  Stopped -> Stopped
    where func [] [] = []
          func (x:xs) (y:ys) = (Equ x y):(func xs ys)
step1 (e:es) = case (step1 es) of
                SetS fs -> SetS (e:fs)
                Stopped -> Stopped

step2 :: [Equ] -> StepResult
step2 [] = Stopped
step2 ((Equ (FuncSym f t1) (FuncSym g t2)):es)
    | f /= g = FailureS
    | otherwise = case (step2 es) of
                  SetS fs -> SetS ((Equ (FuncSym f t1) (FuncSym g t2)):fs)
                  FailureS -> FailureS
                  Stopped -> Stopped
step2 (e:es) = case (step2 es) of
                SetS fs -> SetS (e:fs)
                FailureS -> FailureS
                Stopped -> Stopped

-- remove equations x = x
step3 :: [Equ] -> StepResult
step3 [] = Stopped
step3 ((Equ (Variable x) (Variable y)):es)
    | x == y = SetS es
    | otherwise = case (step3 es) of
                  SetS fs -> SetS ((Equ (Variable x) (Variable y)):fs)
                  Stopped -> Stopped
step3 (e:es) = case (step3 es) of
               SetS fs -> SetS (e:fs)
               Stopped -> Stopped

step4 :: [Equ] -> StepResult
step4 [] = Stopped
step4 ((Equ (Variable x) (Variable y)):es) = case (step4 es) of
                                              SetS fs -> SetS ((Equ (Variable x) (Variable y)):fs)
                                              Stopped -> Stopped
step4 ((Equ t (Variable x)):es) = SetS ((Equ (Variable x) t):es)
step4 (e:es) = case (step4 es) of
               SetS fs -> SetS (e:fs)
               Stopped -> Stopped

step5 :: [Equ] -> StepResult
step5 [] = Stopped
step5 ((Equ (Variable x) (Variable y)):es) = case (step5 es) of
                                              SetS fs -> SetS ((Equ (Variable x) (Variable y)):fs)
                                              Stopped -> Stopped
step5 ((Equ (Variable x) t):es)
    | (elem x (var t)) = FailureS 
    | otherwise = case (step5 es) of
                    SetS fs -> SetS ((Equ (Variable x) t):fs)
                    FailureS -> FailureS
                    Stopped -> Stopped
step5 (e:es) = case (step5 es) of
                SetS fs -> SetS (e:fs)
                FailureS -> FailureS
                Stopped -> Stopped

-- candidates for "x=t" in step 6 of the algorithm
step6cand :: [Equ] -> [Equ]
step6cand l = filter isCandidate6 l
    where
        isCandidate6 (Equ (Variable x) t) = not (elem x (var t)) && length (filter (\(Equ t1 t2) -> if elem x (var t1) || elem x (var t2) then True else False) l) > 1
        isCandidate6 _ = False

-- substitutes in a list of equations a variable by a term EXCEPT for the equation "variable=term" (as used in step 6 of the algorithm)
substeq :: [Equ] -> String -> Term -> [Equ]
substeq [] _ _ = []
substeq ((Equ (Variable x) t):xs) s t1
    | x == s && t /= t1 = (Equ t1 (subst t s t1)):(substeq xs s t1)
    | x /= s && elem s (var t) = (Equ (Variable x) (subst t s t1)):xs
    | otherwise = (Equ (Variable x) t):(substeq xs s t1)
substeq (e:es) s t = e:(substeq es s t)

step6 :: [Equ] -> StepResult
step6 [] = Stopped
step6 l =
    let 
        cand = step6cand l 
    in
        case cand of
            [] -> Stopped
            ((Equ (Variable x) t):es) -> SetS (substeq l x t)
                
onestep :: [Equ] -> StepResult
onestep es = case (step1 es) of
              SetS fs -> SetS fs
              Stopped -> case (step2 es) of
                          FailureS -> FailureS
                          Stopped -> case (step3 es) of
                                      SetS fs -> SetS fs
                                      Stopped -> case (step4 es) of
                                                  SetS fs -> SetS fs
                                                  Stopped -> case (step5 es) of
                                                              FailureS -> FailureS
                                                              Stopped ->  case (step6 es) of
                                                                           SetS fs -> SetS fs
                                                                           Stopped -> Stopped

data AllResult = Failure | Set [Equ]
    deriving Show

unify :: [Equ] -> AllResult
unify es = case (onestep es) of
                    Stopped -> Set es
                    FailureS -> Failure
                    SetS fs -> unify fs
                    
eqset1 = [Equ (Variable "z") (FuncSym "f" [Variable "x"]), Equ (FuncSym "f" [Variable "t"]) (Variable "y")]
         -- z=f(x), f(t)=y  --> should have z=f(x), y=f(t)

eqset2 = [Equ (FuncSym "f" [Variable "x", FuncSym "g" [Variable "y"]]) (FuncSym "f" [FuncSym "g" [Variable "z"], Variable "z"])]
         -- f(x,g(y))=f(g(z),z) --> should have x=g(g(y)), z=g(y)

eqset3 = [Equ (FuncSym "f" [Variable "x", FuncSym "g" [Variable "x"], FuncSym "b" []]) (FuncSym "f" [FuncSym "a" [], FuncSym "g" [Variable "z"], Variable "z"])]
          -- f(x,g(x),b)=f(a,g(z),z) --> should return failure