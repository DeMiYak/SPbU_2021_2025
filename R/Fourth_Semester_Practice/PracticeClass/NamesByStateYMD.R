library("tidyverse")
data <- read.csv("USA Name Data.csv")
data_by_names <- data |>
  select(Name)|>
  group_by(Name)|>
  mutate(Name = sapply(Name, function(x) substring(x, 1, 1)))
data_num <- dplyr::summarize(data_by_names, 
                   Number = n(),
                   Ratio = n()/nrow(data_by_names))
barplot(data_num$Number, names.arg = data_num$Name)
data_num|>
  slice_max(order_by=Number, n = 5)

data_num|>
  slice_min(order_by = Number, n = 5)
data_num
