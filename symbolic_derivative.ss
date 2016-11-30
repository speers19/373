(define  (constant? x)  (number? x))

(define  (variable? x)  (symbol? x))

(define  (same-variable?  v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2))
  )

(define (make-sum a1 a2)  (list '+ a1 a2))

(define (make-product a1 a2)  (list '* a1 a2))

(define (make-difference a1 a2) (list '- a1 a2))

(define (make-quotient a1 a2) (list '/ a1 a2))

(define (make-sin a1) (list 'sin a1 ))

(define (make-cos a1) (list 'cos a1))

(define (make-negative-sin a1) (list '-sin a1))

(define (make-exp a1) (list 'exp a1))

(define (make-log a1) (list 'log a1))

(define  (sum?  x)
 (and (pair? x) (eq? (car x) '+)) 
 )

(define  (product?  x)
 (and (pair? x) (eq? (car x) '*)) 
 )

(define (quotient? x)
  (and (pair? x) (eq? (car x) '/))
  )

(define (difference? x)
  (and (pair? x) (eq? (car x) '-))
  )

(define (sin? x)
  (and (pair? x) (eq? (car x) 'sin))
  )

(define (cos? x)
 (and (pair? x) (eq? (car x) 'cos))
 )

(define (exp? x)
  (and (pair? x) (eq? (car x) 'exp))
  )

(define (log? x)
  (and (pair? x) (eq? (car x) 'log))
  )

(define (first s)  (cadr s))
(define (second s) (caddr s))

(define (deriv expr var)
  (cond

    ((constant? expr)
     0
     )

    ((variable? expr)    
     (cond
       ((same-variable? expr var)   1)
       (else  0)
       )
     )

    ((sum? expr)     
     (make-sum  (deriv  (first expr) var)
      (deriv  (second expr) var)
      )
     )

    ((product? expr)     
     (make-sum
      (make-product  (first   expr)
       (deriv  (second expr) var)
       )
      (make-product  (deriv  (first   expr) var)
       (second expr) 
       )
      )
     )

    ((difference? expr)
     (make-difference (deriv (first expr) var)
      (deriv (second expr) var)
      )
     )

    ((quotient? expr)
      (make-quotient
       (make-difference
        (make-product (deriv (first expr) var)
          (second expr))
        (make-product (first expr)
          (deriv (second expr) var)))
       (make-product (second expr) (second expr))
       )  
      )

    ((sin? expr)
      (make-product
        (make-cos (first expr))
        (deriv (first expr) var)
        )
      )

    ((cos? expr)
      (make-product
        (make-difference 0 (make-sin (first expr)))
        (deriv (first expr) var)
        )
      )

    ((exp? expr)
      (make-exp (first expr))
      )
    
    ((log? expr)
      (make-product
       (make-quotient
          1
       (first expr))
       (deriv (first expr) var)
       )
     )

     





;continue here
;-5.2 times 10 to the something

( else 'screwup)
)
  )



;(deriv '(/ (- (sin (* x (log (cos (/ x (+ (* x x) 1)))))) (* (* x x) x)) (exp (+ x 4))) 'x)

(deriv '(cos 2) 'x)
(deriv '(+ x 2) 'x)
(deriv '(exp (+ x 2)) 'x)
(deriv '(log x) 'x)


  (deriv
  (deriv 
    (deriv 
      (deriv '(/ (- (sin (* x (log (cos (/ x (+ (* x x) 1)))))) (* (* x x) x)) (exp (+ x 4))) 'x)
      'x)
    'x)
    'x)
