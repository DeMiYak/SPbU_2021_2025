# f(x) = e^(0.01x)sin(x), 0 <= x <= 2*pi
# 10*pi <= x <= 20*pi, symmetry reg. x = 10*pi
# Task: draw f(x) on [0, 20*pi], find global max and mark them in red.

x <- seq(0, 10*pi, 0.02)
f <- exp(0.01*x)*sin(x)
f <- c(f, rev(f))
x <- c(x, (x + 10*pi))
plot(x, f, type='l')
abline(v=10*pi, col="purple", lty=2)
which.max(f)
maximae <- which(f==max(f))

points(x[maximae], f[maximae], col="red", pch=16, cex=1)

object.size(f)


# x in [0, 10*pi], y = sin(x)
# y = f(x) = -(x-2*pi)*(x-3*pi), x in [2*pi, 3*pi]

x <- seq(0, 10*pi, 0.01)
y <- sin(x)

piStep <- round(pi*100)
piSegment <- (2*piStep+1):(3*piStep+1)
y[piSegment] <- -1*(x[piSegment]-2*pi)*(x[piSegment]-3*pi)

plot(x, y, type='l')

points(x[piSegment], y[piSegment], col='red', type='l')
