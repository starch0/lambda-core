(ns combinators-test
  (:require [lambda :refer [λ]]
            [combinators :refer :all]
            [booleans :refer :all]
            [numerals :refer :all]
            [clojure.test :refer :all]))

(def factorial-gen
  ;; Church encoding of functions, such as 'λ', does not 
  ;; naturally support 'recur'. This is because the 'λ' macro expands into an 
  ;; anonymous function (created using 'fn'), and functions defined with 'fn' 
  ;; cannot use 'recur' unless the 'recur' is in the tail position.
  ;;
  ;; The 'fn' function in Clojure is needed because it allows us to define a 
  ;; recursive function where 'recur' can be used correctly in the tail position. 
  ;; When the function is structured with 'fn', 'recur' will correctly jump back 
  ;; to the function without adding a new stack frame, thus ensuring the recursion 
  ;; is efficient and won't result in stack overflow.
  (fn [f]
    (fn [n acc]
      ;; Church's 'If' introduces an additional function call, which prevents 'recur'
      ;; from being the final operation, thus breaking TCO and causing a stack overflow.
      ;; Hence, using native 'if' instead of Church's 'If' because
      ;; 'recur' must be the last operation for tail call optimization (TCO).
      (if (toBoolean ((n (λ x F)) T))
        acc
        (recur (pred n) ((mult acc) n))))))

(def Y-factorial (Y factorial-gen))
(def Z-factorial (Z factorial-gen))

(deftest Y-Combinator
  (testing "Y-factorial"
    (is (= (toInt (Y-factorial (fromInt 9) one)) 362880))))

(deftest Z-Combinator
  (testing "Z-factorial"
    (is (= (toInt (Z-factorial (fromInt 9) one)) 362880))))

