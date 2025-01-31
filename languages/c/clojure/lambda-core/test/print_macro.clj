(ns print-macro
  (:require  [clojure.test :as t]))

(defmacro is-print
  ([form]
   `(let [form-args# (rest '~form)
          first-arg# (first form-args#)
          second-arg# (second form-args#)]
      (println (format "%s = %s => %s" 
                       t/*testing-contexts* 
                       (pr-str first-arg#) 
                       (pr-str second-arg#)))
      (t/is ~form))))
