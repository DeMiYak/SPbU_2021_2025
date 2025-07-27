x<-c(0.5,0.3,1.2)
a1<-0.7
a2<--0.3
N<-1000
sd<-0.5
for(i in 4:N){
  x[i] = a1*x[i-1]+a2*x[i-3]+rnorm(1,sd=sd)
}
x

y<-x[4:length(x)]
z1<-x[3:(length(x)-1)]
z2<-x[1:(length(x)-3)]
z3<-x[2:(length(x)-2)]
lm(y~0+z1+z2)

acf(x)

