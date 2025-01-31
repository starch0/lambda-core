(ns booleans-test
  (:require [booleans :refer :all]
            [clojure.test :refer :all]
            [print-macro :refer [is-print]]))

(deftest λ-booleans
  (testing "true"
    (is-print (= (toBoolean T) true)))

  (testing "false"
    (is-print (= (toBoolean F) false)))

  (testing "If"
    (is-print (= (toBoolean (((If T) T) F)) true))
    (is-print (= (toBoolean (((If F) T) F)) false)))

  (testing "And"
    (is-print (= (toBoolean ((And T) T)) true))
    (is-print (= (toBoolean ((And T) F)) false))
    (is-print (= (toBoolean ((And F) T)) false))
    (is-print (= (toBoolean ((And F) F)) false))
    (is-print (= (toBoolean ((And T) ((And T) T))) true))
    (is-print (= (toBoolean ((And T) ((And F) T))) false)))

  (testing "Or"
    (is-print (= (toBoolean ((Or T) T)) true))
    (is-print (= (toBoolean ((Or T) F)) true))
    (is-print (= (toBoolean ((Or F) T)) true))
    (is-print (= (toBoolean ((Or F) F)) false))
    (is-print (= (toBoolean ((Or F) ((Or F) F))) false))
    (is-print (= (toBoolean ((Or F) ((Or T) F))) true)))

  (testing "Not"
    (is-print (= (toBoolean (Not T)) false))
    (is-print (= (toBoolean (Not F)) true))
    (is-print (= (toBoolean (Not (Not T))) true))
    (is-print (= (toBoolean (Not (Not F))) false)))

  (testing "Xor"
    (is-print (= (toBoolean ((Xor T) T)) false))
    (is-print (= (toBoolean ((Xor T) F)) true))
    (is-print (= (toBoolean ((Xor F) T)) true))
    (is-print (= (toBoolean ((Xor F) F)) false)))

  (testing "Expressions"
    ;T AND T AND F OR T
    (is-print (= (toBoolean ((And T) ((And T) ((Or F) T))))
           true))

    ;T AND F AND F OR T AND T
    (is-print (= (toBoolean ((And T) ((And F) ((Or F) ((And T) T)))))
           false))

    ;T OR (F AND F OR T AND T)
    (is-print (= (toBoolean ((Or T) ((And F) ((Or F) ((And T) T)))))
           true))

    ;F OR (F AND F OR F AND T)
    (is-print (= (toBoolean ((Or F) ((And F) ((Or F) ((And F) T)))))
           false))

    ;F OR F AND F OR T AND T
    (is-print (= (toBoolean ((And ((Or F) F)) ((And T) ((Or F) T))))
           false))

    ;T OR F AND F OR T AND T
    (is-print (= (toBoolean ((And ((Or T) F)) ((And T) ((Or F) T))))
           true))))
