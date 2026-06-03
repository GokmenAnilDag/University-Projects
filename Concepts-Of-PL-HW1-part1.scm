;I've sketched the process to understand the problem, I can upload the sketch if needed.
;basically, the top face of the current die will increase by 13 - sum of touching faces for the next die.
;in the given test input, touching faces can't be >=11
;so, first die can have 1,2,4,5,6,7,8,9 for it's possible top face
;second die can have 3,4,6,7,8,9,10 since 9+2 is 11 and eliminated
;final die's top face can be >=11
;I think we can make a recursion to find the possible results this way

;our function template
(define (find-top-face-candidates num-dice touching-sum known-face)

  ;opposite sides has to sum to 13
  (define (opposite n)
    (- 13 n))

  ;increase current-top by 13 - touching-sum
  (define (next-top current-top)
    (+ (- 13 touching-sum) current-top))

  ;check if current-top will exceed 12 during the recursion
  (define (stack-checker current-top dice-left)
    (cond
      [(> current-top 12) #f] ;;stack not possible
      [(= dice-left 1) current-top] ;;stack possible
      [else (stack-checker (next-top current-top) (- dice-left 1))]))

  ;recursion for each possible face
  (define (face-rec faces)
    ;stopping condition
    (if (null? faces)
        '()
        ;list prep
        (let ([f (car faces)]
              [rest (cdr faces)])
          ;check for known-face
          (if (and (not (= f known-face))
                   (not (= f (opposite known-face))))
              ;check if the face will reach the top for each face remaining, if successful, add it to the result list
              (let ([result (stack-checker f num-dice)])
                (if result
                    (cons result (face-rec rest))
                    (face-rec rest)))
              ;removing the known-face by skipping it
              (face-rec rest)))))

  ;calling the recursion with our 12 sides
  (face-rec '(1 2 3 4 5 6 7 8 9 10 11 12)))

;tests
(find-top-face-candidates 4 11 10)
(find-top-face-candidates 3 7 4)
(find-top-face-candidates 5 8 12)
(find-top-face-candidates 3 9 2)
(find-top-face-candidates 4 10 6)