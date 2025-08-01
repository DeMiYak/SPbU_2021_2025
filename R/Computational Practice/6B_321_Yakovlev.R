# �������� ���������������-��������������� �������������� ����
CreateExponentialTimeSeries <- function(A, alpha, freq, angle, N){
  timeSeries <- c()
  
  # �������� �� ������ ������ (�������, ����, ����� ���� ��� ���������)
  if(N <= 0) stop("Error: N <= 0")
  if( freq > (1/2) || freq < 0) stop("Error: frequency is out of bounds")
  if(angle >= 2*pi || angle < 0) stop("Error: angle is out of bounds")
  
  # ���������� ���������� ����
  for(n in 0:(N-1)){
    timeSeries <- c(timeSeries, A*exp(alpha*n)*cos(2*pi*freq*n + angle))
  }
  
  return(timeSeries)
}


# �������� ��������������� ����
CreatePolynomialTimeSeries <- function(coefficientVector, N){
  timeSeries <- c()
  
  # �������� �� ������������ ����� ������� ������������� ��������
  if(typeof(coefficientVector) != "double" && typeof(coefficientVector) != "vector") stop("Error: wrong coefficient type")
  
  # ���������� ���������� ����
  for(i in 0:(N-1)){
    x <- 0
    
    for(j in 1:length(coefficientVector)){
      x = x + coefficientVector[j]*i^(j-1)
    }
    
    timeSeries <- c(timeSeries, x)
  }
  
  return(timeSeries)
}


### 0. ���������������� ����.

library(Rssa)
# ���������
N <- 200
n <- 9:N
L <- n%/%3
varphi <- pi/8
omega <- 1/4
tau <- 3
delta <- 1
# �������� ��������� ������� (������������ ���������� - 0, 1, 0, 0,...)
H <- CreatePolynomialTimeSeries(c(0,1), N)
# �������� �������������� ����
E <- CreateExponentialTimeSeries(tau,0,omega,varphi, N)
X <- H + delta*E


### 1. �������� ������� ������������ ������ �������������� ���� ��� $L = \lfloor N/3\rfloor$

# �������� ������� � ���������� ����� ���������� SSA
Xssa <- c()
# ���� ��� ������������ ������ �������������� ����
for(i in seq_along(n))
{
  tempssa <- ssa(X[1:n[i]], L[i])
  D <- reconstruct(tempssa, groups=1:2)
  A <- D$F1 + D$F2
  r <- max(abs(A-H[1:n[i]]))
  Xssa <- append(Xssa, r)
}


### 2. ����� ������� (�����������)
library(latex2exp)
plot_width <- 6
plot_height <- 4
cairo_pdf("MaxERS.pdf", width = plot_width, height = plot_height)
plot(n, Xssa, type="o", pch=16, cex=0.8, lwd=2, main = TeX(r"(������������ ������ �������������� ���� $L \sim N/3$)"),
     xlab = TeX(r"($N$)"), ylab="������������ ������")
grid()
dev.off()


cairo_pdf("MaxERSNo.pdf", width = plot_width, height = plot_height)
XN <- Xssa*n
plot(n, XN, type="o", pch=16, lwd=2,cex=0.8, cex.main = 0.9, main = TeX(r"(������������ ������ �������������� ���� $L \sim N/3$, ���������� �� $N$)"),
     xlab = TeX(r"($N$)"), ylab=TeX(r"(������������ ������, ���������� �� $N$)"))
grid()
dev.off()
