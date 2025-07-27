from math import gcd



dataX, dataY, dataZ = list(), list(), list()
with open('num.txt', 'r') as file:
    for line in file:
        dataX.append(int(line))

for i in range(len(dataX) - 1):
    dataY.append(dataX[i+1]-dataX[i])

for i in range(1, len(dataY) - 1):
    dataZ.append(dataY[i]**2 - dataY[i-1]*dataY[i+1]) 

M = gcd(*dataZ)
A = (dataY[2]*pow(dataY[1], -1, M))%M
C = (dataX[2]-A*dataX[1])%M

print('dataX', dataX, 'dataY', dataY, 'dataZ', dataZ, 'A: multiplication coefficient', A, 'C: shift coefficient', C, 'M: module', M, sep='\n')