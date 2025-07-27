# Список функций для построения временного ряда

###############################################################################
###############################################################################
###############################################################################


# Строит траекторную матрицу из временного ряда с длиной окна L
BuildTrajectoryMatrix<-function(timeSeries, L){

  timeSeries <- as.vector(timeSeries)

  # Длина окна не должна превосходить длину временного ряда
  if(length(timeSeries) <= L) stop("L parameter (window length) must be less than timeSeries length")


  K <- length(timeSeries) - L + 1

  # Инициализация траекторной матрицы
  matrixResult <- matrix(0, ncol = K, nrow = L)

  for (i in 1:K) {
    matrixResult[,i]<-timeSeries[i:(i+L-1)]
  }

  return(matrixResult)
}

# Функция диагонального усреднения
DiagonalAveraging <- function(x){
  x <- as.matrix(x)

  # Если длина окна больше числа окон - транспонируем матрицу
  if(dim(x)[1] > dim(x)[2]) x <- tr(x)

  L <- dim(x)[1] # Длина окна
  K <- dim(x)[2] # Число окон
  N <- L + K - 1 # Длина ряда

  print(paste("L = ", L, "K = ", K, "N = ", N))


  timeSeriesResult <- c()

  # Восстановление компоненты ряда (по формуле с тремя случаями)

  # Случай один
  for(i in 1:L){
    temporaryValue <- 0

    for(j in 1:i){
      temporaryValue = temporaryValue + x[j, i - j + 1]
    }

    timeSeriesResult[i] <- temporaryValue/i
  }

  # Случай два
  for(i in (L+1):K){
    temporaryValue <- 0

    for(j in 1:L){
      temporaryValue = temporaryValue + x[j, i - j + 1]
    }

    timeSeriesResult[i] <- temporaryValue/L
  }

  # Случай три
  for(i in (K+1):N){
    temporaryValue <- 0

    for(j in (i - K + 1):L){
      temporaryValue = temporaryValue + x[j, i - j + 1]
    }

    timeSeriesResult[i] <- temporaryValue/(N-i+1)
  }

  return(timeSeriesResult)
}

# Функция, возвращающая конечный ранг ряда в случае его существования
TimeSeriesFiniteRank <- function(timeSeries){
  
  N <- length(timeSeries)     # Длина ряда
  
  rnkCurr <- 0                # Ранг
  rnkList <- c()
  
  upperBound <- (N + N%%2)/2  # Верхняя граница проверки (до половины длины ряда)
  
  for(L in 2:upperBound){
    rnkStep <- qr(BuildTrajectoryMatrix(timeSeries, L))$rank 
    
    rnkList = c(rnkList, rnkStep)
    
    if(rnkStep >= rnkCurr) rnkCurr <- rnkStep
    else {
      print("Found a bad rank sequence: ")
      return(0)
    }
  }
  
  print(rnkList)
  
  return(rnkCurr)
}


# Создание экспоненциально-модулированного гармонического ряда
CreateExponentialTimeSeries <- function(A, alpha, freq, angle, N){
  timeSeries <- c()
  
  # Проверка на плохие случаи (частота, угол, длина ряда вне диапазона)
  if(N <= 0) stop("Error: N <= 0")
  if( freq > (1/2) || freq < 0) stop("Error: frequency is out of bounds")
  if(angle >= 2*pi || angle < 0) stop("Error: angle is out of bounds")
  
  # Построение временного ряда
  for(n in 0:(N-1)){
    timeSeries <- c(timeSeries, A*exp(alpha*n)*cos(2*pi*freq*n + angle))
  }
  
  return(timeSeries)
}


# Создание полиномиального ряда
CreatePolynomialTimeSeries <- function(coefficientVector, N){
  timeSeries <- c()
  
  # Проверка на корректность ввода вектора коэффициентов полинома
  if(typeof(coefficientVector) != "double" && typeof(coefficientVector) != "vector") stop("Error: wrong coefficient type")
  
  # Построение временного ряда
  for(i in 0:(N-1)){
    x <- 0
    
    for(j in 1:length(coefficientVector)){
      x = x + coefficientVector[j]*i^(j-1)
    }
    
    timeSeries <- c(timeSeries, x)
  }
  
  return(timeSeries)
}


# Создание полиномиального ряда с отрицательными степенями
CreateReversePolynomialTimeSeries <- function(coefficientVector, N){
  timeSeries <- c()
  
  # Проверка на корректность ввода вектора коэффициентов полинома
  if(typeof(coefficientVector) != "double" && typeof(coefficientVector) != "vector") stop("Error: wrong coefficient type")
  
  # Построение временного ряда
  timeSeries <- c(timeSeries, coefficientVector[1])
  
  for(i in 1:(N-1)){
    x <- 0
    
    for(j in 1:length(coefficientVector)){
      x = x + coefficientVector[j]*i^(1-j)
    }
    
    timeSeries <- c(timeSeries, x)
  }
  
  return(timeSeries)
}

