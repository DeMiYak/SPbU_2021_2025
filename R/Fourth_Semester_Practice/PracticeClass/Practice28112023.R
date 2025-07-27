library("tidyverse")

country_names <- list.files("archive-11")
country_names <- sapply(country_names, function(x) paste0("archive-11/",x))

jam <- data.frame()
for(x in country_names){
  x <- read.csv(x)
  jam <- rbind(jam, x)
}

jam <- mutate(jam, Date = as.Date(Date))

jamCN <- group_by(jam, Country.Name)|>
  summarize(Total.Holidays = n())

jamH <- group_by(jam, Date)|>
  summarize(Total.Holidays = n())|>
  rmarkdown::paged_table()

# Define the phrase
phrase <- "['Christianity', 'Wisdom']"

# Extract the words using gsub
words <- gsub("([][{}()+*^${|\\\\?.])", "", phrase)
print(words)
words <- strsplit(words, split = ", ")
# Print the extracted words
print(words)
      
      