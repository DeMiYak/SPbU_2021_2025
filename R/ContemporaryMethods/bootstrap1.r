N <- 10
alpha <- 0.05
sigma <- 3
h0 <- 0


estim_by_modelling <- function(sigma1){
  x1 <- rnorm(N, 0, sigma1 * sigma)
  y1 <- rnorm(N, 0, sigma)
  stat <- var(x1) / var(y1)
  p_value <- 1 - pf(stat, length(x1) - 1, length(y1) - 1)
  as.integer(p_value < alpha)
}

sigma1 <- runif(1000, 1, 5)
mean(sapply(sigma1, estim_by_modelling))


x0 <- rnorm(N, 0, sigma)
y0 <- runif(N, -sqrt(12 * sigma^2)/2, sqrt(12 * sigma^2)/2)
estim_by_bootstrap <- function(sigma1){
  x1 <- sample(x0, length(x0), replace=TRUE) * sigma1
  y1 <- sample(y0, length(y0), replace=TRUE)
  stat <- var(x1) / var(y1)
  p_value <- 1 - pf(stat, length(x1) - 1, length(y1) - 1)
  as.integer(p_value < alpha)
}

mean(sapply(sigma1, estim_by_bootstrap))