# Создание временного ряда от степенного ряда
CreatePowerTimeSeries <- function(coefficientVector, x, x0, N, Reverse = FALSE){
  timeSeries <- c()
  
  # Проверка на корректность ввода вектора коэффициентов полинома
  if(typeof(coefficientVector) != "double" && typeof(coefficientVector) != "vector") stop("Error: wrong coefficient type")
  
  # Построение временного ряда
  if(Reverse){
    for(i in 0:(N-1)){
      xResult <- coefficientVector[i]*(x-x0)^(-i)
    
      timeSeries <- c(timeSeries, xResult)  
    }
  }
  else{
    for(i in 0:(N-1)){
      xResult <- coefficientVector[i]*(x - x0)^i
      
      timeSeries <- c(timeSeries, xResult)
    }
  }
  return(timeSeries)
}



# Создание логарифмического ряда
CreateLogarithmicTimeSeries <- function(A, logBase = exp(1), coefficientVector, N){
  timeSeries <- c()
  
  
  # Проверка на корректность ввода вектора коэффициентов полинома
  if(typeof(coefficientVector) != "double" && typeof(coefficientVector) != "vector") stop("Error: wrong coefficient type")
  
  # Построение временного ряда
  for(i in 0:(N-1)){
    x <- 0
    
    for(j in 1:length(coefficientVector)){
      x = x + coefficientVector[j]*i^(j-1)
    }
    
    x = A*log(x, logBase)
    
    timeSeries <- c(timeSeries, x)
  }
  
  return(timeSeries)
}






###############################################################################
###############################################################################
###############################################################################

#
#
#
# Часть с использованием пакета Rssa 

library(Rssa)

test<-ssa(timeSeries)

MTS

timeSeries

# Проверка метода диагонального усреднения на траекторной матрице
isTRUE(all.equal(DiagonalAveraging(MTS), test$ecall$x))

TimeSeriesFiniteRank(test$ecall$x)


 
# Денис, следующие шаги:
#   1. сгенерировать разные ряды, с шумом и без, 
#      и продемонстрировать на них понятия сильной и/или слабой разделимости, 
#      а также их отсутствия со ссылками на теорию (необходимую теорию привести в отчете).
# 
#   2. взять реальный ряд и разложить его на тренд, периодику и шум, 
#      объясняя свои действия со ссылками на теорию. 
#      Реальный ряд можно взять отсюда — весь или какую-то последнюю часть. 
#      Это ряд температур по СПб с 1805 года, по месяцам.
#
# НЭ


set.seed(2023)


###############################################################################
###############################################################################
###############################################################################



# Задача 1.


# Наблюдение 1. 
# Поскольку каждый вид временного ряда, рассматриваемый при построении другого ряда,
# имеет свой базис (пусть их ранги будут r1, r2, ..., rk; N - длина ряда), то их линейная комбинация будет
#
# 1. Рядом конечного ранга R
# 2. R = min{r1+r2+...+rk, N %/% 2 + N%%2}


# Пример 1. Сильная и слабая разделимости
# Созданные ряды удовлетворяют условию слабой разделимости (см. предложение 2.1., стр. 14), однако
# разделимость может быть как сильной, так и слабой, в зависимости от параметра.

# Рассмотрим периодический и константный ряды. Для них существуют параметры функций
# и параметры метода L и K = N - L + 1, при которых они разделимы.

######
# Денис, здравствуйте!
# По тому, что вы назвали теоретическими примерами. 
# У вас траекторные матрицы почему-то не ганкелевы, а транспонированные.
# Вообще, предполагается демонстрация в R результатов с помощью rssa. 
# Также, идентификации нужно проводить на основе картинок 
# с собственными векторами и матрице взвешенных корреляций 
# и рисовать восстановленные ряды, причём тренд на фоне ряда. 
# Нужно знать, сколько компонент сингулярного разложения 
# какой компоненте ряда соответствует.
# 
# По реальному ряда - то же самое. 
# Где построенное разложение? 
# Сколько компонент может относиться к сезонное компоненте с периодом 12?
#   
#   НЭ
######


# Возьмём периодической ряд со значением ряда
#
#   f_n = 2*cos(pi*n/2) 
#
#   0 <= n <= 6
#
PeriodicTS <- CreateExponentialTimeSeries(2, 0, 1/4, 0, 7)



# При SVD получим 
#
# сингулярное число кратности два со значением 4.
#
svd(BuildTrajectoryMatrix(PeriodicTS, 4))


# Возьмём константный ряд со значением ряда
#
#   f_n = 1
# 
#   0 <= n <= 6
#
ConstTS <- rep(1, 7)

# При SVD получим
#
# сингулярное число со значением 4.
#
svd(BuildTrajectoryMatrix(ConstTS, 4))



