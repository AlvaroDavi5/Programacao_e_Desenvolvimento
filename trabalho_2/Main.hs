import System.IO
import Data.List (sortBy, sort)
import Data.Set (Set)
import qualified Data.Set as Set
import Data.Map (Map)
import qualified Data.Map as Map

type Point = [Double]
type PointId = Int
type Distance = Double
type Link = (PointId, PointId, Distance)
type Points = Map PointId Point
type Groups = [[PointId]]

splitOn :: Char -> String -> [String]
splitOn delim s = case dropWhile (== delim) s of
    "" -> []
    s' -> w : splitOn delim s''
      where (w, s'') = break (== delim) s'

trim :: String -> String
trim = reverse . dropWhile (== ' ') . reverse . dropWhile (== ' ')

readCsvFile :: String -> IO [[String]]
readCsvFile path = do
    content <- readFile path
    let csvLines = lines content
    let csvRows = map (map trim . splitOn ',') csvLines
    return csvRows

writeListFile :: String -> Groups -> IO ()
writeListFile path groups = do
    let content = unlines [intercalate ", " (map show (sort group)) | group <- groups]
    writeFile path content
  where
    intercalate sep [] = ""
    intercalate sep [x] = x
    intercalate sep (x:xs) = x ++ sep ++ intercalate sep xs

readPoints :: String -> IO Points
readPoints path = do
    csvData <- readCsvFile path
    let pointsList = zip [1..] csvData
    let pointsMap = Map.fromList [(pid, map read row) | (pid, row) <- pointsList]
    return pointsMap

euclideanDistance :: Point -> Point -> Distance
euclideanDistance p1 p2
    | length p1 /= length p2 = error "Os pontos devem ter o mesmo número de dimensões."
    | otherwise = sqrt $ sum [(x - y) ^ 2 | (x, y) <- zip p1 p2]

findClosestPoint :: PointId -> Points -> Set PointId -> (PointId, Distance)
findClosestPoint current pts used =
    let candidates = [(pid, euclideanDistance (pts Map.! current) coords) 
                     | (pid, coords) <- Map.toList pts, not (Set.member pid used)]
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
buildLinks pts = buildLinksHelper 1 (Set.singleton 1) []
  where
    buildLinksHelper current used acc
        | Set.size used >= Map.size pts = acc
        | otherwise =
            let (next, dist) = findClosestPoint current pts used
                newUsed = Set.insert next used
                newLink = (current, next, dist)
            in buildLinksHelper next newUsed (newLink : acc)

dfs :: Set PointId -> Map PointId [PointId] -> PointId -> [PointId] -> (Set PointId, [PointId])
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
    
    buildAdjacency :: [Link] -> Map PointId [PointId]
    buildAdjacency linkList =
        let emptyAdj = Map.fromList [(p, []) | p <- Set.toList allPoints]
        in foldl addLink emptyAdj linkList
      where
        addLink adj (p1, p2, _) =
            let adj1 = Map.adjust (p2:) p1 adj
            in Map.adjust (p1:) p2 adj1
    
    findGroups :: Map PointId [PointId] -> Set PointId -> Groups
    findGroups adj remaining
        | Set.null remaining = []
        | otherwise =
            let point = Set.findMin remaining
                (newVisited, group) = dfs Set.empty adj point []
                newRemaining = Set.difference remaining newVisited
            in sort group : findGroups adj newRemaining

mainFunc :: String -> String -> Int -> IO ()
mainFunc inputFile outputFile k = do
    pts <- readPoints inputFile
    let links = buildLinks pts
    let groups = splitGroups links k
    
    putStrLn "Agrupamentos:"
    mapM_ (\group -> putStrLn $ intercalate ", " (map show (sort group))) groups
    writeListFile outputFile groups
  where
    intercalate sep [] = ""
    intercalate sep [x] = x
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
