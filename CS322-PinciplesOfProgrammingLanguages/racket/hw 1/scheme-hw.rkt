#lang racket

(define (pick index my-list)
  (cond
    ((null? list) '())
    ((< index 1) '())
    (( = index 1) (car my-list))
    (else (pick (- index 1) (cdr my-list)))))

(define (reverse my-list)
  (define (helper old-list new-list)
    (if(null? old-list)
       new-list
       (helper (cdr old-list)(cons(car old-list) new-list))))
  (helper my-list '()))

(define (deep-reverse my-list)
  (if (pair? my-list)
      (reverse(map deep-reverse my-list))
      my-list))

(define (frontier tree)
  (if (pair? tree)
      (append (frontier (car tree)) (frontier (cdr tree)))
      (cons tree '())))

(provide pick frontier reverse deep-reverse)


