# LOGIC
_true = lambda x: lambda y: x
_false = lambda x: lambda y: y
_not = lambda b: b(_false)(_true)
_and = lambda b1: lambda b2: b1(b2)(_false)
_or = lambda b1: lambda b2: b1(_true)(b2)

# CHURCH NUMERALS
_zero = lambda f: lambda x: x
_succ = lambda n: lambda f: lambda x: f(n(f)(x))
_pred = lambda n: lambda f: lambda x: n(lambda g: lambda h: h(g(f)))(lambda u: x)(lambda a: a)
_one = _succ(_zero)

# HELPERS - not pure lambda calculus
read_bool = lambda b: print(b("t")("f"))
read_church = lambda n: print(n(lambda x: x+1)(0))

# EXAMPLES
print("LOGIC")
print("-------------")
print("TRUE/FALSE")
read_bool(_true)
read_bool(_false)

print("NOT")
read_bool(_not(_true))
read_bool(_not(_false))

print("AND")
read_bool(_and(_true)(_true))
read_bool(_and(_true)(_false))
read_bool(_and(_false)(_true))
read_bool(_and(_false)(_false))

print("OR")
read_bool(_or(_true)(_true))
read_bool(_or(_true)(_false))
read_bool(_or(_false)(_true))
read_bool(_or(_false)(_false))

print()
print("CHURCH NUMERALS")
print("-------------")
print("ZERO/SUCC")
read_church(_zero)
read_church(_one)
read_church(_succ(_one))
read_church(_succ(_succ(_one)))

print("PRED")
read_church(_pred(_one))
read_church(_pred(_succ(_one)))
read_church(_pred(_succ(_succ(_one))))
