let _true = fun x -> fun _y -> x
let _false = fun _x -> fun y -> y

let _not = fun b -> b _false _true

let _and = fun b1 -> fun b2 -> b1 b2 _false
let _or = fun b1 -> fun b2 -> b1 _true b2


let _zero: 'a -> 'b -> 'b = fun _f -> fun x -> x
let _succ = fun n -> fun f -> fun x -> f (n f x)

let _pred =
    fun n -> fun f -> fun x -> n (fun g -> fun h -> h (g f)) (fun _u -> x) (fun a -> a)

let _one = _succ _zero

let read_bool = fun b -> (b "true" "false") |> printfn "%s"
let read_church = fun n -> (n (fun x -> x + 1) 0) |> printfn "%d"

// EXAMPLE
printfn "LOGIC"
printfn "----------------"
printfn "TRUE/FALSE"
read_bool _true
read_bool _false
printfn "NOT"
read_bool (_not _true)
read_bool (_not _false)
printfn "AND"
read_bool (_and _true _true)
read_bool (_and _true _false)
read_bool (_and _false _true)
read_bool (_and _false _false)
printfn "OR"
read_bool (_or _true _true)
read_bool (_or _true _false)
read_bool (_or _false _true)
read_bool (_or _false _false)

printfn "\nCHURCH NUMERALS"
printfn "----------------"
printfn "ZERO/SUCC"
read_church _zero
read_church (_one)
read_church (_succ _one)
read_church (_succ (_succ _one))
printfn "PRED"
read_church (_pred (_succ _zero))
read_church (_pred (_succ (_succ _zero)))
read_church (_pred (_succ (_succ (_succ _zero))))
