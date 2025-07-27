# Адаптивный метод отбора

library(ggplot2)
# Плотность распределения Бирнбаума-Саундерса
log_BS_pdf<-function(gamma){
  if(gamma <= 0){
    stop("Gamma must be positive")
  }
  function(x){
    a<-sqrt(x)
    b<-1/a
    log((a+b)/(2*gamma*x)*dnorm((a-b)/gamma)) 
  }
}

# Либо производная логарифма плотности, либо через разностное выражение
log_BS_pdf_deriv<-function(gamma){
  if(gamma <= 0){
    stop("Gamma must be positive")
  }
  function(x){
    -1/(2*x)*((x^2-1)/(gamma^2*x)+(x+3)/(x+1))
  }
}

# Функция-мажоранта g_M
envelope<-function(gamma, n){
  if(gamma<=0){
    stop("Gamma must be positive")
  }
  dots<-seq(0.1, 1, length.out=n)
  h<-log_BS_pdf(gamma)(dots)
  h_deriv<-log_BS_pdf_deriv(gamma)(dots)
  rb<-dots[n]
  z<-(h[2:n]-h[1:(n-1)]-dots[2:n]*h_deriv[2:n]+dots[1:(n-1)]*h_deriv[1:(n-1)])/(h_deriv[1:(n-1)]-h_deriv[2:n])
  gamma_coef<-(-1)/(2*gamma^2)
  function(x){
    idx<-findInterval(x, z)+1
    u<-x
    u[x>=rb]<-h[n] + (x[x>=rb]-rb)*gamma_coef
    u[x<rb]<-h[idx[x<rb]] + (x[x<rb]-dots[idx[x<rb]])*h_deriv[idx[x<rb]]
    u
  }
}
# Функция-миноранта g_m
squeeze<-function(gamma, n){
  if(gamma<=0){
    stop("Gamma must be positive")
  }
  dots<-seq(0.1, 1, length.out=n)
  h<-log_BS_pdf(gamma)(dots)
  function(x){
    idx<-findInterval(x, dots)
    crit<-idx==0|idx==n
    
    l<-x
    l[crit]<-(-Inf)
    l[!crit]<-((dots[idx[!crit]+1]-x[!crit])*h[idx[!crit]]+(x[!crit]-dots[idx[!crit]])*h[idx[!crit]+1])/(dots[idx[!crit]+1]-dots[idx[!crit]])
    l
  }
}

# Поля функции отбора
sampler_obj<-function(gamma, n){
  if(gamma<=0){
    stop("Gamma must be positive")
  }
  dots<-seq(0.1, 1, length.out=n)
  h<-log_BS_pdf(gamma)(dots)
  h_deriv<-log_BS_pdf_deriv(gamma)(dots)
  rb<-dots[n]
  z<-(h[2:n]-h[1:(n-1)]-dots[2:n]*h_deriv[2:n]+dots[1:(n-1)]*h_deriv[1:(n-1)])/(h_deriv[1:(n-1)]-h_deriv[2:n])
  gamma_coef<-(-1)/(2*gamma^2)
  # Проблема: пересчитать первый интеграл
  int_u<-c(exp(h[1])*(exp((z[1]-dots[1])*h_deriv[1])-exp(-dots[1]*h_deriv[1]))/h_deriv[1], # От -Inf до z_1
           exp(h[2:(n-1)]-dots[2:(n-1)]*h_deriv[2:(n-1)])*(exp(z[2:(n-1)]*h_deriv[2:(n-1)])-exp(z[1:(n-2)]*h_deriv[2:(n-1)]))/h_deriv[2:(n-1)], # Остальные случаи
           exp(h[n])*(1-exp((z[n-1]-rb)*h_deriv[n]))/h_deriv[n], # Между последним z и rb
           -exp(h[n])/gamma_coef # После rb
  )
  z_comp<-c(z, rb)
  
  list(dots=dots,
       h=h,
       h_deriv=h_deriv,
       rb=rb,
       z_comp=z_comp,
       gamma_coef=gamma_coef,
       int_u=int_u)
}

# Функция для подготовки основных функций
bundle<-function(gamma, n){
  list(g_M=envelope(gamma, n),
       g_m=squeeze(gamma, n),
       sam_obj=sampler_obj(gamma, n),
       log_pdf=log_BS_pdf(gamma),
       log_pdf_deriv=log_BS_pdf_deriv(gamma))
}

# Лишняя функция отбора
sampler<-function(sampler_obj){
  dots<-sampler_obj$dots
  h<-sampler_obj$h
  h_deriv<-sampler_obj$h_deriv
  rb<-sampler_obj$rb
  z_comp<-sampler_obj$z_comp
  gamma_coef<-sampler_obj$gamma_coef
  int_u<-sampler_obj$int_u
  function(x){
    idx<-findInterval(x, z_comp)+1
    u<-x
    u[x>=rb]<-h[n] + (x[x>=rb]-rb)*gamma_coef
    u[x<rb]<-h[idx[x<rb]] + (x[x<rb]-dots[idx[x<rb]])*h_deriv[idx[x<rb]]
    s<-exp(u)/int_u[idx]
    s
  }
}

