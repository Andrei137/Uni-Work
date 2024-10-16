import Data.Char

transform :: String -> String
transform [] = []
transform (h:t)
    | isLower h = h : h : transform t
    | isDigit h = '*' : transform t
    | h `elem` "ADT" = (toLower h) : transform t
    | otherwise = h : transform t

transformMonad :: String -> String
transformMonad s = do
    c <- s
    if isLower c then
        [c, c]
    else if isDigit c then
        ['*']
    else if c `elem` "ADT" then
        [toLower c]
    else do
        [c]

-- transform "Ana,2"
-- "annaa,*"

-- transformMonad "Ana,2"
-- "annaa,8"

-- transform "ADTabc123" == transformMonad "ADTabc123"
-- True