# Построив временный ряд из их суммы 
#
#
#
TSWOutNoise <- PeriodicTS + ConstTS
SSAWOutNoise <- ssa(TSWOutNoise)
# В ходе SVD получилось
#
# три сингулярных числа со значением 4, которые нельзя однозначно разделить между собой
#
m <- svd(BuildTrajectoryMatrix(TSWOutNoise, 4))
TimeSeriesFiniteRank(TSWOutNoise)

plot(m$d,
     main = "Component norms",
     type ="o",
     ylab = "norms",
     col = "blue",
     pch = 16,
     cex = 0.6,
     las = 1,
)
grid(lty="dotted")

# При добавление белого шума значения сингулярных чисел не совпадают друг с другом
#
# Можно заметить возможность выделения тренда (константного ряда), периодики (ряда с косинусом) и шума (с самым низким сингулярным числом)
#
TSWNoise <- TSWOutNoise + rnorm(7, sd = 0.5)
SSAWNoise <- ssa(TSWNoise)
TimeSeriesFiniteRank(TSWNoise)

plot(SSAWNoise)




# Пример 2. Отсутствие разделимости
# В случае, когда не выполняется слабая разделимость, представление временной ряд в виде суммы нескольких
# компонент ряда является невозможным.

# Рассмотрим на простом примере:

# Пусть дано два константных ряда. Если мы предполагаем, что они, по крайней мере, слабо разделимы, то
#
# по предложению 2.1, скалярное произведение произвольных отрезков длины L и K двух рядов должно быть равно нулю,
# другими словами, биортогональный базис первого ряда должен быть ортогонален биортогональному базису второго ряда,
# поскольку все элементы ряда образованы некоторым биортогональным базисом сингулярного значения 
#

ConstTS_One <- rep(2, 10)

ConstTS_Two <- rep(3, 10)

# Взяв произвольную длину окна 1 < L < 10 
#
L <- 6
K <- 10 - L + 1

ConstTSValue <- c(ConstTS_One[2:(1+L)]%*%ConstTS_Two[4:(3+L)], ConstTS_One[1:K]%*%ConstTS_Two[5:(4+K)]) 
# видим, что значения скалярное произведение любого отрезка ряда = 6L или 6K != 0.
# Следовательно, константные ряды не могут быть отделимы друг от друга


# Конец задачи 1.


###############################################################################
###############################################################################
###############################################################################


# Задача 2.

# При выборе длины окна [4.2.2, с.42], что, хотя и число сингулярных значений, скорее всего будет небольшим
# в сравнение с самой длиной временного ряда, следует брать L как можно ближе к половине,
# чтобы достичь лучшей разделимости

spData <- read.table("SPData.txt", skip=5, col.names=c("Индекс ВМО", "Год", "Январь",
                                                       "Февраль", "Март", "Апрель",
                                                       "Май", "Июнь", "Июль", "Август",
                                                       "Сентябрь", "Октябрь", "Ноябрь",
                                                       "Декабрь")) 


spDataVector <- scan("SPData.txt", skip = 5)
spDataVector <- spDataVector[!spDataVector %in% c(26063, 1805:2021)]
mspSSA <- ssa(spDataVector, L = 1296)

svd(mspData)

plot(mspSSA)

summary(mspSSA)

# Исходя из значений норм компонентов, можно предположить, что
# у рассматриваемого временного ряда в качестве тренда выступают
# экспоненциально-модулированный гармонический ряд (ET1,2) и экспоненциальный ряд (ET3).
# 
# В качестве периодик можно выделить следующие:
# ET4,5; ET6,7; ET8,9; ET10,11; ET12,13; ET14,15; ET16,17; ET18,19;
# ET20,21; ET22,23; ET24,25; ET27, 28; ET30, 31
# То есть, ET4-25; ET27,28; ET30,31;


r <- reconstruct(mspSSA, groups = list(Trend = c(1, 2),
                                  Seasonality = c(3:7))) # Reconstruct into 2 series
plot(r, add.original = TRUE)  # Plot the reconstruction


mspSSA <- ssa(spDataVector, kind = "mssa")
r <- reconstruct(mspSSA, groups = list(Trend = c(1,2)))
plot(r, plot.method = "xyplot", add.residuals = FALSE,
     superpose = TRUE, auto.key = list(columns = 2))
# Trend forecast
fTrend <- rforecast(mspSSA, groups = list(Trend = c(1, 2)),
               len = 50, only.new = FALSE)

fSeason <- rforecast(mspSSA, groups = list(Seasonality = c(3:7)), 
                     len = 50, only.new = FALSE)


# Конец задачи 2.

###############################################################################
###############################################################################
###############################################################################




