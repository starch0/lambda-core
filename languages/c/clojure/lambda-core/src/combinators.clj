(ns combinators)

(def Y (fn [f]
         ((fn [x]
            (x x))
          (fn [x]
            (f (fn [y]
                 ((x x) y)))))))

(def Z
  (fn [f]
    ((fn [x]
       (f (fn [y]
            ((x x) y))))
     (fn [x]
       (f (fn [y]
            ((x x) y)))))))

