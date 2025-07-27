# # Моделирование Y
# model_y_fast <- function(n, k_true, lambda_true, t) {
#   # Генерация K ~ Poisson(t) + 1
#   K <- rpois(n, t) + 1L
#   # Генерация X из распределения Вейбулла
#   X <- rweibull(n, shape = k_true, scale = lambda_true)
#   
#   # Инициализация векторов результатов
#   T_left <- numeric(n)
#   T_right <- numeric(n)
#   
#   # Определяем наблюдения, где X превышает t
#   over_t <- X > t
#   under_t <- !over_t
#   
#   # Обработка случаев, где X > t
#   if (any(over_t)) {
#     K_over <- K[over_t]
#     U <- runif(sum(over_t))
#     T_left[over_t] <- t * U^(1/K_over)
#     T_right[over_t] <- Inf
#   }
#   
#   # Обработка случаев, где X <= t
#   if (any(under_t)) {
#     K_under <- K[under_t]
#     X_under <- X[under_t]
#     m <- rbinom(sum(under_t), K_under, X_under/t)
#     
#     # Случай m = 0
#     case0 <- m == 0
#     if (any(case0)) {
#       T_right_0 <- t * rbeta(sum(case0), 1, K_under[case0])
#       T_left[under_t][case0] <- 0
#       T_right[under_t][case0] <- T_right_0
#     }
#     
#     # Случай m = K_under
#     caseK <- m == K_under
#     if (any(caseK)) {
#       T_left_K <- t * rbeta(sum(caseK), K_under[caseK], 1)
#       T_left[under_t][caseK] <- T_left_K
#       T_right[under_t][caseK] <- Inf
#     }
#     
#     # Случай 0 < m < K_under
#     casemid <- m > 0 & m < K_under
#     if (any(casemid)) {
#       m_mid <- m[casemid]
#       K_mid <- K_under[casemid]
#       T_left[under_t][casemid] <- t * rbeta(sum(casemid), m_mid, K_mid - m_mid + 1)
#       T_right[under_t][casemid] <- t * rbeta(sum(casemid), m_mid + 1, K_mid - m_mid)
#     }
#   }
#   
#   # Возвращаем данные в виде data.frame
#   data.frame(
#     K = K,
#     X = X,
#     T_left = T_left,
#     T_right = T_right
#   )
# }
# 
# k<-2
# lambda<-3
# t<-5
# N<-1e6
# # Пример на корректность
# set.seed(123)
# data <- model_y_fast(n = N, k_true = k, lambda_true = lambda, t = t)
# 
# # Проверка распределения X
# hist(data$X, breaks = 30, main = "Распределение X (Вейбулл)",
#      xlab = "X", freq = FALSE, col = "lightblue")
# curve(dweibull(x, shape = k, scale = lambda), add = TRUE, col = "red", lwd = 2)
# 
# log_likelihood_simple <- function(k, lambda, X) {
#   n <- length(X)
#   -(n*log(k) - n*k*log(lambda) + (k-1)*sum(log(X)) - sum((X/lambda)^k))
# }
# 
# # Проверка на полных данных
# data_full <- data.frame(X = rweibull(1000, shape = 2, scale = 3))
# data<-model_y_fast(1e4, k, lambda, t)
# fit_simple <- mle2(log_likelihood_corrected, 
#                    start = list(k = 1, lambda = 1), 
#                    data = list(data = data))
# coef(fit_simple)  # Должно быть близко к k=2, lambda=3
# 
# library(bbmle)
# 
# log_likelihood_corrected <- function(k, lambda, data) {
#   T_left <- data$T_left
#   T_right <- data$T_right
#   
#   # Вычисление вероятностей с учётом параметризации Вейбулла
#   prob <- ifelse(
#     is.infinite(T_right),
#     exp(-(T_left/lambda)^k),  # P(X > T_left)
#     exp(-(T_left/lambda)^k) - exp(-(T_right/lambda)^k)  # P(T_left < X < T_right)
#   )
#   
#   # Стабилизация численных значений
#   prob <- pmax(prob, 1e-100)
#   return(-sum(log(prob)))
# }
# 
# fit_weibull_improved <- function(data) {
#   # Метод моментов для начальных значений
#   x_mean <- mean(data$X)
#   x_var <- var(data$X)
#   
#   # Приближения для параметров Вейбулла
#   lambda0 <- x_mean / gamma(1 + 1/1.5)  # Эвристика
#   k0 <- 1.5  # Стартовое значение
#   
#   # Оптимизация
#   optim(par=c(k0, lambda0))
#   mle2(
#     log_likelihood_corrected,
#     start = list(k = k0, lambda = lambda0),
#     data = list(data = data),
#     method = "Nelder-Mead",  # Более устойчивый метод
#     control = list(maxit = 1000)
#   )
# }
# 
# # Генерация данных
# set.seed(123)
# data <- model_y_fast(n = 1e4, k_true = 2, lambda_true = 3, t = 5)
# 
# # Подгонка модели
# fit <- fit_weibull_improved(data)
# summary(fit)
# 
# # Профильные доверительные интервалы
# prof_k <- profile(fit, which = "k")
# prof_lambda <- profile(fit, which = "lambda")
# 
# plot(prof_k)  # Должен показать симметричный профиль
# plot(prof_lambda)
# 
# confint(prof_k)    # Должен содержать истинное k=2
# confint(prof_lambda)  # Должен содержать lambda=3
# 
# library(bbmle)
# 
# # 1. Функция правдоподобия (оставляем без изменений)
# log_likelihood <- function(k, lambda, data) {
#   T_left <- data$T_left
#   T_right <- data$T_right
#   X <- data$X
#   
#   contrib <- ifelse(
#     is.infinite(T_right),
#     exp(-(T_left / lambda)^k),
#         exp(-(T_left / lambda)^k) - exp(-(T_right / lambda)^k)
#     )
#         contrib <- pmax(contrib, .Machine$double.eps)
#         -sum(log(contrib))
# }
# 
# # 2. Функция для нахождения ОМП (оставляем без изменений)
# fit_weibull_mle <- function(data) {
#   start_vals <- list(k = 1, lambda = mean(data$X))
#   mle2(log_likelihood,
#        start = start_vals,
#        data = list(data = data),
#        method = "L-BFGS-B",
#        lower = c(k = 0.1, lambda = 0.1))
# }
# 
# N<-1e5
# k_true<-3
# lambda_true<-8
# t<-10
# system.time(data<-model_y_fast(N, k_true, lambda_true, t))
# data
# 
# # 3. Модифицированная версия исследования ДИ без параллелизма
# n_values <- c(50, 100, 200, 500, 1000)
# true_k <- 2
# true_lambda <- 3
# t <- 5
# fit_weibull_mle(data)
# n_sim <- 20  # Уменьшаем для демонстрации
# 
# # Запуск симуляций последовательно
# results <- lapply(n_values, function(n) {
#   replicate(n_sim, {
#     data <- model_y_fast(n, true_k, true_lambda, t)
#     fit <- tryCatch(
#       fit_weibull_mle(data),
#       error = function(e) NULL
#     )
#     
#     if (!is.null(fit)) {
#       tryCatch(
#         confint(fit),
#         error = function(e) matrix(NA, nrow = 2, ncol = 2)
#       )
#     } else {
#       matrix(NA, nrow = 2, ncol = 2)
#     }
#   }, simplify = FALSE)
# })
# 
# # Анализ результатов и визуализация (оставляем без изменений)
# analyze_results <- function(results) {
#   df <- data.frame()
#   for (i in seq_along(n_values)) {
#     n <- n_values[i]
#     ci_list <- results[[i]]
#     
#     widths <- sapply(ci_list, function(x) {
#       # Проверяем структуру объекта
#       if (!is.matrix(x) || ncol(x) < 2) return(NA)
#       
#       # Используем индексы вместо имен столбцов
#       lower <- x[, 1]
#       upper <- x[, 2]
#       mean(upper - lower, na.rm = TRUE)
#     })
#     
#     avg_width <- mean(widths, na.rm = TRUE)
#     df <- rbind(df, data.frame(n = n, width = avg_width))
#   }
#   return(df)
# }
# result_df <- analyze_results(results)
# 
# # Визуализация
# library(ggplot2)
# ggplot(result_df, aes(x = n, y = width)) +
#   geom_line() +
#   geom_point() +
#   labs(
#     title = "Зависимость ширины дов. интервала от размера выборки",
#     x = "Размер выборки",
#     y = "Средняя ширина 95% ДИ"
#   ) +
#   theme_minimal()
# 
# get_profile_ci <- function(fit, param_name, alpha = 0.05) {
#   prof <- profile(fit, which = param_name, alpha = alpha)
#   ci <- confint(prof)
#   return(ci)
# }
# 
# # Пример использования:
# k_true<-2
# lambda_true<-3
# t<-5
# data <- model_y_fast(1e3, k_true, lambda_true, t)
# fit <- fit_weibull_mle(data)
# k_ci <- get_profile_ci(fit, "k")
# lambda_ci <- get_profile_ci(fit, "lambda")
