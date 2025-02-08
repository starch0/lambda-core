fun interface T : (T) -> T {}
// LOGIC    
val TRUE: T
   	get() = T {x: T -> T {y: T -> x}}
val FALSE: T
   	get() = T {x: T -> T {y: T -> y}}
val NOT: T 
   	get() = T {x: T -> x(FALSE)(TRUE)}
val AND: T
   	get() = T {x: T -> T {y: T -> x(y)(FALSE)}}
val OR: T
   	get() = T {x: T -> T {y: T -> x(TRUE)(y)}}

// CHURCH NUMERALS
val ZERO: T
	get() = T{f: T -> T {x: T -> x}}
val SUCC: T
	get() = T {n: T -> T {f: T -> T {x: T -> f(n(f)(x))}}}
val PRED: T
	get() = T {n: T -> T {f: T -> T {x: T -> n(T {g: T -> T {h: T -> h(g(f))}})(T {u -> x})(T {u -> u})}}}

// HELPERS - not pure lambda calculus
fun readBool(t: T) {
	var res: Boolean? = null
    val _true: T = T {x -> 
       	res = true
       	x
    }
    val _false: T = T {x -> 
        res = false
        x
    }
    t(_true)(_false)({t: T -> t})
    println(res)
}

fun readChurchNumber(t: T) {
    var res: Int = 0
    
    val plusOne: T = T {x: T ->
        res++
        x
    }
    
    t(plusOne)({t:T -> t})
    println(res)
}

// -------------------------------------------------

// EXAMPLES
fun main() {
    println("LOGIC")
    println("----------------")
    println("TRUE/FALSE")
    readBool(TRUE) // true
    readBool(FALSE) // false

    println("NOT")
    readBool(NOT(TRUE)) // false
    readBool(NOT(FALSE)) //true
    
    println("AND")
    readBool(AND(FALSE)(FALSE)) // false
    readBool(AND(FALSE)(TRUE)) // false
    readBool(AND(TRUE)(FALSE)) // false
    readBool(AND(TRUE)(TRUE)) // true
    
    println("OR")
    readBool(OR(FALSE)(FALSE)) // false
    readBool(OR(FALSE)(TRUE)) // true
    readBool(OR(TRUE)(FALSE)) // true
    readBool(OR(TRUE)(TRUE)) // true
    
    println("CHURCH NUMERALS")
    println("---------------")
    println("ZERO/SUCC")
    readChurchNumber(ZERO) // 0
    readChurchNumber(SUCC(ZERO)) // 1
    readChurchNumber(SUCC(SUCC(ZERO))) // 2
    
    println("PRED")
    val THREE = SUCC(SUCC(SUCC(ZERO))) // 3
    readChurchNumber(PRED(THREE)) // 2
    readChurchNumber(PRED(PRED(THREE))) // 1 
    readChurchNumber(PRED(PRED(PRED(THREE)))) // 0
}