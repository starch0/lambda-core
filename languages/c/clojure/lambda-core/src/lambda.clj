(ns lambda)

(defmacro λ
  [args & body]
  `(fn [~args] ~@body))