# Наблюдение 2.
# Изменение ранга при умножении элементов двух рядов конечного ранга:
# Пусть один ряд (1) имеет ранг r1, а второй (2) - r2, с длиной N (r1, r2 << N).
# Тогда, если
#
# 1. (1) и (2) - полиномы, то r12 = r1 + r2 - 1, т.е, степень нового полинома
# 2. (1) - экспоненциально-модулированный гармонический ряд
#     и (2) - полином, то r12 = r1*r2, так как базисы не пересекаются 
# 3. (1) и (2) - экспоненциально-модулированные гармонические ряды, то,
# разложив произведение в сумму и положив w1, w2 частотами (1), (2) соответственно,
# рассмотрим следующие случаи:
#
# 3.1. если их частоты совпадают и не равны 1/2 или 0 -> ранг 3.
# 3.2. если сумма частот равна 1/2 (w1 != 0, 1/2; w2 != 0, 1/2) -> ранг 3.
# 3.3. если w1 = 0, 1/2, или w2 = 0, 1/2 -> ранг 2.
# 3.4. если и w1 = 0 или 1/2 и w2 = 0 или 1/2 -> ранг 1.
# 3.5. иначе, ранг 4.
#
#
# 4. (1) - логарифмический ряд от полинома, конечный ранг которого зависит от 
#     коэффициентов полинома



# 1. +

PolyTS_One <- CreatePolynomialTimeSeries(c(1, 2, 1), 20)
TimeSeriesFiniteRank(PolyTS_One)    # r1 = 3

svd(BuildTrajectoryMatrix(PolyTS_One, 10))

PolyTS_Two <- CreatePolynomialTimeSeries(c(3, 5), 20)
TimeSeriesFiniteRank(PolyTS_Two)    # r2 = 2

PolyTS_Three <- PolyTS_One*PolyTS_Two
TimeSeriesFiniteRank(PolyTS_Three)  # r3 = 4


# 2. +

PeriTS_One <- CreateExponentialTimeSeries(1, 1, 1/4, 0, 20)
TimeSeriesFiniteRank(PeriTS_One)        # r1 = 2

svd(BuildTrajectoryMatrix(PeriTS_One, 10))

PolyTS_Two <- CreatePolynomialTimeSeries(c(1, 3, 5), 20)
TimeSeriesFiniteRank(PolyTS_Two)        # r2 = 3

PeriPolyTS_Three <- PeriTS_One*PolyTS_Two
TimeSeriesFiniteRank(PeriPolyTS_Three)  # r12 = 6


# 3. +

PeriTS_One <- CreateExponentialTimeSeries(1, 0, 1/6, 0, 20)
TimeSeriesFiniteRank(PeriTS_One)    # r1 = 2

PeriTS_Two <- CreateExponentialTimeSeries(1, 0, 1/3, 0, 20)
TimeSeriesFiniteRank(PeriTS_Two)    # r2 = 2

PeriTS_Three <- PeriTS_One*PeriTS_Two
TimeSeriesFiniteRank(PeriTS_Three)  # r12 = 3


# 4. ???

LogTS_One <- CreateLogarithmicTimeSeries(1, exp(1), c(1, 1), 20)
TimeSeriesFiniteRank(LogTS_One) # ???

# 5.

PowTS_One <- CreatePowerTimeSeries(rep(2, 20), 3, 0, 20)
TimeSeriesFiniteRank(PowTS_One)



######
# Денис, здравствуйте!
# По тому, что вы назвали теоретическими примерами. 
# У вас траекторные матрицы почему-то не ганкелевы, а транспонированные.
# Вообще, предполагается демонстрация в R результатов с помощью rssa. 
# Также, идентификации нужно проводить на основе картинок 
# с собственными векторами и матрице взвешенных корреляций 
# и рисовать восстановленные ряды, причём тренд на фоне ряда. 
# Нужно знать, сколько компонент сингулярного разложения 
# какой компоненте ряда соответствует.
# 
# По реальному ряда - то же самое. 
# Где построенное разложение? 
# Сколько компонент может относиться к сезонное компоненте с периодом 12?
#   
#   НЭ
######




# ***Example of autossa

ss <- ssa(spDataVector, L = 1296)
plot(ss, type = "vectors", idx = 1:18)
plot(ss, type = "vectors", vectors = "factor", idx = 1:18)
plot(ss, type = "series", groups = 1:18)

g1 <- grouping.auto(ss, base = "series", freq.bins = list(0.005), threshold = 0.80)
g2 <- grouping.auto(ss, base = "eigen", freq.bins = 2, threshold = 0)
g3 <- grouping.auto(ss, base = "factor", freq.bins = list(c(0.1), c(0.1, 0.2)), 
                    threshold = 0, method = "linear")
g4 <- grouping.auto(ss, freq.bins = c(0.1, 0.2), threshold = 0)

g <- grouping.auto(ss, freq.bins = 8, threshold = 0)
plot(reconstruct(ss, groups = g))
plot(g)

g <- grouping.auto(ss, freq.bins = list(0.1, 0.2, 0.3, 0.4, 0.5), threshold = 0.95)
plot(reconstruct(ss, groups = g))
plot(g)


# ***Example of bforecast

# Decompose 'co2' series with default parameters
s <- ssa(co2)
# Produce 24 forecasted values and confidence bounds of the series using
# the first 3 eigentriples as a base space for the forecast.

