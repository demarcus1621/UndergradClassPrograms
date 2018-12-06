#lang racket

;Author:  DeMarcus Campbell
;COMP 3220 Homework 5

;This is Homework 5 Exercise#1
(define flat (lambda(in)
               (cond ((null? in) in)
                     ((null? (car in)) (flat (cdr in)))
                     ((atom? (car in)) (cons (car in) (flat (cdr in))))
                     (else (append (flat (car in)) (flat (cdr in)))))))

(define (atom? in) ;Inspiration drawn from StackOverflow
  (and (not (null? in))
       (not (pair? in))))

;Modify this function to test functionality of Exercise 1
(define test (list '(1 2) 3 4))
test
(flat test)

;This is Homework 5 Exercise#2
(define mod3 (lambda (in)
               (if (= (remainder in 3) 0) #t
                   #f)))

;The variable x can be changed to test program functionality
(define x 41)
x
(mod3 x)

;This is Homework 5 Exercise#3
(define isort (lambda (xs)
                (if (null? xs) xs (insert (list(car xs)) (isort (cdr xs))))))

(define insert (lambda (x lis)
                 (if (null? lis) x
                     (if (null? x) lis
                         (if  (< (car lis) (car x))
                              (cons (car lis) (insert (cdr lis) x))
                              (cons (car x) (insert (cdr x) lis)))))))

;Modify this function to test Exercise 3
(define temp (list 3 2 1))
"Insertion Sort"
temp
(isort temp)

;This is Homework 5 Exercise#4
(define reverse (lambda (x)
                (cond [(null? x) x]
                      [(not (list? x)) "Argument is not a list!"]
                      [(append (reverse (cdr x))(list (car x)))])))

;Modify this list to test that program works
(define lis (list 1 2 3 4 4 3 2 1) )
(define lis2 lis)

(define compare (lambda (in1 in2)
                  (if (equal? in1 in2) "This list is palindrome"
                      "This list is not a palindrome")))

(define lis3 (reverse lis))
lis3
lis2
(compare lis3 lis2)

;This is Homework 5 Exercise#5
(define (part compare lis)
  (cond ((null? lis) lis)
        ((compare (car lis)) (cons (car lis) (part compare(cdr lis))))
        (else (part compare (cdr lis)))))

(define (qsort lis) ;Inspiration drawn from Steven J. Zeil
  (cond ((null? lis) lis)
        (else (let ((piv (car lis)))
                (append (append (qsort (part (lambda (x) (< x piv)) lis))
                                (part (lambda(x) (eq? x piv)) lis))
                        (qsort (part (lambda(x) (> x piv )) lis)))))))

;Modify this function to test the Quicksort function
(define qslist (list 9 58 7 4 5 2 4 1))
"Quicksort"
qslist
(qsort qslist)