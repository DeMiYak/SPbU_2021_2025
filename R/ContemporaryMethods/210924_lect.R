n <- 10
iter<-10^3
lim<-2:100
days<-c(1:365)
# 1
compute_time<-0
resVec <- c()
for(k in lim){
  start<-Sys.time()
  resVal<-mean(replicate(iter, any(duplicated(sample(days, k, replace=TRUE)))))
  resVec<-c(resVec, resVal)
  compute_time <- compute_time + Sys.time() - start
}
resVec
compute_time

plot(lim, resVec)

# 2
n <- 10^3
M<-99
days<-c(1:365)
compute_time<-0
x<-sample(days, M*n, replace=TRUE)|>
  matrix(nrow = n)|>
  apply(1, function(x) {any(duplicated(x))})
x
compute_time

# 3. Picky Bride Problem
n<-1000
m<-30
k<-20
x<-rep(1:m, n)|>
  matrix(nrow=n, byrow=TRUE)|>
  apply(1, function(x) sample(x))
res<-apply(x, 2, findGroom)
mean(res, na.rm=TRUE)
findGroom<-function(x){
  bestF<-max(x[1:k])
  pos<-Position(function(x) x > bestF, x)
  x[pos]==m
}
mean(res, na.rm=TRUE)
rep(1:30)
