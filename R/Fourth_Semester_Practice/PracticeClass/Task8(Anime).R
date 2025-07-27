library("tidyverse")
library("ggplot2")
dataset <- read.csv("Anime.csv")

parse_time <- function(expression) {
  # Check if the expression is "Unknown"
  if (expression == "Unknown") {
    return(NA)
  }
  
  # Extract hours, minutes, and seconds using regular expressions
  hours <- as.numeric(sub(".*?(\\d+) hr.*", "\\1", expression, ignore.case = TRUE))
  minutes <- as.numeric(sub(".*?(\\d+) min.*", "\\1", expression, ignore.case = TRUE))
  seconds <- as.numeric(sub(".*?(\\d+) sec.*", "\\1", expression, ignore.case = TRUE))
  
  # Assign default values when hours, minutes and seconds cannot be found
  if (is.na(hours)) {
    hours <- 0
  }
  if(is.na(minutes)){
    minutes <- 0
  }
  if (is.na(seconds)) {
    seconds <- 0
  }
  # Calculate the total time in seconds
  total_seconds <- hours * 3600 + minutes * 60 + seconds
  
  return(total_seconds)
}
# Example usage
expression1 <- "2 hr. 4 min. 43 sec."
time_in_seconds1 <- parse_time(expression1)
time_in_seconds1

expression2 <- "Unknown"
time_in_seconds2 <- parse_time(expression2)
time_in_seconds2

expression3 <- "1 min. per ep"
time_in_seconds3 <- parse_time(expression3)
time_in_seconds3

data <- dataset |>
  mutate(Episodes = as.integer(Episodes), 
          Duration = sapply(Duration, parse_time),
         Time.total = Episodes*Duration,
         Watchmen.total = Watching + On.Hold + Completed + Dropped,
         Dropped.percent = Dropped/(Watching + On.Hold + Completed + Dropped),
         .after = Dropped) |>
  select(Name, Type, Episodes, Duration, Watchmen.total, 
         Dropped, Dropped.percent, Time.total) 
dataTypes <- data|>
  select(Type)|>
  group_by(Type)|>
  summarize(type.num = n())
dataMovie <- filter(data, Type == "Movie", !is.na(Time.total), !is.na(Dropped.percent))
ggplot(filter(data, Type == "Movie", !is.na(Time.total), !is.na(Dropped.percent))) +
  aes(x = Time.total, y = Dropped.percent) + geom_point()

ggplot(filter(data, Type == "TV", !is.na(Time.total), !is.na(Dropped.percent))) +
  aes(x = Time.total, y = Dropped.percent) + geom_point()

ggplot(filter(data, Type == "OVA", !is.na(Time.total), !is.na(Dropped.percent))) +
  aes(x = Time.total, y = Dropped.percent) + geom_point()

ggplot(filter(data, Type == "ONA", !is.na(Time.total), !is.na(Dropped.percent))) +
  aes(x = Time.total, y = Dropped.percent) + geom_point()

ggplot(filter(data, Type == "Music", !is.na(Time.total), !is.na(Dropped.percent))) +
  aes(x = Time.total, y = Dropped.percent) + geom_point()

ggplot(filter(data, Type == "Special", !is.na(Time.total), !is.na(Dropped.percent))) +
  aes(x = Time.total, y = Dropped.percent) + geom_point()

ggplot(filter(data, Type == "Unknown", !is.na(Time.total), !is.na(Dropped.percent))) +
  aes(x = Time.total, y = Dropped.percent) + geom_point()
  #> 1. Парадокс Монте-Карло
  #> 2. Задача о женихах и невесте
  #>