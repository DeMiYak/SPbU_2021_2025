# x in [0, 10*pi], y = sin(x)
# y = f(x) = -(x-2*pi)*(x-3*pi), x in [2*pi, 3*pi]

x <- seq(0, 10*pi, 0.01)
y <- sin(x)

piStep <- round(pi*100)
piSegment <- (2*piStep+1):(3*piStep+1)
y[piSegment] <- -1*(x[piSegment]-2*pi)*(x[piSegment]-3*pi)

plot(x, y, type='l')

points(x[piSegment], y[piSegment], col='red', type='l')
