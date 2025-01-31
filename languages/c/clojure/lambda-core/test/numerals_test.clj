(ns numerals-test
  (:require [numerals :refer :all]
            [clojure.test :refer :all]
            [print-macro :refer [is-print]]))
 
(deftest λ-numbers
  (testing "zero"
    (is-print (= (toInt zero) 0)))

  (testing "one"
    (is-print (= (toInt (succ zero)) 1))
    (is-print (= (toInt one) 1)))

  (testing "two"
    (is-print (= (toInt (succ (succ zero))) 2))
    (is-print (= (toInt two) 2)))

  (testing "three"
    (is-print (= (toInt (succ (succ (succ zero)))) 3)))

  (testing "predecessor"
    (is-print (= (toInt (pred one)) 0))
    (is-print (= (toInt (pred two)) 1))
    (is-print (= (toInt (pred (succ (succ (succ zero))))) 2))
    (is-print (= (toInt (pred (fromInt 10))) 9))))

(deftest λ-numerical-operations
  (testing "addition"
    (is-print (=
         (toInt ((plus (fromInt 7)) (fromInt 5)))
         12))
    (is-print (=
         (toInt ((plus (fromInt 7)) ((plus (fromInt 6)) (fromInt 2))))
         15)))

  (testing "subtraction"
    (is-print (=
         (toInt ((minus (fromInt 7)) (fromInt 5)))
         2))
    (is-print (=
         (toInt ((minus (fromInt 7)) ((minus (fromInt 6)) (fromInt 2))))
         3)))

  (testing "multiplication"
    (is-print (=
          (toInt ((mult (fromInt 2)) (fromInt 3)))
          6))
    (is-print (=
          (toInt ((mult (fromInt 2)) ((mult (fromInt 5)) (fromInt 3))))
          30)))

  (testing "exponentiation"
    (is-print (=
          (toInt ((exp (fromInt 2)) (fromInt 3)))
          8))
    (is-print (=
          (toInt ((exp (fromInt 2)) ((exp (fromInt 2)) (fromInt 3))))
          256))))

(deftest λ-numeral-expressions
  (testing "numeral expressions"
    ; 3 * (2 + 5) - 2^3
    (is-print (=
         (toInt ((minus ((mult (fromInt 3))
                         ((plus (fromInt 2)) (fromInt 5))))
                 ((exp (fromInt 2)) (fromInt 3))))
         13))))

(deftest λ-toStr
  (testing "toStr"
    (is-print (= (toStr zero) "λf.λn.(n)"))
    (is-print (= (toStr one) "λf.λn.(f(n))"))
    (is-print (= (toStr two) "λf.λn.(f(f(n)))"))
    (is-print (= (toStr (succ (succ (succ zero)))) "λf.λn.(f(f(f(n))))"))
    (is-print (= (toStr (fromInt 5)) "λf.λn.(f(f(f(f(f(n))))))"))))

