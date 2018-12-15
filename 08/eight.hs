-- Subtrees and metadata
data Tree = Node [Tree] [Int] deriving Show

parse :: [Int] -> Tree
parse xs =
    let ([t], _) = (parseHelp xs 1)
     in t

parseHelp :: [Int] -> Int -> ([Tree], [Int])
parseHelp xs 0 = ([], xs)
parseHelp (c : m : rest) n =
    let (children, rem) = parseHelp rest c
        metadata = take m rem
        (stuff, more) = parseHelp (drop m rem) (n - 1)
     in ((Node children metadata) : stuff, more)

sumTree :: Tree -> Int
sumTree (Node ts m) = sum m + sum (map sumTree ts)


valueTree :: Tree -> Int
valueTree (Node [] m) = sum m
valueTree (Node ts m) =
    let values = map valueTree ts
        f i = if i > length values || i <= 0
                 then 0
                 else values !! (i - 1)
     in sum (map f m)

solve :: String -> String
solve s =
    let inp = parse $ map read $ words s
        sol1 = sumTree inp
        sol2 = valueTree inp
     in "ex1: " ++ (show sol1) ++ "\nex2: " ++ (show sol2) ++ "\n"

main = interact solve