f <- bforecast(s, groups = list(1:3), len = 24, R = 50)
matplot(f, col = c("black", "red", "red"), type='l')


# ***Example of Cadzow

# Decompose co2 series with default parameters
s <- ssa(co2)
# Now make rank 3 approximation using the Cadzow iterations
F <- cadzow(s, rank = 3, tol = 1e-10)
library(lattice)
xyplot(cbind(Original = co2, Cadzow = F), superpose = TRUE)
# All but the first 3 eigenvalues are close to 0
plot(ssa(F))

# Compare with SSA reconstruction
F <- cadzow(s, rank = 3, maxiter = 1, correct = FALSE)
Fr <- reconstruct(s, groups = list(1:3))$F1
print(max(abs(F - Fr)))

# Cadzow with and without weights
set.seed(3)
N <- 60
L <- 30
K <- N - L + 1
alpha <- 0.1

sigma <- 0.1
signal <- cos(2*pi * seq_len(N) / 10)
x <- signal + rnorm(N, sd = sigma)

weights <- rep(alpha, K)
weights[seq(1, K, L)] <- 1
salpha <- ssa(x, L = L,
              column.oblique = "identity",
              row.oblique = weights)
calpha <- cadzow(salpha, rank = 2)

cz <- cadzow(ssa(x, L = L), rank = 2)

print(mean((cz - signal)^2))
print(mean((calpha - signal)^2))


# ***Example of calcv

# Decompose 'co2' series with default parameters
s <- ssa(co2)
# Calculate the 5th factor vector
v <- calc.v(s, 5)


# ***Example of clone

# Decompose 'co2' series with default parameters
s <- ssa(co2);
# Perform 'normal copy' of SSA object
s1 <- s;
# Perform 'deep copy' of SSA object
s2 <- clone(s);
# Add some data to 's'
reconstruct(s);
# Now 's1' also contains this data, but 's2' - not
summary(s1);
summary(s2);

# ***Example of clplot
clplot(s)


# ***Example of clusterify

# Decompose 'co2' series with default parameters
s <- ssa(co2)
# Form 3 series from the initial 6 ones:
lllst <- grouping.auto(s, grouping.method = "wcor",
                     groups = 1:6, nclust=3)
# Automatic grouping:
print(lst)
plot(lst)
# Check separability
w <- wcor(s, groups = lst)
plot(w)

# ***Example of decompose

# Decompose 'co2' series with default parameters and decomposition turned off.
s <- ssa(co2, force.decompose = FALSE, svd.method = "nutrlan")
# Perform the decomposition
decompose(s, neig = 50)
# Continue the decomposition
decompose(s, neig = 100)


# ***Example of EOSSA

# Separability of three finite-dimensional series, EOSSA vs Basic SSA
N <- 150
L <- 70
omega1 <- 0.065
omega2 <- 0.07
omega3 <- 0.02
sigma <- 0.5

F1.real <- 2*sin(2*pi*omega1*(1:N))
F2.real <- 4*sin(2*pi*omega2*(1:N))
F3.real <- sin(2*pi*omega3*(1:N))

noise <- rnorm(N, sd = sigma)
F <- F1.real + F2.real + F3.real + noise

ss <- ssa(F, L)
eoss <- eossa(ss, nested.groups = list(1:2, 3:4, 5:6), k = 3)

print(eoss)

plot(ss, type = "series", groups = list(1:2, 3:4, 5:6))
plot(eoss, type = "series", groups = eoss$iossa.groups)

plot(reconstruct(ss,
                 groups = list(1:2, 3:4, 5:6)),
     add.residuals = TRUE, plot.method = "xyplot", main = "",
     xlab = "")

plot(reconstruct(eoss, groups = list(1:2, 3:4, 5:6)),
     add.residuals = TRUE, plot.method = "xyplot", main = "",
     xlab = "")

plot(reconstruct(ss,
                 groups = list(Reconstructed = 1:6, F1 = 1:2, F2 = 3:4, F3 = 5:6)),
     add.residuals = TRUE, plot.method = "xyplot", main = "",
     xlab = "")

plot(reconstruct(eoss,
                 groups = list(Reconstructed = 1:6, F1 = 1:2, F2 = 3:4, F3 = 5:6)),
     add.residuals = TRUE, plot.method = "xyplot", main = "",
     xlab = "")

rec.ideal <- reconstruct(ss,
                         groups = list(Signal = 1:6, F1 = 1:2, F2 = 3:4, F3 = 5:6))
rec.ideal$Signal <- F1.real + F2.real + F3.real
rec.ideal$F1 <- F2.real
rec.ideal$F2 <- F1.real
rec.ideal$F3 <- F3.real

plot(rec.ideal,
     add.residuals = TRUE, plot.method = "xyplot", main = "",
     xlab = "")

# Real-life example (co2), EOSSA vs Basic SSA
sigma <- 0.05 
ss <- ssa(co2)
plot(ss, type = "vector")
eoss <- eossa(ss, 1:6, k = 4)
eoss$iossa.groups

