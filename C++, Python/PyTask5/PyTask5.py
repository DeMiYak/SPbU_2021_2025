# Случай b - вырожденная ковариационная матрица, 
# X - d-мерная сфера

# Этапы построения программы:
# 1. библиотеки для генерации чисел и визуализации
# 2.1. генерация нормального распределения (одномерное)
# 2.2. генерация нормального распределения (многомерное)
# 3. алгоритм построения распределения на сфере
# 4. визуализация алгоритма на срезах размерности 2, 3.

# Условие: вырожденная ковариационная матрица (det = 0)

# На вход: многомерное нормальное распределение с вырожденной ковариационной матрицей

# 1.
import matplotlib.pyplot as plt
import numpy as np
n = 10**3   # длина выборки
# dim = 9, 15, 20, 30, 50, 100
dim = 100   # размерность распределения

# 2. Создание вырожденной ковариационной матрицы
# def CreateSingularMatrix(dim):
#     mat = np.random.uniform(-3, 3, size=(dim,dim))
#     if np.linalg.det(mat) != 0:
#         mat[dim-1] = mat[0]
#     mat = mat*np.transpose(mat)    
#     return mat

# Создаёт вырожденную матрицу
def CreateSingularMatrix(dim):
    mat = np.random.uniform(-10, 10, size=(dim,dim))
    # Симметричность сделает матрицу самосопряжённой в евклидовом пространстве
    mat = np.dot(mat,mat.T)
    eigenVal, eigenVec = np.linalg.eig(mat)
    eigenVal[-1] = 0
    valMat = np.diag(eigenVal)
    eigenVecInv = np.linalg.inv(eigenVec)
    mat = np.dot(np.dot(eigenVec, valMat), eigenVecInv)
    return mat
    

A = CreateSingularMatrix(dim)

# Заданная вырожденная ковариационная матрица
# Так как mat - самосопряжённая матрица, то A.T*A - положительно определённая матрица
covarMat = np.dot(A.T, A)
# print(np.linalg.cholesky(covarMat))

# Построили выборку
sample = np.random.standard_normal(size=(n, dim))
sample = np.dot(sample, A)
estSample = np.mean(sample, axis = 0)
# print(sample, "\n\n", estSample)
# print(sample,sample[0], type(sample))

# Сходимость к выборочной к.м. к заданной к.м. можно проверить через норму Фробениуса
estCovarMat = np.dot((sample - estSample).T, (sample - estSample))/n
dif = np.linalg.norm(covarMat - estCovarMat)
print(dif)

# Равномерное распределение на X - d-мерной сфере (d = dim)
sample = np.random.standard_normal(size=(n, dim))
sampleNormed = sample
for i in range(n):
    sampleNormed[i] = sampleNormed[i]/np.linalg.norm(sampleNormed[i])
plt.figure(figsize=(10,10))
circles = plt.subplot()

for vector in sampleNormed:
    plt.scatter(vector[0], vector[-1], c = 'blue')
circle1 = plt.Circle((0,0),1, color='r', fill = False)
circles.add_patch(circle1)
plt.xlim(-1,1)
plt.ylim(-1,1)
plt.grid(ls='--')
plt.show()