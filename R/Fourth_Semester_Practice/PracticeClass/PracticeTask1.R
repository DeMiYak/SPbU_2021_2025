f <- function(x, y){
  exp(-x^2 - y^2) * x
}
f <- function(x){
  exp(-x[1]^2 - x[2]^2) * x[1]
}
x <- seq(-2, 2, length.out = 100)
y <- seq(-2, 2, length.out = 100)
grid <- expand.grid(x = x, y = rev(y))
grid[1:10,]

f.res <- f(grid$x, grid$y)
f.res[1:10]

z <- f.res
dim(f.res) <- c(length(x), length(y))

gradient_slide <- function(x0, y0, f, eps = 1e-5, alpha = 0.2){
  dx <- (f(x0+eps, y0) - f(x0, y0))/eps
  dy <- (f(x0, y0+eps) - f(x0, y0))/eps
  while(dist(c(x0 - (x1 <- x0 - dx*alpha), y0 - (y1 <- y0 - dy*alpha))) > 1e-2){
    arrows(x0, y0, x1, y1, length=0.05)
    x0 <- x1
    y0 <- y1
    dx <- (f(x0+eps, y0) - f(x0, y0))/eps
    dy <- (f(x0, y0+eps) - f(x0, y0))/eps
  }
}

contour(x, y, f.res)
gradient_slide(0.2, 0.4, f)


# gradientVector <- function(x, f, eps = 1e-6){
#   df <- c()
#   for(i in x){
#     df <- c(df, (f(xMod) - f(x))/eps)
#   }
}