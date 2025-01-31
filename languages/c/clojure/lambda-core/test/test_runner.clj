(ns test-runner
  (:require [clojure.test :as t]
            [numerals-test]
            [booleans-test]))

(defn -main [& args]
  (t/run-tests 'numerals-test 'booleans-test))
