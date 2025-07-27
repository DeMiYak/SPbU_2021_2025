#> Monty-Hall's paradox
#>

# Number of simulations
num_simulations <- 1000

# Function to run a single Monty Hall game
run_game <- function() {
  # Assigning door labels
  doors <- c('A', 'B', 'C')
  
  # Placing the prize randomly behind one of the doors
  prize_door <- sample(doors, 1)
  
  # Player's initial door selection
  player_choice <- sample(doors, 1)
  
  # Monty opens a door
  monty_opens <- setdiff(doors, c(prize_door, player_choice))
  open_door <- sample(monty_opens, 1)
  
  # Switch or not?
  switched_choice <- setdiff(doors, c(player_choice, open_door))
  switched_choice <- sample(switched_choice, 1)
  
  # Determining whether player wins or not
  win <- (switched_choice == prize_door)
  return(win)
}

# Running multiple simulations of the game
results <- replicate(num_simulations, run_game())

# Calculating probabilities
switched_win_probability <- mean(results)
non_switched_win_probability <- 1 - switched_win_probability

# Printing the results
cat("Switched win probability:", switched_win_probability, "\n")
cat("Non-switched win probability:", non_switched_win_probability)

# Step 1: Create a character vector for x-axis labels
x_labels <- c("A", "B", "C", "D", "E")

# Step 2: Convert to a factor
x_factor <- as.factor(x_labels)

# Step 3: Create histogram
hist(x_factor, main = "Histogram", xlab = "Variable", ylab = "Frequency")