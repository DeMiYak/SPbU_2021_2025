# 3 б) Взять небольшой невыпуклый многоугольник, реализовать моделирование 
# в невыпуклом случае. Например, можно взять многоугольник из файла (это CSV, 
# вершины в порядке обхода против часовой стрелки. Помните, что 
# между последней и первой вершиной есть отрезок), 
# и продемонстрировать ваше решение на нём.

import numpy as np
import matplotlib.pyplot as plt
import random
import time
Data = np.loadtxt('coord.txt', skiprows=1, dtype='float', delimiter=',')
Data1 = np.copy(Data)
plt.plot(Data1[:, 0], Data1[:, 1], **{'color': 'blue', 'marker': 'o'})

def skew_prod(a, b): #косое произведение двух векторов
    return a[0]*b[1] - a[1]*b[0]


dataTriangle = []
index = 0
while(len(Data) > 3):
    # Возьмём три точки, для которых образуем треугольник в случае успех
    prevPoint = Data[(index-1)%len(Data)]
    point = Data[index%len(Data)]
    nextPoint = Data[(index+1)%len(Data)]
    
    firstVect = prevPoint - point
    secondVect = point - nextPoint
    canBuild = True
    triAreaOr = skew_prod(firstVect, secondVect)
    
    # Проверка на косое произведение
    if(triAreaOr > 0):
        # Проверка на отсутствие точек внутри треугольника
        # Один из способов: если с точками треугольника и точкой цикла
        # все косые произведения от их векторов < 0 - вектор с точкой цикла и вектор треугольника;
        # ориентируемы, как правая тройка
        # >= 0 - на границе или вне треугольника
        triArea = abs(triAreaOr)
        for i in range(len(Data)):
            # Независимая от треугольника точка (из цикла)
            firIndie = prevPoint - Data[i]
            secIndie = point - Data[i]
            thrIndie = nextPoint - Data[i]
            fourthIndie = nextPoint - prevPoint
            
            first_if = skew_prod(secIndie, firstVect) < 0
            second_if = skew_prod(firIndie, fourthIndie) < 0
            third_if = skew_prod(thrIndie, secondVect) < 0
            #print('УСЛОВИЕ ВНУТРИ   ',first_if , second_if , third_if)
            if first_if and second_if and third_if:#внутри
                canBuild = False
                break
    else:
        canBuild = False
    
    # Если можем построить треугольник, добавляем его точки и удаляем point
    #print(canBuild)
    if(canBuild):
        dataTriangle.append([prevPoint,point,nextPoint])
        Data = np.delete(Data, index%len(Data),axis=0)
        for z in dataTriangle:
            x, y = zip(*z)
            plt.plot(Data1[:, 0], Data1[:, 1], **{'color': 'blue', 'marker': 'o'})
            plt.plot(x, y, **{'color': 'red', 'marker': 'o', 'linewidth':'5.0'})
        plt.show()
    else:# Если не сделали ухо - переходим к следующей точке 
        index = (index+1)%len(Data)
        
# Добавляем оставшийся треугольник
dataTriangle.append(Data)
for z in dataTriangle:
    x, y = zip(*z)
    plt.plot(x, y, **{'color': 'blue', 'marker': 'o'})
plt.show()

# Уменьшаем число вычислений за счёт введения матрицы треугольников
# с двумя векторами и точкой между ними
dataTriWithVec = []
for triangle in dataTriangle:
    fVec = triangle[-1] - triangle[0]
    sVec = triangle[1] - triangle[0]
    #print('fVec: ', fVec, 'sVec: ', sVec, '\n\n\n')
    dataTriWithVec.append([triangle[0], sVec, fVec])

# Считаем площади треугольников и находим их вероятности выпадения
#dataTriWithVec = np.array(dataTriWithVec)
#print(dataTriWithVec, dataTriWithVec[0][1], sep='\n')

dataArea = []
for triangle in dataTriWithVec:
    area = abs(skew_prod(triangle[-1], triangle[1]))/2
    dataArea.append(area)

dataArea = dataArea/sum(dataArea)
# print(dataArea, sum(dataArea))

# Моделирование дискретного распределения
modOne = 10**4
randDistr = []

# Метод без копирования памяти через np.array
start = time.time()
for i in range(modOne):
    
    triangle = random.choices(dataTriWithVec, dataArea)
    # По какой-то причине, random.choices оборачивает список
    # в ещё один список
    #triangle = np.array(triangle[0])
    x, y = random.uniform(0, 1), random.uniform(0, 1)
    if(x+y>1):
        x = 1 - x
        y = 1 - y
    # xyVec = x*triangle[-1] + y*triangle[1]
    # randDistr.append(xyVec + triangle[0])
    xyVec = [x*triangle[0][-1][0] + y*triangle[0][1][0], x*triangle[0][-1][1] + y*triangle[0][1][1]]
    randDistr.append([xyVec[0] + triangle[0][0][0], xyVec[1] + triangle[0][0][1]])
end = time.time()
print('time: ', end - start, '\n')
for z in randDistr:
    #print('\n', z)
    x, y = z[0], z[1]
    plt.plot(x, y, **{'color': 'blue', 'marker': 'o', 'linestyle': 'none'})
plt.show()  

# Метод с копированием памяти через np.array
start = time.time()
for i in range(modOne):
    
    triangle = random.choices(dataTriWithVec, dataArea)
    # По какой-то причине, random.choices оборачивает список
    # в ещё один список
    triangle = np.array(triangle[0])
    x, y = random.uniform(0, 1), random.uniform(0, 1)
    if(x+y>1):
        x = 1 - x
        y = 1 - y
    xyVec = x*triangle[-1] + y*triangle[1]
    randDistr.append(xyVec + triangle[0])
    # xyVec = [x*triangle[0][-1][0] + y*triangle[0][1][0], x*triangle[0][-1][1] + y*triangle[0][1][1]]
    # randDistr.append([xyVec[0] + triangle[0][0][0], xyVec[1] + triangle[0][0][1]])
end = time.time()
print('time: ', end - start, '\n')
for z in randDistr:
    #print('\n', z)
    x, y = z[0], z[1]
    plt.plot(x, y, **{'color': 'blue', 'marker': 'o', 'linestyle': 'none'})
plt.show()

# В целом, метод без выделения памяти работает в два раза быстрее