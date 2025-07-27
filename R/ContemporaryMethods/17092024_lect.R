a <- c(1,2,3)
a/sum(a)
mean(a>1)

# summary(table(...)) returns chisq, df, p-value
# Независимость случайных величин ~ p-value > 0.05
quantile(x<-rnorm(1001))

# 20 из 11 игр - выигранные (55%), нул-гипотеза (H0) - p>0.5
prop.test(11, 20, 0.5, alternative="greater")

# Тест на нормальность
shapiro.test(rchisq(100, 3))
shapiro.test(rnorm(100))

# Для дихотомий
library("tseries")
runs.test(rnorm(100))

x1 <- c(14, 10)
x2 <- c(30, 40)
prop.test(x1, x2, conf.level=0.95, alternative="greater")

# Для сравнения распределений: критерий Колмогорова-Смирнова
ks.test()


-3/sqrt(4^2/12+9^2/18)

pt(-2.718,11)

qf(0.95,19,19)

pt(-2.201, 11)
qnorm(0.005)
p<-107/180
p1<-0.65
p2<-0.55
n1<-80
n2<-100
z<-(p1-p2)/sqrt(p*(1-p)/n1+p*(1-p)/n2)
z

x<-c(28,32,15,14,38,43,19)
chisq.test(x)
