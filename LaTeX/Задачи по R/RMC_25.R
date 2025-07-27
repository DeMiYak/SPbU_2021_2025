# Вычисление многомерного интеграла
library(ggplot2)
# Вычисления константы C
calc_const<-function(p){
  1/(1-exp(-1)+p^(-1))
}

# Вычисление функции m
m <- function(x, t, c, p, con = calc_const(p)) {
  a <- numeric(length(x))
  # Vectorized calculations
  a[x <= 1 & t < c * x] <- x[x <= 1 & t < c * x]^(-p - 1) * exp(x[x <= 1 & t < c * x]) / con
  a[x > 1 & t < c * x] <- 1 / con
  a
}

# Вычисление кси (t)
xi<-function(n){
  abs(qnorm(runif(n), 0, 1/sqrt(2)))
}

# Вычисление эта (x)
eta<-function(n, p, con = calc_const(p)){
  beta<-runif(n)
  con<-con*(1-exp(-1))
  a<-numeric(n)
  alpha<-runif(n)
  a[beta<con]<- -log(1-(1-exp(-1))*alpha[beta<con])
  a[beta>=con]<- (1-alpha[beta>=con])^(-1/p)
  a
}

# Алгоритм вычисления интеграла методом Монте-Карло
MC_Integration <- function(c, p, n=10e4){
  if(c<=0||p<=0||p>=1){
    stop("Wrong values. Must be: c>0 and 0<p<1")
  }
  con<-calc_const(p)
  xi <- xi(n)
  eta <- eta(n, p, con)
  m <- m(eta, xi, c, p, con)
  # list(mean=mean(m), se = sd(m)/sqrt(n))
  m
}

Exact_Integration <- function(c, p){
  c^p/(sqrt(pi)*p)*gamma((1-p)/2)
}

#-----------------------------------------------#
#-----------------------------------------------#

# Параметры (0 < p < 1, c > 0, n > 0)
c<-2
p<-0.3
n<-1e8
# Создаем последовательности для каждого диапазона с разными шагами
seq_result <- c(
  seq(100, 1000, by = 100),        # 100-1000 с шагом 100
  seq(2000, 10000, by = 1000),     # 2000-10000 с шагом 1000
  seq(20000, 100000, by = 10000), # 20000-100000 с шагом 10000
  seq(2e5, 1e6, by = 1e5),        # 200000-1000000 с шагом 100000
  seq(2e6, 1e7, by = 1e6),         # 2,000,000-10,000,000 с шагом 1,000,000
  n
)

#-----------------------------------------------#
#-----------------------------------------------#

# Для доверительного интервала последовательности (по ЦПТ)
ex <- Exact_Integration(c, p)
mc <- MC_Integration(c,p,n)
mc_mean<- sapply(seq_result, function(x) mean(mc[1:x]))
mc_se<-sapply(seq_result, function(x) sd(mc[1:x])/sqrt(x))

gamma<-0.95
ce<-qnorm((1+gamma)/2)
lower<- mc_mean-ce*mc_se
upper<- mc_mean+ce*mc_se

df <- data.frame(SampleSize = seq_result, Mean = mc_mean, Lower = lower, Upper = upper)

ggplot(df, aes(x = SampleSize, y = Mean)) +
  geom_point() +
  geom_line(color="darkblue") +
  geom_ribbon(aes(ymin = lower, ymax=upper), alpha = 0.2, fill = "blue") +
  scale_x_log10() +
  labs(title = "Difference between Monte Carlo and Exact Integration (95% CI)",
       x = "Sample Size (log10 scale)",
       y = "MC")

#-----------------------------------------------#
#-----------------------------------------------#

# Для доверительного интервала для траектории (Винеровский процесс)
# Разбиение по сотым долям секунды (шаг h = 0.01)
ex<-Exact_Integration(c, p)
mc<-MC_Integration(c, p, n)
t<-seq(1000000, n, by = 1000000)/n
mc_sd<-sd(mc)
mc_sd_sqrt<-mc_sd*sqrt(n)
ntlow<-sapply(t, function(x) floor(n*x))
mc_mean<- sapply(ntlow, function(x) mean(mc[1:x]))

# Вычисление u*(t) из конспектов Романа Гученко 
a<-0.1
b<-3.15
ustar<-function(t){
  a + b*sqrt(t)
}

# Построение доверительного интервала с графиком
coef<-ustar(t)*mc_sd_sqrt/ntlow
diff<-mc_mean-ex
lower<-diff - coef
upper<- diff + coef
df_traj<-data.frame(TimeStamp=t, Values=mc_mean-ex, Lower = lower, Upper = upper)
ggplot(df_traj, aes(x = TimeStamp, y = Values)) +
  geom_point() +
  geom_line(color="darkblue") +
  geom_ribbon(aes(ymin = lower, ymax=upper), alpha = 0.2, fill = "blue") +
  labs(title = "Difference between Monte-Carlo and Exact Integration (95% CI)",
       x = "Sample Size",
       y = "MC - Exact")
