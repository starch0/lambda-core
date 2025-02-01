package main

import "fmt"

type T func(t T) T

// LOGIC
var (
	_true  T = func(x T) T { return func(y T) T { return x } }
	_false T = func(x T) T { return func(y T) T { return y } }
	_not   T = func(b T) T { return b(_false)(_true) }
	_and   T = func(b1 T) T { return func(b2 T) T { return b1(b2)(_false) } }
	_or    T = func(b1 T) T { return func(b2 T) T { return b1(_true)(b2) } }
)

// CHURCH NUMERALS
var (
	_zero T = func(f T) T { return func(x T) T { return x } }
	_succ T = func(n T) T {
		return func(f T) T {
			return func(x T) T {
				return f(n(f)(x))
			}
		}
	}
	_pred T = func(n T) T {
		return func(f T) T {
			return func(x T) T {
				return n(func(g T) T { return func(h T) T { return h(g(f)) } })(func(u T) T { return x })(func(a T) T { return a })
			}
		}
	}
	_one T = _succ(_zero)
)

// HELPERS - not pure lambda calculus
func readBool(b T) bool {
	var res bool
	var closureTrue T = func(t T) T {
		res = true
		return t
	}
	var closureFalse T = func(t T) T {
		res = false
		return t
	}
	b(closureTrue)(closureFalse)(func(t T) T { return t })
	return res
}

func readChurch(n T) int {
	res := 0
	var closurePlusOne T = func(t T) T {
		res++
		return t
	}
	n(closurePlusOne)(func(t T) T { return t })
	return res
}

func main() {
	fmt.Println("LOGIC")
	fmt.Println("-------------")
	fmt.Println("TRUE/FALSE")
	fmt.Println(readBool(_true))
	fmt.Println(readBool(_false))

	fmt.Println("NOT")
	fmt.Println(readBool(_not(_true)))
	fmt.Println(readBool(_not(_false)))

	fmt.Println("AND")
	fmt.Println(readBool(_and(_true)(_true)))
	fmt.Println(readBool(_and(_true)(_false)))
	fmt.Println(readBool(_and(_false)(_true)))
	fmt.Println(readBool(_and(_false)(_false)))

	fmt.Println("OR")
	fmt.Println(readBool(_or(_true)(_true)))
	fmt.Println(readBool(_or(_true)(_false)))
	fmt.Println(readBool(_or(_false)(_true)))
	fmt.Println(readBool(_or(_false)(_false)))

	fmt.Println("\nCHURCH NUMERALS")
	fmt.Println("-------------")
	fmt.Println("ZERO/SUCC")
	fmt.Println(readChurch(_zero))
	fmt.Println(readChurch(_one))
	fmt.Println(readChurch(_succ(_one)))
	fmt.Println(readChurch(_succ(_succ(_one))))
	fmt.Println("PRED")
	fmt.Println(readChurch(_pred(_one)))
	fmt.Println(readChurch(_pred(_succ(_one))))
	fmt.Println(readChurch(_pred(_succ(_succ(_one)))))

}
