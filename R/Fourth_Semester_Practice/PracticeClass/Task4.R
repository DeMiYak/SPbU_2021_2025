# Linear Equations

x <- 1:4
y <- c(4, 5, 1, 4)

val <- c(x^0, x^1, x^2, x^3)

a <- t(matrix(
  val, 
  nrow=4, 
  ncol=4, 
  byrow = TRUE))

x_solve <- solve(a, y)

x_span <- seq(min(x), max(x), 0.01)

x_mat <- cbind(x_span^0, x_span^1, x_span^2, x_span^3)

f_span <- x_mat%*%x_solve

plot(x_span, f_span, type='l')

points(x, y, col='red', pch=16)