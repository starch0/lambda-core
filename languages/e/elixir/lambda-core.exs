#!/usr/bin/env elixir

###########
#  LOGIC  #
###########

_true = fn x -> fn y -> x end end
_false = fn x -> fn y -> y end end

_not = fn b -> b.(_false).(_true) end
_and = fn b1 -> fn b2 -> b1.(b2).(_false) end end
_or = fn b1 -> fn b2 -> b1.(_true).(b2) end end

#####################
#  CHURCH NUMERALS  #
#####################

_zero = fn f -> fn x -> x end end
_succ = fn n -> fn f -> fn x -> f.(n.(f).(x)) end end end

_pred = fn n ->
  fn f ->
    fn x ->
      n.(fn g -> fn h -> h.(g.(f)) end end).(fn u -> x end).(fn a -> a end)
    end
  end
end

_one = _succ.(_zero)

########################################
#  HELPERS - not pure lambda calculus  #
########################################

read_bool = fn b -> IO.puts(b.("t").("f")) end
read_church = fn n -> IO.puts(n.(fn x -> x + 1 end).(0)) end

##############
#  EXAMPLES  #
##############

IO.puts("LOGIC")
IO.puts("--------------")
IO.puts("TRUE/FALSE")
# t
read_bool.(_true)
# f
read_bool.(_false)

IO.puts("NOT")
# f
read_bool.(_not.(_true))
# t
read_bool.(_not.(_false))

IO.puts("AND")
# t
read_bool.(_and.(_true).(_true))
# f
read_bool.(_and.(_true).(_false))
# f
read_bool.(_and.(_false).(_true))
# f
read_bool.(_and.(_false).(_false))

IO.puts("OR")
# t
read_bool.(_or.(_true).(_true))
# t
read_bool.(_or.(_true).(_false))
# t
read_bool.(_or.(_false).(_true))
# f
read_bool.(_or.(_false).(_false))

IO.puts("\nCHURCH NUMERALS")
IO.puts("--------------")
IO.puts("ZERO/SUCC")
# 0
read_church.(_zero)
# 1
read_church.(_succ.(_zero))
# 2
read_church.(_succ.(_succ.(_zero)))
# 3
read_church.(_succ.(_succ.(_succ.(_zero))))

IO.puts("PRED")
# 0
read_church.(_pred.(_one))
# 1
read_church.(_pred.(_succ.(_one)))
# 2
read_church.(_pred.(_succ.(_succ.(_one))))
