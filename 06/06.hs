import System.Environment

type InputData = [(Int, Int)]

testInp = parse "1, 1\n1, 6\n8, 3\n3, 4\n5, 5\n8, 9"

parse :: String -> InputData
parse inp =
    let l1 = lines $ filter (/= ',') inp
        l2 = map words l1
     in map (\[x, y] -> (read x, read y)) l2

minmax :: InputData -> ((Int, Int), (Int, Int))
minmax d =
    let (xs, ys) = unzip d
     in ((minimum xs, maximum xs), (minimum ys, maximum ys))

dist :: (Int, Int) -> (Int, Int) -> Int
dist (x1, y1) (x2, y2) =
    abs (x1 - x2) + abs (y1 - y2)

sumDist :: (Int, Int) -> InputData -> Int
sumDist p ps = sum $ map (dist p) ps

main = do
    args <- getArgs
    inp <- readFile (args !! 0)
    let stuff = parse inp
    let (_, (maxx, maxy)) = minmax stuff
    let res = length $ filter (<10000) [sumDist (x,y) stuff | x <- [0..10*maxx], y <- [0..10*maxy]]
    putStrLn (show res)
