(define (transpose l)

	(define p '())
	(define n (length l))
	(define answer '())
	(define counter (length (car l)))

	(recwork l p n answer counter)
)

(define (recwork l p n answer counter)

	(cond 
		((= counter 0) 
			(reverse answer))
		(else
			(recwork (slicearray l p n) p n (cons (firstrow l p n) answer) (- counter 1)))
	)
)

(define (firstrow l p n)

	(cond 
		((= n 0) 
			(reverse p))
		(else 
			(firstrow (cdr l) (cons (car (car l)) p) (- n 1)))
	)
)

(define (slicearray l p n) 

	(cond
		((= n 0) 
			(reverse p))
		(else 
			(slicearray (cdr l) (cons (cdr (car l)) p) (- n 1)))
	)
) 

(define l

	(list
		(list 2 4 7 1 4 6)
		(list 8 5 2 0 7 6)
		(list 4 2 2 9 7 6)
	)
)

(transpose l)