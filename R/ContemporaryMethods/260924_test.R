# 3.1-1
alpha<-0.02

x_1<-0.38
n_1<-10
sig_1<-0.02

x_2<-0.37
n_2<-9
sig_2<-0.01

sig<-sqrt(sig_2^2/n_2 + sig_1^2/n_1)
# Имеет нормальное распределение, так как известны дисперсии
z<-(x_1-x_2)/sig
c_gamma<-qnorm(alpha)
z
c_gamma
c_gamma<z

#3.1-3
alpha<-0.02

s_1<-4.3
n_1<-14
x_1<-27

s_2<-5.6
n_2<-10
x_2<-21

# Гипотеза H0: mu_1 = mu_2

s_p<-((n_1-1)*s_1^2+(n_2-1)*s_2^2)/(n_1 + n_2 - 2)
s<-sqrt(s_p^2/n_1+s_p^2/n_2)
t<-(x_1 - x_2)/s
t

c_gamma<-qnorm(1-alpha/2)
c_gamma

-c_gamma < t & t < c_gamma

#3.1-5
alpha<-0.05

n_1<-200
p_1<-0.15

n_2<-200
p_2<-0.21

c_gamma<-qnorm(1-alpha/2, df=n_1+n_2-1)
c_gamma

E<-c_gamma*sqrt(p_1*(1-p_1)/n_1 + p_2*(1-p_2)/n_2)
E
low<- p_1-p_2 - E
high<-p_1-p_2 + E
low
high
low < 0 & 0 < high


# 3.1-7
alpha<-0.10
n_pm<-10
pm<-c(63,72,85,97,82, 101, 73, 62, 58, 75)
n_comp<-10
comp<-c(68,80,95,93,80,106,82,78,65,83)
x_pm<-mean(pm)
sig_pm<-mean((pm-x_pm)^2)
sig_pm
x_comp<-mean(comp)
sig_comp<-mean((comp-x_comp)^2)
sig_comp

sig<-sqrt(sig_pm/n_pm + sig_comp/n_comp)
sig

t<-(x_1-x_2)/sig
t

c_gamma<-qt(1-alpha, df=9)
c_gamma

#3.2-1
alpha<-0.10
exp_dr<-c(125,36,19)
prob_dr<-c(0.74,0.23,0.03)

chisq.test(exp_dr,  p=prob_dr)
x_sq<-35.461
c_alpha_right<-qchisq(1-alpha/2, df=2)
c_alpha_right
c_alpha_left<-qchisq(alpha/2, df=2)
c_alpha_left

# 3.2-5
alpha<-0.01
n<-152

xrows<-as.matrix(c(45, 52, 55)/n)
xcols<-as.matrix(c(46,51,27,28)/n)

# Матрица теоретических частот и вероятностей
xtheor<-xcols%*%xrows*n
xprob<-xcols%*%xrows

xempir<-matrix(c(18,16,12,9,15,27,5,12,10,13,9,6), ncol=3, byrow=TRUE)

xempir
xempir<-as.vector(xempir)
xtheor
xtheor<-as.vector(xtheor)
xprob<-as.vector(xprob)
xprob

chisq<-sum((xempir-xprob*n)^2/(xprob*n))
chisq

c_alpha<-qchisq(1-alpha,df=6)
c_alpha

c_alpha>chisq

#3.2-6
alpha<-0.05
n<-222

xrows<-as.matrix(c(100, 74, 48)/n)
xcols<-as.matrix(c(44,82,64,32)/n)

# Матрица теоретических частот и вероятностей
xtheor<-xcols%*%xrows*n
xprob<-xcols%*%xrows

xempir<-matrix(c(16,25,3,44,23,15,31,15,18,9,11,12), ncol=3, byrow=TRUE)

xempir
xempir<-as.vector(xempir)
xtheor
xtheor<-as.vector(xtheor)
xprob<-as.vector(xprob)
xprob

chisq<-sum((xempir-xprob*n)^2/(xprob*n))
chisq

c_alpha<-qchisq(1-alpha,df=6)
c_alpha

c_alpha>chisq
c_alpha
