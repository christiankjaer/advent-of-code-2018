main = interact (show . firstRepeat . parse . lines)

parse :: [String] -> [Int]
parse = map (\x -> read (filter (/= '+') x))

firstRepeat :: [Int] -> Int
firstRepeat l =  g (== 0) 0 l where
    g f n [] = g f n l
    g f n (x:xs) =
        let t = x + n in
            if f t then t else g (\m -> m == t || f m) t xs
