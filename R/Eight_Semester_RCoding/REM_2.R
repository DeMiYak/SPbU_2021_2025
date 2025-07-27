# Загрузка необходимых пакетов
library(mclust)
library(ggplot2)

# Загрузка данных
data <- read.table("faithful.txt", skip = 3, header = TRUE, 
                   col.names = c("id", "eruptions", "waiting"))

# Удаление столбца с идентификаторами
data <- data[, c("eruptions", "waiting")]

# Применение EM-алгоритма через mclust
model <- Mclust(data)

# Сводка модели (показывает оптимальное число кластеров по BIC)
summary(model)

# Визуализация результатов
plot(model, what = "classification", main = "Кластеризация данных")
plot(model, what = "uncertainty", main = "Неопределённость кластеризации")
plot(model, what = "density", main = "Плотность смеси")

# Дополнительная визуализация с ggplot2
ggplot(data, aes(x = eruptions, y = waiting, color = factor(model$classification))) +
  geom_point() +
  stat_ellipse() +  # Добавление эллипсов доверия
  labs(title = "Кластеризация извержений гейзера Old Faithful",
       x = "Длительность извержения (мин)",
       y = "Время ожидания (мин)",
       color = "Кластер") +
  theme_minimal()

# Обоснование адекватности модели
cat("Оптимальное число кластеров:", model$G, "\n")
cat("Лучшая модель:", model$modelName, "\n")
cat("BIC для выбранной модели:", max(model$BIC), "\n")
