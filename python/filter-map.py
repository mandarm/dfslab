import math

def is_prime(n) :
    if n == 0 or n == 1 :
        return False
    for i in range(2, 1+int(math.sqrt(n))) :
        if n % i == 0 :
            return False
    return True

A = list(range(10))
B = list(range(10,20))

P = filter(is_prime, A)
T = filter( lambda x : x % 3 == 0, A)
print(list(P), list(T))

M = map(lambda x,y : x+y, A, B)
print(list(M))
M = map(lambda x,y : x+y, A, B[:3])
print(list(M))