plot(eoss)
rec <- reconstruct(eoss, groups = eoss$iossa.groups)
plot(rec)

plot(reconstruct(ss,
                 groups = list(ET1 = 1,ET2 = 2,ET3 = 3,ET4 = 4,ET5 = 5,ET6 = 6)),
     add.residuals = TRUE, plot.method = "xyplot", main = "",
     xlab = "")

plot(reconstruct(eoss,
                 groups = eoss$iossa.groups),
     add.residuals = TRUE, plot.method = "xyplot", main = "",
     xlab = "")

# Sine wave with phase shift, EOSSA vs Basic SSA
omega1 <- 0.06
omega2 <- 0.07
sigma <- 0.25

F1.real <- sin(2*pi*omega1*(1:N))
F2.real <- sin(2*pi*omega2*(1:N))
v <- c(F1.real,  F2.real)
v <- v + rnorm(v, sd = sigma)
# v <- c(F1.real,  F2.real)

ss <- ssa(v, L = 35)

eoss <- eossa(ss, 1:4, 2)
ioss <- iossa(ss, list(1:2, 3:4))

plot(reconstruct(eoss, groups = eoss$iossa.groups))

plot(reconstruct(eoss,
                 groups = eoss$iossa.groups), plot.method = "xyplot", main = "",
     xlab = "")

plot(reconstruct(ss, groups = list(1:2, 3:4)),
     plot.method = "xyplot",
     main = "", xlab = "")
plot(reconstruct(ss, groups = list(1,2, 3,4)),
     plot.method = "xyplot",
     main = "", xlab = "")


# ***Example of forecast

s <- ssa(co2)
# Calculate 24-point forecast using first 6 components as a base
f <- forecast(s, groups = list(1:6), method = "recurrent", bootstrap = TRUE, len = 24, R = 10)

# Plot the result including the last 24 points of the series
plot(f, include = 24, shadecols = "green", type = "l")
# Use of predict() for prediction
p <- predict(s, groups = list(1:6), method = "recurrent", len = 24)
# Simple plotting
plot(p, ylab = "Forecasteed Values")


# ***Example of FOSSA

# Separation of two mixed sine-waves with equal amplitudes
N <- 150
L <- 70
omega1 <- 1/15
omega2 <- 1/10

v <- sin(2*pi*omega1 * (1:N)) + sin(2*pi*omega2 * (1:N))
s <- ssa(v, L)
fs <- fossa(s, nested.groups = 1:4, gamma = 100)

# Rssa does most of the plots via lattice
ws <- plot(wcor(s, groups = 1:4))
wfs <- plot(wcor(fs, groups = 1:4))
plot(ws, split = c(1, 1, 2, 1), more = TRUE)
plot(wfs, split = c(2, 1, 2, 1), more = FALSE)

opar <- par(mfrow = c(2, 1))
plot(reconstruct(s, groups = list(1:2, 3:4)))
plot(reconstruct(fs, groups = list(1:2, 3:4)))
par(opar)

# Real-life example: Australian Wine Sales

data(AustralianWine)
s <- ssa(AustralianWine[1:120, "Fortified"], L = 60)
fs <- fossa(s, nested.groups = list(6:7, 8:9, 10:11), gamma = 10)

plot(reconstruct(fs, groups = list(6:7, 8:9, 10:11)))
plot(wcor(s, groups = 6:11))
plot(wcor(fs, groups = 6:11))

# Real life example: improving of strong separability
data(USUnemployment)
unempl.male <- USUnemployment[, "MALE"]
s <- ssa(unempl.male)
fs <- fossa(s, nested.groups = 1:13, gamma = 1000)

# Comparison of reconstructions
rec <- reconstruct(s, groups = list(c(1:4, 7:11), c(5:6, 12:13)))
frec <- reconstruct(fs, groups <- list(5:13, 1:4))
# Trends
matplot(data.frame(frec$F1, rec$F1, unempl.male), type= 'l',
        col=c("red","blue","black"), lty=c(1,1,2))
# Seasonalities
matplot(data.frame(frec$F2, rec$F2), type = 'l', col=c("red","blue"), lty=c(1,1))

# W-cor matrices before and after FOSSA
ws <- plot(wcor(s, groups = 1:30), grid = 14)
wfs <- plot(wcor(fs, groups = 1:30), grid = 14)
plot(ws, split = c(1, 1, 2, 1), more = TRUE)
plot(wfs, split = c(2, 1, 2, 1), more = FALSE)

# Eigenvectors before and after FOSSA
plot(s, type = "vectors", idx = 1:13)
plot(fs, type = "vectors", idx = 1:13)

# 2D plots of periodic eigenvectors before and after FOSSA
plot(s, type = "paired", idx = c(5, 12))
plot(fs, type = "paired", idx = c(1, 3))

# Compare FOSSA with and without normalize
N <- 150
L <- 70
omega1 <- 1/15
omega2 <- 1/10

