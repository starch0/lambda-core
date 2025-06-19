# LOGIC
const _true  = x -> y -> x
const _false = x -> y -> y
const _not   = b -> b(_false)(_true)
const _and   = b1 -> b2 -> b1(b2)(_false)
const _or    = b1 -> b2 -> b1(_true)(b2)

# CHURCH NUMERALS
const _zero = f -> x -> x
const _succ = n -> f -> x -> f(n(f)(x))
const _pred = n -> f -> x -> n(g -> h -> h(g(f)))(_u -> x)(_a -> a)
const _one  = _succ(_zero)

# HELPERS - not pure lambda calculus
function readBool(b)
    println(b("t")("f"))
end

function readChurch(n)
    println(n(x -> x+1)(0))
end

# -------------------------------------------------

# EXAMPLES
println("LOGIC")
println("---------------")
println("TRUE/FALSE")
readBool(_true)    # t
readBool(_false)   # f

println("NOT")
readBool(_not(_true))   # f
readBool(_not(_false))  # t

println("AND")
readBool(_and(_true)(_true))     # t
readBool(_and(_true)(_false))    # f
readBool(_and(_false)(_true))    # f
readBool(_and(_false)(_false))   # f

println("OR")
readBool(_or(_true)(_true))      # t
readBool(_or(_true)(_false))     # t
readBool(_or(_false)(_true))     # t
readBool(_or(_false)(_false))    # f

println("\nCHURCH NUMERALS")
println("---------------")
println("ZERO/SUCC")
readChurch(_zero)                     # 0
readChurch(_one)                      # 1
readChurch(_succ(_one))               # 2
readChurch(_succ(_succ(_one)))        # 3

println("PRED")
readChurch(_pred(_one))               # 0
readChurch(_pred(_succ(_one)))        # 1
readChurch(_pred(_succ(_succ(_one)))) # 2