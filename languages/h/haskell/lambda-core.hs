true' a b = a

false' a b = b

not' p = p false' true'

and' b1 b2 = b1 b2 false'

or' b1 = b1 true'

churchToBool b = b True False

zero' f x = x

one' = succ' zero'

succ' n f x = f $ n f x

pred' n f x = n (\g h -> h (g f)) (const x) id

churchToNum n = n (+ 1) 0

main = do
  -- basic booleans
  print $ churchToBool true'
  print $ churchToBool false'

  -- not
  print $ churchToBool $ not' true'
  print $ churchToBool $ not' false'

  -- and
  print $ churchToBool $ and' false' false'
  print $ churchToBool $ and' false' true'
  print $ churchToBool $ and' true' false'
  print $ churchToBool $ and' true' true'

  -- or
  print $ churchToBool $ or' false' false'
  print $ churchToBool $ or' false' true'
  print $ churchToBool $ or' true' false'
  print $ churchToBool $ or' true' true'

  -- numbers
  print $ churchToNum zero'
  print $ churchToNum one'
  print $ churchToNum $ pred' $ succ' one'
  print $ churchToNum $ pred' one'
