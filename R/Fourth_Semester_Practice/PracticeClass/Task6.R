# Задание 3 с прошедшей пары. Дана m — матрица смежности для
# ориентированного графа. Если из точки А в точку B есть путь,
# то m(A, B) = 1. В противном случае m(A, B) = 0.

# Если нормировать матрицу по строкам (то есть каждую строку
# матрицы разделить на сумму элементов в строке), получим матрицу
# p переходных вероятностей p(A, B) для некоторой марковской цепи,
# которая описывает следующий случайный процесс: на каждом шаге процесса,
# если вы находитесь в точке А графа, с вероятностью  p(A, B) вы переходите
# в точку B. Матрица pn = p^n (матрица p умножается сама на себя n раз) состоит
# из вероятностей pn(A, B) оказаться в точке B, если вы начинали путь 
# из точки A. Есть теорема о том, что если матрица p (а значит и соответствующий
# ей граф) обладает определенным свойством (давайте скажем, что любая точка
# является достижимой из любой другой точки), то при достаточно большом
# n pn(A, B) не зависит от А, то есть в какой бы точке графа вы не начали путь,
# через большое время вы с фиксированной вероятностью окажитесь в определенной
# точке графа. При таком раскладе, все строки в матрице pn(A, B) будут одинаковы
# начиная с некоторого n. Набор значений в каждой строке  называется стационарным
# распределением. Задача состоит в том, чтобы найти это распределение. Чтобы
# любая точка графа была точно достижима из другой, воспользуйтесь
# преобразованием 0.99 * p + 0.01 E / k, где E — матрица k на k, которая
# состоит из единиц, а k — количество точек в графе


# 0. Подключение библиотеки. Инициализация размера матрицы смежности
library('igraph')

x <- 5

matSample <- matrix(
  c(0, 0, 1, 0, 0,
    1, 1, 1, 0, 1,
    0, 0, 0, 0, 0,
    1, 0, 1, 0, 0,
    1, 1, 1, 0, 1)
  , ncol = x, nrow = x, byrow = TRUE)

matSample



m <- matrix(
  c(
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0
  ),
  nrow = 10,
  ncol = 10,
  byrow = TRUE
)

plot(graph_from_adjacency_matrix(m))

plot(graph_from_adjacency_matrix(matSample))


# 2. Цикл нормирования матрицы с проверкой на строки из нулей
rowSums(matSample)
which(rowSums(matSample)==0)

eraseNullRows <- function(matSample){
  while((min(rowSums(matSample)) == 0) && (length(matSample) != 0)){
    
    # 2.1. Нахождение нулевых строк
    ind_del <- which(rowSums(matSample)==0)
    
    # 2.2. Удаление нулевых строк
    if(length(ind_del) != 0) {
      matSample <- matSample[-ind_del,]
      matSample <- matSample[,-ind_del]
    }
  }
}

normalizeRows <- function(matSample){
  # 2.3. Нормирование матрицы
  for(i in 1:dim(matSample)[1]){
    matSample[i,] <- matSample[i,]/sum(matSample[i,])
  }
}

findStationaryVariance <- function(matSample){
  matSampleNew <- 0.99*matSample + 0.01/(x-length(ind_del))
  while(max(abs(matSampleNew - (matSampleNew <- matSampleNew%*%matSampleNew))) == 0){}
  return(matSampleNew)
  
}

solveSV <- function(matSample){
  eraseNullRows(matSample)
  normalizeRows(matSample)
  return(findStationaryVariance(matSample))
}
normalize
matSampleNew <- solveSV(matSample)
matSampleNew
# 3. Нахождение стационарного распределения
matSampleNew <- 0.99*matSample + 0.01/(x-length(ind_del))

matSampleNew

while(max(abs(matSampleNew - (matSampleNew <- matSampleNew%*%matSampleNew))) == 0){}

matSampleNew
