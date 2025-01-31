(ns y-combinator-test
  (:require [y-combinator :refer :all]
            [clojure.test :refer :all]))


(def factorial-gen (fn [func]
                     (fn [n]
                       (if (zero? n)
                         1
                         (* n (func (dec n)))))))

(deftest λ-Y-Combinator
  (testing "factorial"
    (is (= ((Y factorial-gen) 19) 121645100408832000))))