v <- 3*sin(2*pi*omega1 * (1:N)) + 2*sin(2*pi*omega2 * (1:N))
s <- ssa(v, L)
fs <- fossa(s, nested.groups = 1:4, gamma = 100)
fs.norm <- fossa(s, nested.groups = 1:4, gamma = 100, normalize = TRUE)
opar <- par(mfrow = c(2, 1))
plot(reconstruct(fs, groups = list(1:2, 3:4)))
plot(reconstruct(fs.norm, groups = list(1:2, 3:4)))
par(opar)

# 2D example
data(Mars)
s <- ssa(Mars)
plot(s, "vectors", idx = 1:50)
plot(s, "series", idx = 1:50)
fs <- fossa(s, nested.groups = 1:50, gamma = Inf)
plot(fs, "vectors", idx = 1:14)
plot(fs, "series", groups = 1:13)

# Filters example, extracting horizontal and vertical stripes
data(Mars)
s <- ssa(Mars)
fs.hor <- fossa(s, nested.groups = 1:50, gamma = Inf,
                filter = list(c(-1, 1), c(1)))
plot(fs.hor, "vectors", idx = 1:14)
plot(fs.hor, "series", groups = 1:13)
fs.ver <- fossa(s, nested.groups = 1:50, gamma = Inf,
                filter = list(c(1), c(-1, 1)))
plot(fs.ver, "vectors", idx = 1:14)
plot(fs.ver, "series", groups = 1:13)


# ***Example of Frobenius.cor

# Separation of two mixed sine-waves with equal amplitudes
N <- 150
L <- 70
omega1 <- 1/5
omega2 <- 1/10

v <- sin(2*pi*omega1 * (1:N)) + sin(2*pi*omega2 * (1:N))
s <- ssa(v, L)
fs <- fossa(s, nested.groups = 1:4, gamma = 100)

# Decomposition is F-orthogonal
plot(frobenius.cor(fs, groups = 1:4), main = "F-correlation matrix")

plot(wcor(s, groups = 1:4))
plot(wcor(fs, groups = 1:4))


# Separate two non-separable sine series with different amplitudes

N <- 150
L <- 70

omega1 <- 0.07
omega2 <- 0.0675

F <- 2*sin(2*pi*omega1 * (1:N)) + 2*sin(2*pi*omega2 * (1:N))
s <- ssa(F, L)
ios <- iossa(s, nested.groups = list(1:2, 3:4),
             kappa = NULL, maxiter = 1000, tol = 1e-5)

plot(reconstruct(ios, groups = ios$iossa.groups))
summary(ios)

# Decomposition is really oblique
plot(frobenius.cor(ios, groups = 1:4), main = "F-correlation matrix")

plot(wcor(ios, groups = 1:4))
plot(owcor(ios, groups = list(1:2, 3:4)), main = "Oblique W-correlation matrix")




data(USUnemployment)
unempl.male <- USUnemployment[, "MALE"]

s <- ssa(unempl.male)
ios <- iossa(s, nested.groups = list(c(1:4, 7:11), c(5:6, 12:13)))
summary(ios)

# W-cor matrix before IOSSA and w-cor matrix after it
plot(wcor(s, groups = 1:30))
plot(wcor(ios, groups = 1:30))

# Confirmation of the indicated max value in the above warning
plot(frobenius.cor(ios, groups = 1:30), main = "F-correlation matrix")


# ***Example of gapfill

# Produce series with gaps
F <- co2; F[100:200] <- NA
# Perform shaped SSA
s <- ssa(F, L = 72)
# Fill in gaps using the trend and 2 periodicty components
g <- gapfill(s, groups = list(1:6))
# Compare the result
plot(g)
lines(co2, col = "red")


# ***Example of Hankel

# Construct the Hankel trajectory matrix for 'co2' series
h <- new.hmat(co2, L = 10)
# Print number of columns and rows
print(hrows(h))
print(hcols(h))


# ***Example of hmatr

# Calculate H-matrix for co2 series
h <- hmatr(co2, L = 24)
# Plot the matrix
plot(h)


# ***Example of IOSSA

# Separate three non-separable sine series with different amplitudes
N <- 150
L <- 70

omega1 <- 0.05
omega2 <- 0.06
omega3 <- 0.07

F <- 4*sin(2*pi*omega1 * (1:N)) + 2*sin(2*pi*omega2 * (1:N)) + sin(2*pi*omega3 * (1:N))
s <- ssa(F, L)
ios <- iossa(s, nested.groups = list(1:2, 3:4, 5:6), kappa = NULL, maxiter = 100, tol = 1e-3)

plot(reconstruct(ios, groups = ios$iossa.groups))
summary(ios)


# Separate two non-separable sines with equal amplitudes
N <- 200
L <- 100
omega1 <- 0.07
omega2 <- 0.06

F <- sin(2*pi*omega1 * (1:N)) + sin(2*pi*omega2 * (1:N))
s <- ssa(F, L)

