import queue_alt
import random
import time


M = 100

for N in [ 10, 100, 1000, 10000, 100000 ] :
    queue_alt.size = N+1
    Q = [ 0 for i in range(queue_alt.size) ]

    start = time.process_time();
    for i in range(N) :
        queue_alt.enqueue(Q, i) # random.randint(0,N)
    for i in range(N) :
        x = queue_alt.dequeue(Q)
    end = time.process_time();
    print("Time for %d elements (alternative implementation): %.4f" % (N, end - start))

    start = time.process_time();
    for i in range(N) :
        Q[i] = i # random.randint(0,N)
    for i in range(N) :
        x = Q.pop(0)
    end = time.process_time();
    print("Time for %d elements (default implementation): %.4f" % (N, end - start))

