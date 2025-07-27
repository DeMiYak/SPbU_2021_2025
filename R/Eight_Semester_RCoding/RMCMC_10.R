# Для распределения Лапласа, если нужно
library(VGAM)

# Реализация алгоритма Метрополиса-Гастингса с равномерным блужданием
metropolis_uniform <- function(n_iter, delta, start = 0) {
  chain <- numeric(n_iter)
  chain[1] <- start
  accept <- 0
  # Блуждание
  for (i in 2:n_iter) {
    current <- chain[i-1]
    proposal <- current + runif(1, -delta, delta)
    ratio <- dnorm(proposal) / dnorm(current)
    if (runif(1) < ratio) {
      chain[i] <- proposal
      accept <- accept + 1
    } else {
      chain[i] <- current
    }
  }
  acceptance_rate <- accept / (n_iter - 1)
  list(chain = chain, acceptance_rate = acceptance_rate)
}

# Реализация для распределения Коши
metropolis_cauchy <- function(n_iter, gamma, start = 0) {
  chain <- numeric(n_iter)
  chain[1] <- start
  accept <- 0
  for (i in 2:n_iter) {
    current <- chain[i-1]
    proposal <- current + rcauchy(1, scale = gamma)
    ratio <- dnorm(proposal) / dnorm(current)
    if (runif(1) < ratio) {
      chain[i] <- proposal
      accept <- accept + 1
    } else {
      chain[i] <- current
    }
  }
  acceptance_rate <- accept / (n_iter - 1)
  list(chain = chain, acceptance_rate = acceptance_rate)
}

# Реализация для распределения Лапласа
metropolis_laplace <- function(n_iter, lambda, start = 0) {
  chain <- numeric(n_iter)
  chain[1] <- start
  accept <- 0
  for (i in 2:n_iter) {
    current <- chain[i-1]
    proposal <- current + rlaplace(1, scale = lambda)
    ratio <- dnorm(proposal) / dnorm(current)
    if (runif(1) < ratio) {
      chain[i] <- proposal
      accept <- accept + 1
    } else {
      chain[i] <- current
    }
  }
  acceptance_rate <- accept / (n_iter - 1)
  list(chain = chain, acceptance_rate = acceptance_rate)
}

# Функция для подбора параметра методом бинарного поиска
find_parameter <- function(f, target, lower, upper, tol = 0.01, max_iter = 20) {
  for (i in 1:max_iter) {
    mid <- (lower + upper) / 2
    result <- f(mid)
    ar <- result$acceptance_rate
    if (ar > target) {
      lower <- mid
    } else {
      upper <- mid
    }
    if (abs(ar - target) < tol) break
  }
  list(parameter = mid, acceptance_rate = ar)
}

# Параметры симуляции
n_iter <- 100000
set.seed(123)

# 1. Исследование равномерного предложения при разных delta
deltas <- c(0.1, 1, 10)
results_unif <- lapply(deltas, function(d) metropolis_uniform(n_iter, d))
names(results_unif) <- deltas

# Автокорреляция первого порядка
acf_unif <- sapply(results_unif, function(res) acf(res$chain, plot = FALSE)$acf[2])

# Автокорреляция от соседних значений снижается с увеличением шага delta.
acf_unif

lapply(results_unif, function(res) acf(res$chain))

# 2. Сравнение с Коши и Лапласом (параметры по умолчанию)
result_cauchy <- metropolis_cauchy(n_iter, gamma = 1)
result_laplace <- metropolis_laplace(n_iter, lambda = 1)

acf_cauchy <- acf(result_cauchy$chain, plot = FALSE)$acf[2]
acf_laplace <- acf(result_laplace$chain, plot = FALSE)$acf[2]
acf(result_cauchy$chain)
acf(result_laplace$chain)
# 3. Подбор параметров для вероятности перехода ~0.25
# Для равномерного предложения
f_unif <- function(d) metropolis_uniform(n_iter, d)
param_unif <- find_parameter(f_unif, 0.25, 1, 10)

# Для Коши
f_cauchy <- function(g) metropolis_cauchy(n_iter, g)
param_cauchy <- find_parameter(f_cauchy, 0.25, 0.1, 5)

# Для Лапласа
f_laplace <- function(l) metropolis_laplace(n_iter, l)
param_laplace <- find_parameter(f_laplace, 0.25, 0.1, 5)

# Вывод результатов
cat("Равномерное блуждание:\n")
print(data.frame(delta = deltas, 
                 AcceptanceRate = sapply(results_unif, function(x) x$acceptance_rate),
                 Autocorrelation = acf_unif))

cat("\nКоши (gamma=1): Acceptance Rate =", result_cauchy$acceptance_rate,
    "Autocorrelation of First Order =", acf_cauchy, "\n")
cat("Лапласа (lambda=1): Acceptance Rate =", result_laplace$acceptance_rate,
    "Autocorrelation of First Order =", acf_laplace, "\n\n")

cat("Подобранные параметры для вероятности перехода ~0.25:\n")
cat("Равномерное: delta =", param_unif$parameter, 
    "Acceptance Rate =", param_unif$acceptance_rate, "\n")
cat("Коши: gamma =", param_cauchy$parameter, 
    "Acceptance Rate =", param_cauchy$acceptance_rate, "\n")
cat("Лапласа: lambda =", param_laplace$parameter, 
    "Acceptance Rate =", param_laplace$acceptance_rate, "\n")

