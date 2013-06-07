( ( word) word2)
;F-> <endoffile> || TF
;T-> (S)
;S-> () || atom || (S) || ()S || atom S || (S)S
;
;F -> 
;	T -> (S)
;		S-> ()S   
;		S-> (S) 


(()(ash))
(defun project (y x)
  (let (
        (ip-xy (sum (* x y)))
        (ip-xx (sum (* x x)))
        )
    (* (/ ip-xy ip-xx) x))
)

(defun project (y x)
  (let (
        (ip-xy (sum (* x y)))
        (ip-xx (sum (* x x)))
        )
    (* (/ ip-xy ip-xx) x))
)
(defparameter *small* 1)
(defparameter *big* 100)

(defun guess-my-number ()
     (ash (+ *small* *big*) -1))

(defun bigger ()
     (setf *small* (1+ (guess-my-number)))
     (guess-my-number))

