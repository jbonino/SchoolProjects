#lang racket

(require rackunit "scheme-hw.rkt")

(define hw-tests
  (test-suite "scheme homework tests"
              
   (test-case "test pick"
    (begin
      (check-equal? (pick 0 '(1 2 3)) '())
      (check-equal? (pick 7 '(1 2 3)) '())
      (check-equal? (pick 1 '(3 2 1)) 3)
      (check-equal? (pick 2 '(3 2 1)) 2)
      (check-equal? (pick 3 '(3 2 1)) 1) ))

  (test-case "frontier"
    (begin
      (check-equal? (frontier 42) '(42))
      (check-equal? (frontier (cons 1 (cons 2 3))) '(1 2 3))
      (check-equal?
       (frontier (cons (cons (cons 1 (cons 2 3)) 4) 5))
       '(1 2 3 4 5)) ))

  (test-case "my-reverse"
    (begin
      (check-equal? (my-reverse '(1 2 3)) '(3 2 1))
      (check-equal? (my-reverse '((1 2) (3 4))) '((3 4) (1 2))) ))

  (test-case "deep-reverse"
    (begin
      (check-equal? (deep-reverse '(1 2 3)) '(3 2 1))
      (check-equal? (deep-reverse '((1 2) (3 4))) '((4 3) (2 1)))
      (check-equal? (deep-reverse '()) '())
      (check-equal? (deep-reverse 42) 42)
      (check-equal?
       (deep-reverse '(1 2 (3 (4 5) 6) ((7 8))))
       '(((8 7)) (6 (5 4) 3) 2 1)) )) ))

(require rackunit/gui)
(test/gui hw-tests)
