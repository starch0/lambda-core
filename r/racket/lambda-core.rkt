#lang racket

; LOGIC
(define _true 
    (lambda (x) 
        (lambda (y) x)))

(define _false 
    (lambda (x) 
        (lambda (y) y)))

(define _not
    (lambda (b)
        ((b _false) _true)))

(define _and
    (lambda (b1) 
        (lambda (b2) 
            ((b1 b2) _false))))

(define _or
    (lambda (b1)
        (lambda (b2) 
            ((b1 _true) b2))))


; CHURCH NUMERALS
(define _zero 
    (lambda (f) 
        (lambda (x) x)))

(define _succ
    (lambda (n)
        (lambda (f)
            (lambda (x) 
                (f ((n f) x))))))

(define _pred
    (lambda (n)
        (lambda (f)
            (lambda (x)
                (((n (lambda (g)
                        (lambda (h) (h (g f)))))
                    (lambda (u) x))
                 (lambda (a) a))))))

(define _one (_succ _zero))


; HELPERS - not pure lambda calculus
(define read-bool
    (lambda (b)
        (displayln ((b "t") "f"))))

(define read-church
    (lambda (n)
        (displayln ((n (lambda (x) (+ x 1))) 0))))

; -------------------------------------------------

; EXAMPLES
(displayln "LOGIC")
(displayln "--------------")
(displayln "TRUE/FALSE")
(read-bool _true) ; t
(read-bool _false) ; f

(displayln "NOT")
(read-bool (_not _true)) ; f
(read-bool (_not _false)) ; t

(displayln "AND")
(read-bool ((_and _true) _true)) ; t
(read-bool ((_and _true) _false)) ; f
(read-bool ((_and _false) _true)) ; f
(read-bool ((_and _false) _false)) ; f

(displayln "OR")
(read-bool ((_or _true) _true)) ; t
(read-bool ((_or _true) _false)) ; t
(read-bool ((_or _false) _true)) ; t
(read-bool ((_or _false) _false)) ; f

(displayln "\nCHURCH NUMERALS")
(displayln "--------------")
(displayln "ZERO/SUCC")
(read-church _zero) ; 0
(read-church (_succ _zero)) ; 1
(read-church (_succ (_succ _zero))) ; 2
(read-church (_succ (_succ (_succ _zero)))) ; 3

(displayln "PRED")
(read-church (_pred _one)) ; 0
(read-church (_pred (_succ _one))) ; 1
(read-church (_pred (_succ (_succ _one)))) ; 2

