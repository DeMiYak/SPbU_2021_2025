# Функция генерации данных
model_y <- function(n, k_true, lambda_true, t) {
  # Генерация K ~ Poisson(t) + 1
  K <- rpois(n, t) + 1L
  # Генерация X из распределения Вейбулла
  X <- rweibull(n, shape = k_true, scale = lambda_true)
  # Генерация данных для каждого наблюдения
  lapply(1:n, function(i) {
    k_i <- K[i]
    X_i <- X[i]
    # Генерация внутренних точек интервалов
    T_inner <- sort(runif(k_i, 0, t))

    # Полные границы интервалов: 0 = T0 < T1 < ... < Tk < Tk+1 = Inf
    T_all <- c(0, T_inner, Inf)

    # Определение интервала, содержащего X
    j_i <- findInterval(X_i, T_all, left.open = TRUE)
    list(
      K = k_i,
      intervals = T_all,
      j = j_i
    )
  })
}

# Векторизованная функция логарифма правдоподобия
log_likelihood <- function(params, data) {
  k <- params[1]
  lambda <- params[2]

  # Извлечение границ интервалов
  T_left <- sapply(data, function(obs) obs$intervals[obs$j])
  T_right <- sapply(data, function(obs) obs$intervals[obs$j+1])

  # Векторизованные вычисления
  term1 <- exp(-(T_left/lambda)^k)
  term2 <- ifelse(is.infinite(T_right), 0, exp(-(T_right/lambda)^k))
  probs <- term1 - term2

  # Обработка некорректных значений
  probs <- pmax(probs, .Machine$double.eps)

  sum(log(probs))
}

# Поиск ОМП
find_MLE <- function(data, init_k = 1, init_lambda = 1, method="Nelder-Mead") {
  optim(
    par = c(init_k, init_lambda),
    fn = log_likelihood,
    data = data,
    control = list(fnscale = -1, maxit = 1000),
    method = method,
    lower = c(1e-6, 1e-6)
  )$par
}

# Построение профиля правдоподобия
profile_likelihood <- function(data, param_seq, fixed_param = "k") {
  profile <- sapply(param_seq, function(p) {
    if (fixed_param == "k") {
      optim(1, function(lambda) -log_likelihood(c(p, lambda), data),
            method = "Brent", lower = 1e-6, upper = 100)$value
    } else {
      optim(1, function(k) -log_likelihood(c(k, p), data),
            method = "Brent", lower = 1e-6, upper = 100)$value
    }
  })
  data.frame(param = param_seq, logLik = -profile)
}

# Расчет ширины доверительного интервала
calculate_ci_width <- function(profile) {
  max_loglik <- max(profile$logLik)
  cutoff <- max_loglik - qchisq(0.95, 1)/2
  ci <- range(profile$param[profile$logLik >= cutoff])
  diff(ci)
}

# Основной анализ
analyze_ci_scaling <- function(n_samples, true_k = 2, true_lambda = 3, t = 5) {
  results <- lapply(n_samples, function(n) {
    data <- model_y(n, true_k, true_lambda, t)
    mle <- find_MLE(data)

    # Профилирование для k
    k_seq <- seq(mle[1]*0.5, mle[1]*1.5, length.out = 50)
    profile_k <- profile_likelihood(data, k_seq, "k")

    # Профилирование для lambda
    lambda_seq <- seq(mle[2]*0.5, mle[2]*1.5, length.out = 50)
    profile_lambda <- profile_likelihood(data, lambda_seq, "lambda")

    data.frame(
      n = n,
      k_width = calculate_ci_width(profile_k),
      lambda_width = calculate_ci_width(profile_lambda)
    )
  })
  do.call(rbind, results)
}

# Запуск анализа
n_samples <- c(50, 100, 200, 500, 1000)
results <- analyze_ci_scaling(n_samples)

# Визуализация
library(ggplot2)
ggplot(results, aes(n, k_width)) +
  geom_point() +
  geom_smooth(method = "lm", formula = y ~ I(1/sqrt(x))) +
  labs(title = "Зависимость ширины ДИ для k от объема выборки",
       x = "Объем выборки", y = "Ширина ДИ")

ggplot(results, aes(n, lambda_width)) +
  geom_point() +
  geom_smooth(method = "lm", formula = y ~ I(1/sqrt(x))) +
  labs(title = "Зависимость ширины ДИ для lambda от объема выборки",
       x = "Объем выборки", y = "Ширина ДИ")

# Генерация данных
set.seed(123)
N<-1e5
method<-"Nelder-Mead"
test_data <- model_y(n = N, k_true = 1.3, lambda_true = 2.0, t = 5)

# Поиск оценок
param <- find_MLE(test_data, init_k = 1, init_lambda = 1, method = method)
# Вывод результатов
cat("Оценки параметров:\n",
    "k_hat =", round(param[1], 3),
    "\n lambda_hat =", round(param[2], 3))