# Функция генерации точек
rq <- function(sampler_obj, N) {
  # Нормируем интегралы
  sum_int_u <- sum(sampler_obj$int_u)
  probs <- sampler_obj$int_u / sum_int_u
  cum_probs <- cumsum(probs)
  len<-length(sampler_obj$z_comp)
  # Генерируем равномерные случайные числа
  U <- runif(N)
  
  # Определяем интервалы для каждого U
  idx <- findInterval(U, cum_probs, rightmost.closed = TRUE) + 1
  
  # Инициализируем вектор для результатов
  x <- numeric(N)
  
  # Обрабатываем каждый интервал
  for (i in seq_along(sampler_obj$int_u)) {
    mask <- (idx == i)
    if (sum(mask) == 0) next
    
    # Масштабируем U на (0,1) внутри интервала
    # Теоретически у U_scaled распределение U(0,1)
    # Практически - можно уменьшить число вызовов U(0,1) на один для каждой итерации
    U_scaled <- (U[mask] - c(0, cum_probs)[i]) / probs[i]
    
    if (i == 1) {
      # Интервал (-Inf, z_comp[1])
      lower <- -Inf
      upper <- sampler_obj$z_comp[1]
      # Параметры экспоненты: u = h[1] + (x - dots[1])*h_deriv[1]
      # s(x) = exp(u) / int_u[i] = exp(a*x + b)
      a <- sampler_obj$h_deriv[1]
      b <- sampler_obj$h[1] - sampler_obj$dots[1] * sampler_obj$h_deriv[1]
      # Обратная CDF: x = (log(a * int_u[i] * U + exp(a*lower + b)) - b)/a
      # Но lower = -Inf, поэтому упрощаем
      
      # Проблема: может принимать отрицательные значения (интеграл от -inf до z_1)
      # А должен быть от 0 до z_1
      x[mask] <- (log(a * sampler_obj$int_u[i] * U_scaled + exp(b)) - b) / a
    } else if (i <= len) {
      # Интервал [z_comp[i-1], z_comp[i])
      lower <- sampler_obj$z_comp[i-1]
      upper <- sampler_obj$z_comp[i]
      # Параметры экспоненты
      a <- sampler_obj$h_deriv[i]
      b <- sampler_obj$h[i] - sampler_obj$dots[i] * a
      # Обратная CDF
      x[mask] <- (log(a * sampler_obj$int_u[i] * U_scaled + exp(a * lower + b)) - b) / a
    } else {
      # Интервал [rb, Inf)
      lambda <- -sampler_obj$gamma_coef
      x[mask] <- sampler_obj$rb - log(1 - U_scaled) / lambda
    }
  }
  
  x
}

# Реализация отбора
rf<-function(pack, n)
{
  sam_obj<-pack$sam_obj
  g_M<-pack$g_M
  g_m<-pack$g_m
  h<-pack$log_pdf
  h_deriv<-pack$log_pdf_deriv
  out<-numeric(0)
  rejected<-1:n
  k<-length(rejected)
  while(k>0){
    candidates<-rq(sam_obj, k)    # Генерируем k значений
    out[rejected]<-candidates     # Присваиваем отвергнутые значения
    alpha<-runif(k)               # Генерируем k равномерных чисел
    # В rejected хранятся позиции, которые необходимо повторно проверить
    first_rejected<-exp(g_m(out[rejected])-g_M(out[rejected]))<=alpha
    rejected<-rejected[first_rejected]
    # Теперь, в rejected хранятся позиции, которые не прошли первую волну отбора
    # Если брать alpha[rejected], то можно выйти за массив, поэтому надо использовать
    # first_rejected - выбираем те alpha, которые не удовлетворили первой волне
    
    # Проблема здесь, но непонятно в чём
    second_rejected<-exp(h(out[rejected])-g_M(out[rejected]))<=(alpha[first_rejected])
    rejected<-rejected[second_rejected] # Длины отличаются
    k<-length(rejected)
  }
  out
}

n<-13
N<-1e7
seq(0.1, 1, length.out=n)
# Задание параметров
gamma<-1
step<-0.001
x<-seq(0.1, 2, by=step)
log_BS_gamma<-log_BS_pdf(gamma)
log_y<-log_BS_gamma(x)
# Построение графиков плотности
g_M<-envelope(gamma, n)
g_m<-squeeze(gamma, n)
sam_obj<-sampler_obj(gamma, n)
s_k<-sampler(sam_obj)
rr<-rq(sam_obj, N)
rr[is.na(rr)]
plot(x, s_k(x))
shr<-cumsum(s_k(x))*step
plot(x,shr)
plot(x,log_y,type="l",col="red")
lines(x, g_M(x),col="green")
lines(x, g_m(x), col="blue")

# Проверка функции отбора
pack<-bundle(gamma, n)
result<-rf(pack, N)

