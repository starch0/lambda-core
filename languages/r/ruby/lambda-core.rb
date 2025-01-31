# LOGIC
_true = ->(x) { ->(y) { x } }
_false = ->(x) { ->(y) { y } }
_not = ->(b) { b[_false][_true] }
_and = ->(b1) { ->(b2) { b1[b2][_false] } }
_or = ->(b1) { ->(b2) { b1[_true][b2] } }

# CHURCH NUMERALS
_zero = ->(f) { ->(x) { x } }
_succ = ->(n) { ->(f) { ->(x) { f[n[f][x]] } } }
_pred = ->(n) {
  ->(f) {
    ->(x) {
      n[->(g) { ->(h) { h[g[f]] } }][->(u) { x }][->(a) { a }]
    }
  }
}
_one = _succ[_zero]

# HELPERS - not pure lambda calculus
def read_bool(b)
  puts b["t"]["f"]
end

def read_church(n)
  puts n[->(x) { x + 1 }][0]
end

# EXAMPLES
puts "LOGIC"
puts "---------------"
puts "TRUE/FALSE"
read_bool(_true) # t
read_bool(_false) # f

puts "NOT"
read_bool(_not[_true]) # f
read_bool(_not[_false]) # t

puts "AND"
read_bool(_and[_true][_true]) # t
read_bool(_and[_true][_false]) # f
read_bool(_and[_false][_true]) # f
read_bool(_and[_false][_false]) # f

puts "OR"
read_bool(_or[_true][_true]) # t
read_bool(_or[_true][_false]) # t
read_bool(_or[_false][_true]) # t
read_bool(_or[_false][_false]) # f

puts "\nCHURCH NUMERALS"
puts "---------------"
puts "ZERO/SUCC"
read_church(_zero) # 0
read_church(_one) # 1
read_church(_succ[_one]) # 2
read_church(_succ[_succ[_one]]) # 3

puts "PRED"
read_church(_pred[_one]) # 0
read_church(_pred[_succ[_one]]) # 1
read_church(_pred[_succ[_succ[_one]]]) # 2