# Apply FOSSA and then IOSSA
fs <- fossa(s, nested.groups = 1:4)
ios <- iossa(fs, nested.groups = list(1:2, 3:4), maxiter = 100)
summary(ios)

opar <- par(mfrow = c(3, 1))
plot(reconstruct(s, groups = list(1:2, 3:4)))
plot(reconstruct(fs, groups = list(1:2, 3:4)))
plot(reconstruct(ios, groups = ios$iossa.groups))
par(opar)

wo <- plot(wcor(ios, groups = 1:4))
gwo <- plot(owcor(ios, groups = 1:4))
plot(wo, split = c(1, 1, 2, 1), more = TRUE)
plot(gwo, split = c(2, 1, 2, 1), more = FALSE)



data(USUnemployment)
unempl.male <- USUnemployment[, "MALE"]

s <- ssa(unempl.male)
ios <- iossa(s, nested.groups = list(c(1:4, 7:11), c(5:6, 12:13)))
summary(ios)

# Comparison of reconstructions
rec <- reconstruct(s, groups = list(c(1:4, 7:11), c(5:6, 12:13)))
iorec <- reconstruct(ios, groups <- ios$iossa.groups)
# Trends
matplot(data.frame(iorec$F1, rec$F1, unempl.male), type='l',
        col=c("red","blue","black"), lty=c(1,1,2))
# Seasonalities
matplot(data.frame(iorec$F2, rec$F2), type='l', col=c("red","blue"),lty=c(1,1))

# W-cor matrix before IOSSA and w-cor matrix after it
ws <- plot(wcor(s, groups = 1:30), grid = 14)
wios <- plot(wcor(ios, groups = 1:30), grid = 14)
plot(ws, split = c(1, 1, 2, 1), more = TRUE)
plot(wios, split = c(2, 1, 2, 1), more = FALSE)

# Eigenvectors before and after Iterative O-SSA
plot(s, type = "vectors", idx = 1:13)
plot(ios, type = "vectors", idx = 1:13)

# 2D plots of periodic eigenvectors before and after Iterative O-SSA
plot(s, type = "paired", idx = c(5, 12))
plot(ios, type = "paired", idx = c(10, 12), plot.contrib = FALSE)

data(AustralianWine)
Fortified <- AustralianWine[, "Fortified"]
s <- ssa(window(Fortified, start = 1982 + 5/12, end = 1986 + 5/12), L = 18)
ios <- iossa(s, nested.groups = list(trend = 1, 2:7),
             kappa = NULL,
             maxIter = 1)
fs <- fossa(s, nested.groups = 1:7, gamma = 1000)

rec.ssa <- reconstruct(s, groups = list(trend = 1, 2:7))
rec.iossa <- reconstruct(ios, groups = ios$iossa.groups);
rec.fossa <- reconstruct(fs, groups = list(trend = 7, 1:6))

Fort <- cbind(`Basic SSA trend` = rec.ssa$trend,
              `Iterative O-SSA trend` = rec.iossa$trend,
              `DerivSSA trend` = rec.fossa$trend,
              `Full series` = Fortified)

library(lattice)
xyplot(Fort, superpose = TRUE, col = c("red", "blue", "green4", "black"))



# Shaped 2D I. O-SSA separates finite rank fields exactly
mx1 <- outer(1:50, 1:50,
             function(i, j) exp(i/25 - j/20))
mx2 <- outer(1:50, 1:50,
             function(i, j) sin(2*pi * i/17) * cos(2*pi * j/7))

mask <- matrix(TRUE, 50, 50)
mask[23:25, 23:27] <- FALSE
mask[1:2, 1] <- FALSE
mask[50:49, 1] <- FALSE
mask[1:2, 50] <- FALSE

mx1[!mask] <- mx2[!mask] <- NA

s <- ssa(mx1 + mx2, kind = "2d-ssa", L = c(10, 10))
plot(reconstruct(s, groups = list(1, 2:5)))

ios <- iossa(s, nested.groups = list(1, 2:5), kappa = NULL)
plot(reconstruct(ios, groups = ios$iossa.groups))


# I. O-SSA for MSSA
N.A <- 150
N.B <- 120
L <- 40

omega1 <- 0.05
omega2 <- 0.055

tt.A <- 1:N.A
tt.B <- 1:N.B
F1 <- list(A = 2 * sin(2*pi * omega1 * tt.A), B = cos(2*pi * omega1 * tt.B))
F2 <- list(A = 1 * sin(2*pi * omega2 * tt.A), B = cos(2*pi * omega2 * tt.B))

F <- list(A = F1$A + F2$A, B = F1$B + F2$B)

s <- ssa(F, kind = "mssa")
plot(reconstruct(s, groups = list(1:2, 3:4)), plot.method = "xyplot")

ios <- iossa(s, nested.groups = list(1:2, 3:4), kappa = NULL)
plot(reconstruct(ios, groups = ios$iossa.groups), plot.method = "xyplot")
