;I've done a sketch to visualize the problem, I can upload the sketch if needed
;problem is a different version of the tower of hannoi problem
;instead of (2^n)-1 it'll take (3^n)-1 movcs for n number of boxes because of the lighter on top rule
;I think the middle platform weight rule hinders the test cases, I've tried to get a success but failed

(define (move-containers-to-platform amount weights)

  ;sum of the weights for middle platform rule
  (define (sum-weights box-stack)
    (if (null? (cdr box-stack))
        (car box-stack)
        (+ (car box-stack) (sum-weights (cdr box-stack)))))

  ;the middle platform rule
  (let* ((limit (* (sum-weights weights) 0.75)))

         ;returning false if limit is esceeded
         (define (check sum)
           (if (> sum limit) #f sum))

         ;process for the job, num: number of boxes, from: current location, to: next location, wght: weight of current box, midwght: current weight of middle platform
         (define (job-process num from to wght midwght)
           (cond ((not midwght) #f)
                 ((= num 0) midwght)
                 ((= num 1)
                  (let* ((weight (car wght))

                    ;every move from platforms 1 to 3 and vice versa, will pass through platform 2
                    (mid-in (if (= from 2) midwght (check (+ midwght weight))))
                    (mid-out (if (and mid-in (= to 2)) mid-in (if mid-in (check (- mid-in weight)) #f))))
                    mid-out))

                 ;moving lighter boxes to clear the movement of the heaviest, then moving heaviest to middle
                 ;then moving lighter boxes back to move heaviest to final position, and lighter boxes on top
                 (else
                  (let* ((wght-rest (cdr wght))
                    (wght-curr (car wght))
                    (p1 (job-process (- num 1) from to wght-rest midwght))
                    (p2 (if p1 (check (+ p1 wght-curr)) #f))
                    (p3 (job-process (- num 1) to from wght-rest p2))
                    (p4 (if p3 (check (- p3 wght-curr)) #f)))
                    ;final move process
                    (job-process (- num 1) from to wght-rest p4)))))

    ;success or empty list depending on the result
           (let ((result (job-process amount 3 1 weights 0)))
             (if (not result) '() 'success))))

;tests
(move-containers-to-platform 5 '(20 30 50 60 80))
(move-containers-to-platform 4 '(10 30 60 100))
(move-containers-to-platform 6 '(10 20 30 80 90 100))