{-
  Hello World in Haskell

run using commands:
ghc hello_worldxtimes.hs -o prog
./prog
-}


hello_worlds 0 = return ()
hello_worlds x = do putStrLn "Hello World"
                    hello_worlds (x-1)
main = do
   putStrLn "How many times do you want?"
   n <- readLn :: IO Int
   hello_worlds n