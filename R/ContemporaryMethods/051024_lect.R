# Моделирование

alpha<-0.05
n<-30
mean<-3
sigma<-1.44
c_alpha<-c(qnorm(alpha/2, mean, sigma), qnorm(1-alpha/2, mean, sigma))
x<-rnorm(n, mean, sigma)
t<-sqrt(n/sigma)*(mean(x)-mean)

M<-10
n_rep<-1000
mean_alt<-runif(n_rep, mean-M, mean+M)
# Сосчитать t и проверить на вхождение в доверительную область
x_sample<-lapply(mean_alt, function(x) {rnorm(n, x, sigma)})
x_sample_mean<-lapply(x_sample, mean)
x_sample_mean
x_sample_mean<-unlist(x_sample_mean)
t_alt<-sqrt(n/sigma)*(x_sample_mean-mean)
p_val_alt<-lapply(t_alt, function(x) 2*(1-pnorm(abs(x))))|>
  unlist()
p_val_alt
mean(p_val_alt<alpha)

# Bootstrap

M<-10
n_rep<-1000
mean_alt<-runif(n_rep, mean-M, mean+M)
mat_sample<-matrix(rnorm(n_rep*n, mean, sigma), nrow=n, byrow=TRUE)|>
  apply(MARGIN=1, function(x) x+runif(1, -M, M))
t_mat_alt<-apply(mat_sample, 1, function(x) sqrt(n/sigma)*(mean(x)-mean))
p_mat_val<-lapply(t_mat_alt, function(x) 2*(1-pnorm(abs(x))))|>unlist()
mean(p_mat_val<alpha)
