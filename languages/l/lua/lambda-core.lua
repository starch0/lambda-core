-- _lc postfix to prevent conflict
-- Bool value
local true_lc = function(x)
	return function(y)
		return x
	end
end
local false_lc = function(x)
	return function(y)
		return y
	end
end

-- Boolean Operations
local and_lc = function(a)
	return function(b)
		return a(b)(false_lc)
	end
end

local or_lc = function(a)
	return function(b)
		return a(true_lc)(b)
	end
end

local not_lc = function(a)
	return a(false_lc)(true_lc)
end

-- Church Numerals
local zero = function(f)
	return function(x)
		return x
	end
end
local one = function(f)
	return function(x)
		return f(x)
	end
end
local succ = function(n)
	return function(f)
		return function(x)
			return f(n(f)(x))
		end
	end
end
-- This is ugly
local pred = function(n)
	return function(f)
		return function(x)
			return n(function(g)
				return function(h)
					return h(g(f))
				end
			end)(function(u)
				return x
			end)(function(u)
				return u
			end)
		end
	end
end
-- a slightly better version of pred
local pred_v2 = function(n)
	return function(f)
		return function(x)
			local helper = function(g)
				return function(h)
					return h(g(f))
				end
			end
			return n(helper)(function(_)
				return x
			end)(function(u)
				return u
			end)
		end
	end
end
-- Helper functions
local read_bool = function(b)
	return b(true)(false)
end

local read_church = function(n)
	return n(function(x)
		return x + 1
	end)(0)
end

-- Test Cases
print(read_bool(true_lc)) -- true
print(read_bool(false_lc)) -- false
print(read_bool(not_lc(true_lc))) -- false
print(read_bool(not_lc(false_lc))) -- true
print(read_bool(and_lc(true_lc)(true_lc))) -- true
print(read_bool(and_lc(true_lc)(false_lc))) -- false
print(read_bool(and_lc(false_lc)(true_lc))) -- false
print(read_bool(and_lc(false_lc)(false_lc))) -- false
print(read_bool(or_lc(true_lc)(true_lc))) -- true
print(read_bool(or_lc(true_lc)(false_lc))) -- true
print(read_bool(or_lc(false_lc)(true_lc))) -- true
print(read_bool(or_lc(false_lc)(false_lc))) -- false

print(read_church(zero)) -- 0
print(read_church(succ(zero))) -- 1
print(read_church(succ(one))) -- 2
print(read_church(succ(succ(one)))) -- 3
print(read_church(pred(one))) -- 0
print(read_church(pred_v2(one))) -- 0
print(read_church(pred(succ(one)))) -- 1
print(read_church(pred_v2(succ(one)))) -- 1
print(read_church(pred(succ(succ(one))))) -- 2
print(read_church(pred_v2(succ(succ(one))))) -- 2
