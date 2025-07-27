library(tidyverse)
library(data.table)


flights <- read.csv("flights14.csv")
tv_flights <- as_tibble(flights)
dt_flights <- data.table(flights)


N <- 100
base_time = 0
tv_time = 0
dt_time = 0
for (i in 1:N)
{
  start = Sys.time()
  flights[flights$origin == "JFK" & flights$month == 6L, ]
  base_time <- base_time + Sys.time() - start
  
  start = Sys.time()
  tv_flights|>
    filter(origin == "JFK" & month == 6L)
  tv_time <- tv_time + Sys.time() - start
  
  start = Sys.time()
  dt_flights[origin == "JFK" & month == 6L]
  dt_time <- dt_time + Sys.time() - start
}