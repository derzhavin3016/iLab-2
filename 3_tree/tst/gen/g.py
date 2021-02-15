#!/usr/bin/env python3
import random

n = 1000000
step = 10
for i in range(2):
    print(int(n / step))
    for i in range(0, n, step):
        print(i)



n_req = 100000
print(n_req)
for i in range(n_req):
    lower = random.randint(-n, n)
    upper = random.randint(lower, n)
    print(str(lower) + ' ' + str(upper))

