# Набросок для проверочной 29.10.2024

library(carData)
summary(Adler)
summary(AMSsurvey)

library(purrr)
mp<-map(Adler, summary)

mean(Adler$instruction=="good")

table(AMSsurvey)
table(Adler$instruction, Adler$expectation)
factor(Adler$instruction)
Adler$instruction

summary(table(Adler$instruction, Adler$expectation))

lambda<-1
n<-100
poi<-rexp(n, lambda)
# Нормализация
scale(poi)

library(tseries)
runs.test(poi)

nor<-rnorm(n)
t.test(poi, nor)

m<-lm(poi~nor)
anova(m)
effects(m)
fitted(m)
confint(m)
coef(m)
residuals(m)
resid(m)
summary(m)
vcov(m)

# ggplot
# facet_wrap - обёртка по факторам (графики по факторам)
# geom_bar - гистограмма
# geom_errorbar - доверительный интервал для гистограммы
# stat_summary
# geom_line
# geom_boxplot
# geom_histogram
# stat_function
# ggtitle

# tidyverse
# fct_inorder

# library(patchwork)
# Для зарисовки нескольких графиков

# map_dbl - попарная корреляция для каждого столбца

# boxcox (for lm) - применение степенного преобразования к зависимой переменной.

# library(broom)
# augment - построение графика остатков и подогнанных значений
# либо plot(m, which = 1)
# which.max(...)
# outlierTest(...)
# influence.measures(...)
# dwtest(...) - Дарбин-Уотсон проверяет невязку на наличие автокорреляции
# predict(...)
# oneway.test(...) - anova однофакторный
# aov(...) - -||-
# interaction.plot(...) - график взаимодействий
# TukeyHSD(...) - каковы различия между средними значениями групп.
# kruskal.test(...) - проверка медиан групп

n<-8
group1 <- c(4, 6, 5, 1, 7, 2, 3, 8)
group2 <- c(7, 6, 4, 3, 5, 2, 1, 8)
diff = group1-group2
diff_sq = diff**2
spearman_coef <- 1 - 6*sum(diff_sq)/(n*(n**2-1))
spearman_coef
cor.test(group1, group2, method="spearman")

group1 <- c(107, 95, 116, 109, 101, 98)
group2 <- c(107, 102, 112, 104, 105, 103)
diff = group1-group2
diff_sq = diff**2
spearman_coef <- 1 - 6*sum(diff_sq)/(n*(n**2-1))
spearman_coef
cor.test(group1, group2, method="spearman")
print("Коэф-т Спирмена")
