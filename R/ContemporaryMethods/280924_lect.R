n<-20
# x ~ w*N(a, sig^2) + (1-w)*U(M, N)
a<-2
sig<-4
w<-0.7
M<-12
N<-21

fun<-function(){
  alpha<-runif(1)
  if(alpha < w){
    rnorm(1, a, sig)
  }
  else{
    runif(1, M, N)
  }
}
x<-replicate(n, fun())

x_mean_th <- w*a + (1-w)*(M+N)/2
x_mean_th
t<-c()
for(i in 1:length(x)){
  t<-c(t, sd(x[-i]))
}
t
t_mean<-sd(t)
t_mean
var(t)
t.test(x, t)
t.test(x, mu = a)
sqrt(length(x))*(sd(x)-a)/sqrt(var(x))
t.test(t)
chisq.test(x, t)

x_var_th<-w*(sig+a^2) + (1-w)*(((M+N)/2)^2+(N-M)^2/12) - x_mean_th^2
x_var_th
x_mean_th
bias<-(n-1)*(t_mean - sd(x))
bias
