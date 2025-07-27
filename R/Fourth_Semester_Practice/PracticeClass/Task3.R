# f(x) = int_{-inf}^x 1/sqrt(2*pi)*exp(-t^2/2) dt
# -4 <= x <= 4

# One.

x <- seq(-4, 4, 0.01)
f <- 1/sqrt(2*pi)*exp(-x^2/2)
sumf <- (f[1:800]+f[2:801])/2*0.01
intf <- cumsum(sumf)

plot(x, f, type='l')
plot(x[1:800], intf, type='l')

dif <- (intf[2:800] - intf[1:799])/0.01

plot(x[1:799], dif, type='l')
