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

BS_root<-function(gamma){
  a<- -2*(3*gamma^2-1)/(3*gamma^2)
  b_rad<- -27*gamma^12 - 54*gamma^10 + 18*gamma^8 - 8*gamma^6
  b_rad<- as.complex(b_rad)
  rad<-3*sqrt(6)*sqrt(b_rad)
  b_root<- (-135*gamma^6 + 108*gamma^4 - 36*gamma^2 + rad + 8)^(1/3)
  b<- b_root/(3*gamma^2)
  c<- -(-27*gamma^4 + 12*gamma^2 - 4)/(3*gamma^2*b_root)
  x<-a+b+c
  Re(x)
}

# Функция-мажоранта g_M
envelope<-function(gamma, dots){
  if(gamma<=0){
    stop("Gamma must be positive")
  }
  n<-length(dots)
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
squeeze<-function(gamma, dots){
  if(gamma<=0){
    stop("Gamma must be positive")
  }
  h<-log_BS_pdf(gamma)(dots)
  len<-length(dots)
  function(x){
    idx<-findInterval(x, dots)
    crit<-idx==0|idx==len
    
    l<-x
    l[crit]<-(-Inf)
    l[!crit]<-((dots[idx[!crit]+1]-x[!crit])*h[idx[!crit]]+(x[!crit]-dots[idx[!crit]])*h[idx[!crit]+1])/(dots[idx[!crit]+1]-dots[idx[!crit]])
    l
  }
}

# Поля функции отбора
sampler_obj<-function(gamma, dots){
  if(gamma<=0){
    stop("Gamma must be positive")
  }
  n<-length(dots)
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
bundle<-function(gamma, dots){
  list(g_M=envelope(gamma, dots),
       g_m=squeeze(gamma, dots),
       sam_obj=sampler_obj(gamma, dots))
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
rf_optimized <- function(starting_point, len, gamma, n, max_points = 100) {
  inflection_point <- BS_root(gamma)
  h <- log_BS_pdf(gamma)
  
  # Инициализация выходного массива и индексов
  out <- numeric(n)
  rejected <- 1:n
  k <- n
  x <- seq(starting_point, inflection_point, length.out = len)
  
  while(k > 0) {
    # Обновление конверта и squeeze
    pack <- bundle(gamma, x)
    candidates <- rq(pack$sam_obj, k)
    out[rejected] <- candidates
    
    # Векторизованные проверки
    alpha <- runif(k)
    current_values <- out[rejected]
    
    # Первая проверка (squeeze)
    g_m_vals <- pack$g_m(current_values)
    g_M_vals <- pack$g_M(current_values)
    first_check <- exp(g_m_vals - g_M_vals) <= alpha
    
    # Вторая проверка (точная плотность) только для неудавшихся
    second_check <- logical(k)
    if(any(!first_check)) {
      h_vals <- h(current_values[!first_check])
      second_check[!first_check] <- exp(h_vals - g_M_vals[!first_check]) <= alpha[!first_check]
    }
    
    # Обновление индексов отвергнутых
    new_rejected <- rejected[!(first_check | second_check)]
    
    # Обновление точек адаптации
    if(length(x) < max_points){
      accepted <- current_values[first_check | second_check]
      new_points <- accepted[accepted >= starting_point & 
                               accepted <= inflection_point & 
                               !is.na(accepted)]
      x <- sort(unique(c(x, new_points)))
      if(length(x) > max_points){
        x<-c(starting_point, sort(x)[2:(max_points-1)], inflection_point)
      }
    }
    
    # Подготовка к следующей итерации
    rejected <- new_rejected
    k <- length(rejected)
  }
  
  return(out)
}

rf_highspeed <- function(starting_point, k, gamma, n) {
  inflection_point <- BS_root(gamma)
  if (starting_point >= inflection_point) stop("starting_point must be less than inflection point")
  
  # Инициализация точек адаптации
  points <- sort(unique(c(
    starting_point,
    seq(starting_point, inflection_point, length.out = k + 2)
  )))
  
  log_f <- log_BS_pdf(gamma)
  slope_asymptote <- -1/(2*gamma^2)
  
  # Предварительные вычисления для быстрого обновления
  precompute_env <- function() {
    m <- length(points)
    x_left <- points[-m]
    x_right <- points[-1]
    n_segments <- length(x_left)
    
    # Секущие для верхней границы
    f_left <- sapply(x_left, log_f)
    f_right <- sapply(x_right, log_f)
    m_sec <- (f_right - f_left)/(x_right - x_left)
    c_sec <- f_left - m_sec*x_left
    
    # Касательные для нижней границы
    deriv_left <- sapply(x_left, log_BS_pdf_deriv(gamma))
    deriv_right <- sapply(x_right, log_BS_pdf_deriv(gamma))
    
    # Добавляем асимптотический сегмент
    list(
      segments = data.frame(
        a = c(x_left, inflection_point),
        b = c(x_right, Inf),
        m_upper = c(m_sec, slope_asymptote),
        c_upper = c(c_sec, log_f(inflection_point) - slope_asymptote*inflection_point),
        m_lower_left = c(deriv_left, NA),
        m_lower_right = c(deriv_right, NA)
      )
    )
  }
  
  env <- precompute_env()
  
  # Векторизованная генерация из верхней оболочки
  sample_env <- function(n) {
    probs <- with(env$segments, {
      integrals <- ifelse(is.infinite(b), 
                          -exp(c_upper)/m_upper,
                          (exp(m_upper*b + c_upper) - exp(m_upper*a + c_upper))/m_upper)
      pmax(integrals, 0)
    })
    probs <- probs/sum(probs)
    
    # Выбор сегментов
    idx <- sample.int(nrow(env$segments), n, replace = TRUE, prob = probs)
    seg <- env$segments[idx, ]
    
    # Генерация значений
    u <- runif(n)
    a <- seg$a
    b <- seg$b
    m <- seg$m_upper
    c <- seg$c_upper
    
    x <- ifelse(is.infinite(b),
                a - log(1 - u)/abs(m),
                log(exp(m*a)*(1 - u) + exp(m*b)*u)/m)
    
    list(x = x, log_env = m*x + c, seg_idx = idx)
  }
  
  # Векторизованная проверка условий
  check_acceptance <- function(x, log_env) {
    log_u <- log_env + log(runif(length(x)))
    
    # Быстрая проверка положения относительно точки перегиба
    left_mask <- x <= inflection_point
    
    # Инициализация принятых значений
    accepted <- logical(length(x))
    
    # Проверка squeeze для левой части
    if(any(left_mask)) {
      left_x <- x[left_mask]
      left_idx <- findInterval(left_x, points, rightmost.closed = TRUE)
      
      # Вычисление нижней границы
      m_lower <- pmax(env$segments$m_lower_left[left_idx], 
                      env$segments$m_lower_right[left_idx])
      c_lower <- log_f(points[left_idx]) - m_lower*points[left_idx]
      log_squeeze <- m_lower*left_x + c_lower
      
      squeeze_accept <- log_u[left_mask] <= log_squeeze
      accepted[left_mask] <- squeeze_accept
    }
    
    # Проверка плотности для оставшихся
    remaining <- !accepted
    if(any(remaining)) {
      log_fx <- sapply(x[remaining], log_f)
      accepted[remaining] <- log_u[remaining] <= log_fx
    }
    
    accepted
  }
  
  # Основной цикл генерации
  result <- numeric(n)
  generated <- 0
  
  while(generated < n) {
    batch_size <- min(1e5, n - generated)
    candidates <- sample_env(batch_size)
    accepted <- check_acceptance(candidates$x, candidates$log_env)
    
    # Сохранение результатов
    n_accepted <- sum(accepted)
    if(n_accepted > 0) {
      result[(generated + 1):(generated + n_accepted)] <- candidates$x[accepted]
      generated <- generated + n_accepted
    }
    
    # Адаптация оболочки
    new_points <- candidates$x[!accepted & candidates$x < inflection_point]
    if(length(new_points) > 0) {
      points <- sort(unique(c(points, new_points)))
      env <- precompute_env()
    }
  }
  
  result
}


st<-0.05
k<-10
gamma<-3
N<-1e7
system.time(x<-rf_optimized(st, k, gamma, N))
system.time(x<-rf_highspeed(st, k, gamma, 1e6))

# Проверка распределения

# Функция плотности BS
BS_pdf <- function(gamma) {
  function(x) {
    a <- sqrt(x)
    b <- 1/a
    (a + b) / (2 * gamma * x) * dnorm((a - b)/gamma)
  }
}

pdf_bs <- BS_pdf(gamma = gamma)

# Построение гистограммы
hist(x, breaks = 1000, freq = FALSE, main = "Histogram and Theoretical Density", xlab = "x")
curve(pdf_bs(x), add = TRUE, col = "red", lwd = 2)


# Задание параметров
gamma<-1
step<-0.001
x<-seq(0.1, 2, by=step)
log_BS_gamma<-log_BS_pdf(gamma)
log_y<-log_BS_gamma(x)
# Построение графиков плотности
g_M<-envelope(gamma, x)
g_m<-squeeze(gamma, x)
sam_obj<-sampler_obj(gamma, x)
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