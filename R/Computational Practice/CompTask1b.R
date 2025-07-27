library("rgl")
library("random")
maxNum = 2^31
randvec <- randomNumbers(n = 3000, min = 0, max = maxNum, col = 3)/maxNum 
plot3d(randvec)


randu <- function(v){
  return ((65539*v)%%(maxNum))
}

randuGenerator <- function(seed, n = 300, col = 3){
  if(n%%col != 0) stop("Cannot divide n by col")
  row = n/col
  randuMat <- matrix(nrow = row, ncol = col)
  for (i in 1:n){
  }
}

x <- 1
x <- randu(x)
x > 2^31

