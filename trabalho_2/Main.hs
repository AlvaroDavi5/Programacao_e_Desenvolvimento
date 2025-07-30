import System.IO
import qualified Data.Set as Set
import qualified Data.Map as Map

type PointId = Int
type Distance = Double
type Point = [Distance]
type Link = (PointId, PointId, Distance)
type Points = Map.Map PointId Point
type Groups = [[PointId]]

sort :: Ord a => [a] -> [a]
sort [] = []
sort (x:xs) = sort smaller ++ [x] ++ sort larger
  where
    smaller = [y | y <- xs, y <= x]
    larger = [y | y <- xs, y > x]

sortBy :: (a -> a -> Ordering) -> [a] -> [a]
sortBy _ [] = []
sortBy cmp (x:xs) = sortBy cmp smaller ++ [x] ++ sortBy cmp larger
  where
    smaller = [y | y <- xs, cmp y x /= GT]
    larger = [y | y <- xs, cmp y x == GT]

trim :: String -> String
trim = reverse . dropWhile (== ' ') . reverse . dropWhile (== ' ')

splitByChar :: Char -> String -> [String]
splitByChar delim s = case dropWhile (== delim) s of
    "" -> []
    spl -> fp : splitByChar delim sp
      where (fp, sp) = break (== delim) spl

readCsvFile :: String -> IO [[String]]
readCsvFile path = do
    content <- readFile path
    let csvLines = lines content
    let csvRows = map (map trim . splitByChar ',') csvLines
    return csvRows

readPoints :: String -> IO Points
readPoints path = do
    csvData <- readCsvFile path
    -- comeca o ID 1
    let pointsList = zip [1..] csvData
    let pointsMap = Map.fromList [(pid, map read row) | (pid, row) <- pointsList]
    return pointsMap

euclideanDistance :: Point -> Point -> Distance
euclideanDistance p1 p2
    | length p1 /= length p2 = error "Os pontos devem ter o mesmo número de dimensões."
    | otherwise = sqrt $ sum [(x - y) ^ (2 :: Int) | (x, y) <- zip p1 p2]

findClosestPoint :: PointId -> Points -> Set.Set PointId -> (PointId, Distance)
findClosestPoint current pts visited =
    let candidates = [(pid, euclideanDistance (pts Map.! current) coords) 
                     | (pid, coords) <- Map.toList pts, not (Set.member pid visited)]
        sortedCandidates = sortBy compareDistance candidates
    in head sortedCandidates
  where
    compareDistance (pid1, dist1) (pid2, dist2)
        | dist1 < dist2 = LT
        | dist1 > dist2 = GT
        | pid1 < pid2 = LT
        | pid1 > pid2 = GT
        | otherwise = EQ

buildLinks :: Points -> [Link]
-- comeca com o ponto 1 e um conjunto de visitados contendo apenas o ponto 1
buildLinks pts = buildLinksHelper 1 (Set.singleton 1) []
  where
    buildLinksHelper current visited acc
        | Set.size visited >= Map.size pts = acc
        | otherwise =
            let (next, dist) = findClosestPoint current pts visited
                newVisited = Set.insert next visited
                newLink = (current, next, dist)
            in buildLinksHelper next newVisited (newLink : acc)

dfs :: Set.Set PointId -> Map.Map PointId [PointId] -> PointId -> [PointId] -> (Set.Set PointId, [PointId])
dfs visited adj node currentGroup =
    let newVisited = Set.insert node visited
        newGroup = node : currentGroup
        neighbors = Map.findWithDefault [] node adj
        unvisitedNeighbors = filter (`Set.notMember` newVisited) neighbors
    in foldl (\(vis, grp) neighbor -> dfs vis adj neighbor grp) (newVisited, newGroup) unvisitedNeighbors

splitGroups :: [Link] -> Int -> Groups
splitGroups links k
    -- caso K seja menor ou igual a 1, retorna todos os pontos em um único grupo
    | k <= 1 = [sort $ Set.toList allPoints]
    -- caso K seja maior ou igual ao número de links + 1, retorna cada ponto em um grupo separado
    | k >= length links + 1 = [[p] | p <- sort $ Set.toList allPoints]
    | otherwise =
        let distSorted = sortBy (\(_, _, d1) (_, _, d2) -> compare d2 d1) links
            linksToKeep = drop (k - 1) distSorted
            adj = buildAdjacency linksToKeep
            groups = findGroups adj allPoints
        in groups
  where
    allPoints = Set.fromList [p | (p1, p2, _) <- links, p <- [p1, p2]]
    buildAdjacency :: [Link] -> Map.Map PointId [PointId]
    buildAdjacency linkList =
        let emptyAdj = Map.fromList [(p, []) | p <- Set.toList allPoints]
        in foldl addLink emptyAdj linkList
      where
        addLink adj (p1, p2, _) =
            let adj1 = Map.adjust (p2:) p1 adj
            in Map.adjust (p1:) p2 adj1
    findGroups :: Map.Map PointId [PointId] -> Set.Set PointId -> Groups
    findGroups adj remaining
        | Set.null remaining = []
        | otherwise =
            let point = Set.findMin remaining
                (newVisited, group) = dfs Set.empty adj point []
                newRemaining = Set.difference remaining newVisited
            in sort group : findGroups adj newRemaining

writeListFile :: String -> Groups -> IO ()
writeListFile path groups = do
    let content = unlines [intercalate ", " (map show (sort group)) | group <- groups]
    writeFile path content
  where
    intercalate _ [] = ""
    intercalate _ [x] = x
    intercalate sep (x:xs) = x ++ sep ++ intercalate sep xs

mainFunc :: String -> String -> Int -> IO ()
mainFunc inputFile outputFile k = do
    points <- readPoints inputFile
    let links = buildLinks points
    let groups = splitGroups links k

    putStrLn "Agrupamentos:"
    mapM_ (\group -> putStrLn $ intercalate ", " (map show (sort group))) groups
    writeListFile outputFile groups
  where
    intercalate _ [] = ""
    intercalate _ [x] = x
    intercalate sep (x:xs) = x ++ sep ++ intercalate sep xs

main :: IO ()
main = do
    putStr "Forneca o nome do arquivo de entrada: "
    hFlush stdout
    inputFile <- getLine
    putStr "Forneca o nome do arquivo de saida: "
    hFlush stdout
    outputFile <- getLine
    putStr "Forneca o número de grupos (K): "
    hFlush stdout
    groupSize <- getLine
    mainFunc inputFile outputFile (read groupSize)
