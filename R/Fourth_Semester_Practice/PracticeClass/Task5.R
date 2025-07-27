# Умножать матрицу смежности, пока число нулей не перестанет уменьшаться


library(igraph)

m <- matrix(
  c(
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0
  ),
  nrow = 10,
  ncol = 10,
  byrow = TRUE
)

m <- m+t(m)
diag(m) <- 1

zeroCountI <- length(m[m==0])
m <- m%*%m
zeroCountII <- length(m[m==0])
mCount <- 2
while(zeroCountI != zeroCountII){
  zeroCountI <- zeroCountII
  m <- m%*%m
  mCount <- mCount*2
  zeroCountII <- length(m[m==0])
}
  
message(paste("zeroI =", zeroCountI, "; zeroII =", zeroCountII, "; mCount =", mCount))
  
m[m!=0] <- 1
plot(graph_from_adjacency_matrix(m))

