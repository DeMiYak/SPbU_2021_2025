# 1.1-2

n = 10
x_mean <- 12
gamma<-0.99
s<-2
c_gamma<-qt((1-gamma)/2+gamma, n-1)

lower_bound<-x_mean-c_gamma*s/sqrt(n-1)
high_bound<-x_mean+c_gamma*s/sqrt(n-1)
lower_bound
high_bound

# 1.1-4
n=75
p_mean = 15/75
gamma<-0.90
c_gamma<-qnorm((1-gamma)/2+gamma)

lower_4 <- p_mean - c_gamma*sqrt(p_mean*(1-p_mean)/n)
high_4 <- p_mean + c_gamma*sqrt(p_mean*(1-p_mean)/n)
res_4 <- c(lower_4, high_4)
res_4
c_gamma

# 1.1-6
n=150
p_mean = 86/150
gamma<-0.95
c_gamma<-qnorm((1-gamma)/2+gamma)

lower_6 <- p_mean - c_gamma*sqrt(p_mean*(1-p_mean)/n)
high_6 <- p_mean + c_gamma*sqrt(p_mean*(1-p_mean)/n)
res_6 <- c(lower_6, high_6)
res_6
c_gamma

# 1.1-8
n=300
p_mean = 0.6
gamma<-0.95
c_gamma<-qnorm((1-gamma)/2+gamma)

lower_8 <- p_mean - c_gamma*sqrt(p_mean*(1-p_mean)/n)
high_8 <- p_mean + c_gamma*sqrt(p_mean*(1-p_mean)/n)
res_8 <- c(lower_8, high_8)
res_8
c_gamma

# 1.1-10

# 1.2-2
n=80
p_mean = 9/80
alpha=0.05

p_value<-pbinom(9 , size = 80, prob=p_mean)
p_value

# 1.2-4
E_0 <- 4800
s <- 800
n <- 25
x_mean <- 4235
alpha <- 0.1

t <- sqrt(n-1)*(x_mean-E_0)/s
t
c_alpha<-qt(1-alpha/2, 24)
c_alpha

abs(t)<c_alpha

# 1.2-6
n<-30
E_0<-60
sigma<-13.42
x_mean<-mean(c(72, 45, 36, 68, 69, 71, 
               57, 83, 26, 60, 72, 58, 
               87, 48, 60, 56, 64, 68, 
               42, 57, 57, 58, 63, 49, 
               73, 75, 42, 63))

t <- sqrt(n)*(x_mean - E_0)/sigma
alpha<-0.05
p_value<-pnorm(t)
p_value>alpha
