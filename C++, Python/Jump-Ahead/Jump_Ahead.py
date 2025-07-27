# -*- coding: utf-8 -*-

import numpy as np
import time

# 2 a). 
# Реализовать процедуру jump-ahead для датчика (вариант указан в таблице). 
# Продемонстрировать, что jump-ahead совпадает с 
# вычислением «в лоб» для небольших N (N порядка сотни), 
# и работает мгновенно для более-менее разумного большого N, например, миллиарда.

# Важное замечание: следите за отсутствием переполнений при 
# возведении матрицы в степень.

A = 30000005
C = 7373737
M = 536870912

def LCG(x):
    return (A*x + C)%M

def LCG_Jump(x, n):
    coef_m = np.array([(A,C),(0,1)])
    res_m = np.array([(1,0),(0,1)])
    
    sgn = 0
    if(n > 0): sgn = 1
    elif(n == 0): sgn = 0
    else: sgn = -1
    n *= sgn
    
    while(n):
        rem = n%2
        n //= 2
        if(rem):
            res_m = res_m.dot(coef_m)
        coef_m = coef_m.dot(coef_m)
        for j in range(2):
            coef_m[0][j] %= M
            res_m[0][j] %= M
    
    if(sgn == -1):
        res_m[0][0] = pow(int(res_m[0][0]), -1, M)
        res_m[0][1] = int(-1*int(res_m[0][0])*int(res_m[0][1]))%M
    x = int(res_m[0][0]*x + res_m[0][1])%M
    return x


n = 300
x = 1
for i in range(n):
    x = LCG(x)

y = LCG_Jump(1, n)
print(x, y, sep="\n")

k = 10**7
s = time.time()
print('\n', LCG_Jump(1, k))
f = time.time()
print("Computation Time: ", f - s)

# x = 1
# s = time.time()
# for i in range(k):
#     x = LCG(x)
# f = time.time()
# print(x, f - s, sep='\n')

m = LCG_Jump(1, -k)
for i in range(k):
    m = LCG(m)
print(m)
 