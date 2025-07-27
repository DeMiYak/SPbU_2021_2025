library("tidyverse")

#> Using this library to conveniently expand the column with artists' names
#> via "cSplit"

#> For each artist find the total track number
#> total listening of all tracks number
#> and print the most listened tracks' names 

dataset <- read.csv(file = "spotify-23.csv")

# data <- dataset |>
#   mutate(artist_names = strsplit(artist.s._name, ', ')) |>
#   select(artist_names, track_name, streams) |>
#   unnest_longer(artist_names) |>
#   group_by(artist_names) |>
#   summarise(num.tracks = n(), 
#             across(
#               .cols = c(streams),
#               .fns = list(
#                 max = ~ max(.x, na.rm=F)
#               ),
#               .names = '{.col}.{.fn}'
#             )) |>
#   inner_join(
#     dataset |>
#     mutate(artist_names = strsplit(artist.s._name, ', ')) |>
#     select(artist_names,track_name, streams) |>
#     unnest_longer(artist_names) |>
#     group_by(artist_names) |>
#     rename(streams.max = streams, track_name.max = track_name),
#     by = c('artist_names','streams.max')
#       )

data <- dataset |>
  mutate(artist_names = strsplit(artist.s._name, ', ')) |>
  select(artist_names, track_name, streams) |>
  unnest_longer(artist_names) |>
  group_by(artist_names) |>
  summarize(num.tracks = n(), 
            streams.max = max(streams),
            track.hit = track_name[which.max(streams)],)
