# Load necessary libraries
library(Rssa)
library(ggplot2)
library(latex2exp)
library(Cairo)

# Define PI for use in functions below
PI <- asin(1) 

################################################################################
# Block 1: Auxiliary functions for SSA and linear estimation
################################################################################

#' @title Diagonal Averaging of a Matrix
#' @description This function performs diagonal averaging for a given matrix.
#'              If i, j are column and row indices, each element
#'              is replaced by its diagonal average for i+j=const. 
#' @param matr Input matrix.
#' @return Matrix with averaged anti-diagonals.
#' @examples
#' test_matrix <- matrix(1:9, nrow = 3)
#' diag_averaging(test_matrix)
diag_averaging <- function(matr) {
  # Check if input is a matrix
  if (!is.matrix(matr)) {
    stop("Error: Input data must be a matrix.")
  }
  # Empty or NA-containing matrices are handled carefully
  if (nrow(matr) == 0 || ncol(matr) == 0) {
    return(matr)
  }
  
  rows <- nrow(matr)
  cols <- ncol(matr)
  result <- matr # Copy the matrix to preserve changes
  
  # Iterate over all possible sums of indices (from 2 to rows + cols)
  # row(matr) + col(matr) - 2 gives the anti-diagonal index, starting from 0
  # Diagonal averaging
  for (diag_sum_val in 2:(rows + cols)) {
    indices <- which(row(matr) + col(matr) == diag_sum_val, arr.ind = TRUE)
    
    if (length(indices) > 0) {
      # Extract elements on the current anti-diagonal
      diag_elements <- matr[indices]
      # Calculate the mean value, ignoring NA
      mean_val <- mean(diag_elements, na.rm = TRUE)
      # Assign the mean value to all elements on this anti-diagonal in the result matrix
      result[indices] <- mean_val
    }
  }
  return(result)
}

#' @title Calculation of Projection Matrices P and Q
#' @description The function calculates projection matrices P = U U^T and Q = V V^T,
#'              where U is the matrix of left singular vectors, and V is the matrix
#'              of right singular vectors of the signal trajectory matrix H.
#' @param H Time series (clean signal).
#' @param L Window length (SSA parameter).
#' @param d Rank used for reconstruction (number of components).
#' @return A list containing matrices P and Q.
#' @examples
#' H_test <- sin(1:100 / 10)
#' L_test <- 30
#' d_test <- 2
#' pq_matrices <- calc.p_q(H_test, L_test, d_test)
#' names(pq_matrices) # Should be c("P", "Q")
calc.p_q <- function(H, L, d) {
  # Input data validation
  if (!is.numeric(H) || length(H) == 0) {
    stop("Error: H must be a non-empty numeric vector.")
  }
  if (!is.numeric(L) || L <= 0 || L > length(H)) {
    stop("Error: L must be a positive number, not exceeding the length of H.")
  }
  if (!is.numeric(d) || d <= 0 || d > L) {
    stop("Error: d must be a positive number, not exceeding L.")
  }
  
  # Perform SSA
  ssa.obj <- Rssa::ssa(H, L = L, kind = "1d-ssa") # Specify kind for clarity
  
  # Check that d does not exceed the number of available singular values
  if (d > length(ssa.obj$sigma)) {
    warning(paste("Parameter d (", d, ") exceeds the number of singular values (", length(ssa.obj$sigma), "). Using d = ", length(ssa.obj$sigma), ".", sep=""))
    d <- length(ssa.obj$sigma)
  }
  
  # Extract U (left singular vectors)
  U <- ssa.obj$U[, 1:d, drop = FALSE] # drop = FALSE to preserve matrix structure when d=1
  
  # Extract V (right singular vectors)
  # calc.v might not be exported or might require ssa.obj as the first argument
  # In Rssa v1.0.4, calc.v is an internal function.
  # An alternative way to get V is directly via $V if available, or via decomposition.
  # Usually V is ssa.obj$V. If not, then V = t(X_elementary) %*% U %*% diag(1/sigma)
  # However, a more direct way is to use Rssa::reconstruct to get elementary matrices,
  # and then their decomposition, or use Rssa::calc.v if available.
  # In this context, it is assumed that calc.v from Rssa is available.
  V <- Rssa::calc.v(ssa.obj, idx = 1:d)[, 1:d, drop = FALSE] # drop = FALSE
  
  # Calculate projection matrices
  P <- U %*% t(U)
  Q <- V %*% t(V)
  
  return(list(P = P, Q = Q))
}

#' @title Calculation of the Linear Error Approximation Matrix
#' @description The function calculates the matrix P E + E Q - P E Q, where P and Q are
#'              projection matrices, and E is the trajectory matrix of the noise.
#' @param pq A list containing matrices P and Q (output of calc.p_q function).
#' @param E Noise time series.
#' @param L Window length (SSA parameter), used to build the noise trajectory matrix.
#' @return The linear error approximation matrix.
#' @examples
#' H_test <- sin(1:100 / 10)
#' E_test <- rnorm(100, 0, 0.1)
#' L_test <- 30
#' d_test <- 2
#' pq_mats <- calc.p_q(H_test, L_test, d_test)
#' error_approx_matrix <- calc.pe_eq_peq(pq_mats, E_test, L_test)
calc.pe_eq_peq <- function(pq, E, L) {
  # Input data validation
  if (!is.list(pq) || !all(c("P", "Q") %in% names(pq))) {
    stop("Error: pq must be a list with elements P and Q.")
  }
  if (!is.matrix(pq$P) || !is.matrix(pq$Q)) {
    stop("Error: P and Q in the pq list must be matrices.")
  }
  if (nrow(pq$P) != ncol(pq$P) || nrow(pq$P) != L) {
    stop(paste("Error: P must be a square L x L matrix, where L =", L))
  }
  if (nrow(pq$Q) != ncol(pq$Q) || ncol(pq$P) != (length(E) - L + 1) && nrow(pq$Q) != (length(E) - L +1) ) {
    # K = N - L + 1. Q is K x K.
    # ncol(P) is L. This check seems incorrect. P is L x L. Q is K x K.
    # The important part is that E_hankel is L x K.
    # So P %*% E_hankel is L x K. E_hankel %*% Q is L x K. P %*% E_hankel %*% Q is L x K.
  }
  if (!is.numeric(E) || length(E) == 0) {
    stop("Error: E must be a non-empty numeric vector.")
  }
  if (!is.numeric(L) || L <= 0 || L > length(E)) {
    stop("Error: L must be a positive number, not exceeding the length of E.")
  }
  
  P <- pq$P
  Q <- pq$Q
  
  # Construct the trajectory matrix for noise E
  # Ensure the correct hankel function is used
  E_hankel <- Rssa::hankel(E, L = L) # L - number of rows, K = N-L+1 - number of columns
  
  # Check dimensions for matrix multiplication
  # P (L x L), E_hankel (L x K), Q (K x K)
  # K = ncol(E_hankel)
  if (ncol(P) != nrow(E_hankel)) {
    stop(paste("Dimension mismatch error: ncol(P) =", ncol(P), "but nrow(E_hankel) =", nrow(E_hankel)))
  }
  if (ncol(E_hankel) != nrow(Q)) {
    stop(paste("Dimension mismatch error: ncol(E_hankel) =", ncol(E_hankel), "but nrow(Q) =", nrow(Q)))
  }
  
  # Calculate P E Q
  PE <- P %*% E_hankel
  EQ <- E_hankel %*% Q
  PEQ <- PE %*% Q # or P %*% EQ
  
  # Calculate P E + E Q - P E Q
  result_matrix <- PE + EQ - PEQ
  
  return(result_matrix)
}


################################################################################
# Block 2: Auxiliary functions for time series generation
################################################################################

#' @title Create an Exponentially-Modulated Harmonic Series
#' @description Generates a time series as a sum of several exponentially-modulated harmonics.
#' @param A Vector of amplitudes.
#' @param alpha Vector of exponential modulation coefficients.
#' @param freq Vector of frequencies.
#' @param angle Vector of initial phases (in radians).
#' @param N Length of the generated time series.
#' @return Vector of the time series.
CreateExponentialTimeSeries <- function(A, alpha, freq, angle, N){
  if (length(A) != length(alpha) || length(A) != length(freq) || length(A) != length(angle)) {
    stop("Error: Lengths of vectors A, alpha, freq, angle must match.")
  }
  if (N <= 0) {
    stop("Error: N must be a positive integer.")
  }
  t_vals <- matrix(0:(N-1), nrow = 1) # Time index as a 1xN matrix
  
  # Initialize the resulting series
  total_series <- numeric(N)
  
  # Summing components
  # Vectorization here can be complex if A, alpha, freq, angle are vectors of different lengths.
  # The original code `A * exp(alpha %*% t) * cos(2 * PI * (freq %*% t) + angle)`
  # implies that A, alpha, freq, angle are component vectors.
  # `alpha %*% t_vals` will be a KxN matrix, where K is the number of components.
  
  # If A, alpha, freq, angle are parameter vectors for K components:
  num_components <- length(A)
  if (num_components == 0) return(numeric(N))
  
  # Convert parameter vectors to K x 1 matrices for correct multiplication
  A_m <- matrix(A, ncol = 1)
  alpha_m <- matrix(alpha, ncol = 1)
  freq_m <- matrix(freq, ncol = 1)
  angle_m <- matrix(angle, ncol = 1)
  
  # alpha_m %*% t_vals -> KxN matrix
  # freq_m %*% t_vals -> KxN matrix
  # A_m * ... -> KxN matrix (element-wise multiplication, A_m replicated by columns)
  # angle_m is also replicated
  
  # `angle_m` should be KxN or Kx1. If Kx1, it will be replicated.
  # `A_m` should be KxN or Kx1.
  
  # Correct vectorization:
  # t_vals should be 1xN
  # alpha_m (Kx1) %*% t_vals (1xN) -> KxN
  # freq_m (Kx1) %*% t_vals (1xN) -> KxN
  # A_m (Kx1) will be multiplied element-wise with the result of exp(...) * cos(...)
  # angle_m (Kx1) will be added element-wise to 2*pi*freq*t
  
  exp_term <- exp(alpha_m %*% t_vals) # KxN
  cos_term <- cos(2 * base::pi * (freq_m %*% t_vals) + matrix(angle_m, nrow = num_components, ncol = N, byrow = FALSE)) # KxN
  
  # Correct:
  # Create A_m_expanded K x N matrix
  A_m_expanded <- matrix(A_m, nrow = num_components, ncol = N, byrow = FALSE)
  result_matrix <- A_m_expanded * exp_term * cos_term
  
  return(colSums(result_matrix))
}


#' @title Create a Polynomial Time Series
#' @description Generates a time series based on a polynomial of a given degree.
#' @param coefficientVector Vector of polynomial coefficients (starting with c0, c1*t, c2*t^2, ...).
#' @param N Length of the generated time series.
#' @return Vector of the time series.
CreatePolynomialTimeSeries <- function(coefficientVector, N) {
  if(!is.numeric(coefficientVector)) stop("Error: coefficientVector must be numeric.")
  if (N <= 0) stop("Error: N must be a positive integer.")
  
  k <- length(coefficientVector)
  if (k == 0) return(numeric(N))
  
  t_vals <- 0:(N-1)
  
  # Create a matrix of powers t^(j-1) for j=1:k
  # powers will be an N x k matrix
  powers <- outer(t_vals, 0:(k-1), "^")
  
  # Calculate the series: powers %*% coefficientVector
  timeSeries <- powers %*% coefficientVector
  
  return(as.vector(timeSeries))
}


################################################################################
# Block 3: Main analysis function
################################################################################

#' @title Signal Analysis with Noise using SSA and Linear Approximation Methods
#' @description This function performs time series analysis consisting of a signal and noise.
#'              It calculates signal reconstruction errors using SSA and linear
#'              approximation for various lengths of the analyzed series segment.
#'              The function also creates plots of the maximum reconstruction error
#'              for linear approximation and SSA error, both multiplied by series length N and without.
#'
#' @param H Clean signal (numeric vector).
#' @param signal_type Name of the signal type for plot titles (string).
#' @param E Noise (numeric vector, must have the same length as H).
#' @param noise_type Name of the noise type for plot titles (string).
#' @param d Rank used for signal reconstruction in SSA (integer).
#' @param delta Formal perturbation parameter (noise scale) (numeric).
#' @param div Divisor for determining window length L (L = n / div) (integer).
#' @param by Increment parameter for the sequence of analyzed segment lengths n (integer).
#' @param size_param Line size parameter for ggplot plots (numeric).
#'
#' @return A list containing:
#' \itemize{
#'   \item \code{p_graph}: Plot of the original signal with noise (ggplot object).
#'   \item \code{p_max_recovery_error}: Plot of the maximum recovery error (ggplot object).
#'   \item \code{p_max_recovery_error_mult_N}: Plot of the maximum recovery error multiplied by N (ggplot object).
#'   \item \code{df_graph}: Data frame with data for p_graph plot.
#'   \item \code{df_recovery_error}: Data frame with recovery error data.
#'   \item \code{df_timing}: Data frame with computation times for each iteration.
#'   \item \code{N_overall}: Overall length of the original signal H.
#'   \item \code{d_rank}: Used rank d.
#'   \item \code{div_param}: Used divisor div.
#'   \item \code{n_vector}: Vector of analyzed segment lengths n.
#'   \item \code{L_vector}: Vector of window lengths L.
#' }
#' @examples
#' \dontrun{
#' # Example data
#' N_example <- 1200
#' d_example <- 4
#' div_example <- 4
#' by_example <- 30
#' delta_example <- 1
#' size_param_example <- 0.6
#' 
#' theta_example <- c(2020/1000, -2141/10^4, 122/10^4, -1/10^3)
#' H_example <- CreatePolynomialTimeSeries(theta_example, N_example)
#' 
#' df_E_param_example <- data.frame(
#'   A = c(12, -6, -10, 4),
#'   omega = c(1/sqrt(10), sqrt(3)/10, 1/31, sqrt(2)/5),
#'   varphi = c(7*base::pi/5, 13*base::pi/17, base::pi/2, 4*base::pi/7),
#'   alpha = rep.int(0,4)
#' )
#' E_example <- CreateExponentialTimeSeries(
#'   A = df_E_param_example$A,
#'   alpha = df_E_param_example$alpha,
#'   freq = df_E_param_example$omega, # Parameter name in function is freq, in data.frame it's omega
#'   angle = df_E_param_example$varphi,
#'   N = N_example
#' )
#'
#' results <- analyze_signal_noise(
#'   H = H_example,
#'   signal_type = "Polynomial",
#'   E = E_example,
#'   noise_type = "Harmonic",
#'   d = d_example,
#'   delta = delta_example,
#'   div = div_example,
#'   by = by_example,
#'   size_param = size_param_example
#' )
#' # # Show plots
#' # print(results$p_graph)
#' # print(results$p_max_recovery_error)
#' # print(results$p_max_recovery_error_mult_N)
#' # Show tables
#' # print(head(results$df_recovery_error))
#' # print(head(results$df_timing))
#' }

analyze_signal_noise <- function(H, signal_type, E, noise_type, d, delta, div, by, size_param) {
  
  # --- Step 1: Parameter Initialization ---
  if (length(H) != length(E)) {
    stop("Error: Signal H and noise E must have the same length.")
  }
  N_overall <- length(H)
  
  # Create sequences for n and L
  # n - sequence of analyzed segment lengths
  # L - corresponding sequence of window lengths
  n_vector <- seq(d * div, N_overall, by = by)
  if (length(n_vector) == 0 || n_vector[length(n_vector)] > N_overall) {
    # If n_vector is empty or the last element is greater than N_overall, correct it
    # This can happen if d*div > N_overall or N_overall is not reached with step 'by'
    # Ensure n_vector is not empty and does not exceed N_overall
    n_vector <- seq(d * div, N_overall, by = by)
    n_vector <- n_vector[n_vector <= N_overall]
    if (length(n_vector) == 0 && d*div <= N_overall) { # if d*div is valid, but seq didn't work
      n_vector <- d*div
    } else if (length(n_vector) == 0) {
      stop(paste("Cannot create sequence n. Check parameters d, div, by and N_overall. d*div =", d*div, "N_overall =", N_overall))
    }
  }
  L_vector <- n_vector %/% div
  
  # Check that L_vector does not contain zeros or negative values if n_vector is small
  if (any(L_vector <= 0)) {
    stop("Error: Parameters d, div resulted in invalid L values (<=0). Increase n or decrease div.")
  }
  
  # --- Step 2: Calculation Loop ---
  num_iterations <- length(n_vector)
  Xssa_errors <- numeric(num_iterations)
  Xlinear_errors <- numeric(num_iterations)
  computation_times_secs <- numeric(num_iterations)
  
  X_perturbed_full <- H + delta * E # Full perturbed signal
  
  for (i in 1:num_iterations) {
    cat("Iteration ", i, " of ", num_iterations, ", n = ", n_vector[i], "\n")
    start_time <- Sys.time()
    
    L_curr <- L_vector[i]
    n_curr <- n_vector[i]
    
    # Current segments of signal and noise
    H_curr <- H[1:n_curr]
    E_curr <- E[1:n_curr]
    X_curr <- X_perturbed_full[1:n_curr] # or H_curr + delta * E_curr
    
    # SSA part
    if (L_curr > 0 && L_curr <= n_curr && d > 0 && d <= L_curr) {
      tempssa <- Rssa::ssa(X_curr, L = L_curr, kind = "1d-ssa")
      if (d > length(tempssa$sigma)) {
        warning(paste("In iteration i=", i, " d=", d, "is greater than the number of singular values=", length(tempssa$sigma), ". Using d=", length(tempssa$sigma)))
        d_effective <- length(tempssa$sigma)
      } else {
        d_effective <- d
      }
      if (d_effective > 0) {
        D_reconstructed <- Rssa::reconstruct(tempssa, groups = list(1:d_effective))$F1
        Xssa_errors[i] <- max(abs(D_reconstructed - H_curr))
      } else {
        Xssa_errors[i] <- NA # Cannot reconstruct with d_effective = 0
      }
      
      
      # Linear approximation
      pq_mats <- calc.p_q(H_curr, L_curr, d_effective) # Use d_effective
      pe_eq_peq_matrix <- calc.pe_eq_peq(pq_mats, E_curr, L_curr)
      Xlinear_errors[i] <- max(abs(diag_averaging(pe_eq_peq_matrix))) * delta
    } else {
      warning(paste("Skipping iteration i=", i, "due to invalid parameters: n_curr=", n_curr, ", L_curr=", L_curr, ", d=", d))
      Xssa_errors[i] <- NA
      Xlinear_errors[i] <- NA
    }
    
    
    end_time <- Sys.time()
    computation_times_secs[i] <- as.numeric(difftime(end_time, start_time, units = "secs"))
  }
  
  df_timing <- data.frame(n_value = n_vector, time_seconds = computation_times_secs)
  
  # --- Step 3: Visualization and Result Formatting ---
  df_recovery_error <- data.frame(
    N_iteration = n_vector, # Use n_vector as X-axis, corresponding to 'N' in the user's original code
    SSA_Error = Xssa_errors,
    Linear_Estimate = Xlinear_errors,
    SSA_Error_N = Xssa_errors * n_vector,
    Linear_Estimate_N = Xlinear_errors * n_vector
  )
  
  # Data frame for the original signal plot (10% of length)
  plot_len <- floor(0.1 * N_overall)
  if (plot_len == 0 && N_overall > 0) plot_len <- N_overall # If 10% is 0, but data exists, show all
  if (plot_len == 0 && N_overall == 0) {
    df_graph <- data.frame(t = integer(0), x = numeric(0)) # Empty df if no data
  } else {
    df_graph <- data.frame(t = 1:plot_len, x = X_perturbed_full[1:plot_len])
  }
  
  
  # Plot of the original signal
  title_p_graph <- sprintf("Plot: %s + %s", signal_type, noise_type)
  p_graph <- ggplot(df_graph, aes(x = t)) +
    geom_line(aes(y = x), linewidth = size_param) + # ggplot2 v3.4.0+ uses linewidth instead of size
    labs(
      title = title_p_graph,
      x = TeX(r"($t$)"), # Time axis t
      y = TeX(r"($X_t$)")  # Signal value X_t
    ) +
    theme_minimal(base_size = 12) + # Increase base font size
    theme(
      plot.title = element_text(hjust = 0.5, size = rel(1.2)), # Centered title, slightly larger
      axis.title = element_text(size = rel(1.1)), # Axes slightly larger
      legend.position = "none" # If legend is not needed
    )
  
  # Plot of maximum recovery error
  title_p_max_err_text <- sprintf("Maximum signal recovery error $L \\sim N/%f$", div)
  title_p_max_err <- TeX(title_p_max_err_text)
  p_max_recovery_error <- ggplot(df_recovery_error, aes(x = N_iteration)) +
    geom_line(aes(y = SSA_Error, color = "SSA Error"), linewidth = size_param) +
    geom_line(aes(y = Linear_Estimate, color = "Linear Approximation"), linewidth = size_param, linetype = "dashed") +
    labs(
      title = title_p_max_err,
      x = TeX(r"($N$)"), # Length of the analyzed segment
      y = "Maximum Error"
    ) +
    scale_color_manual(
      values = c("SSA Error" = "black", "Linear Approximation" = "red"),
      name = NULL # Remove legend title
    ) +
    theme_minimal(base_size = 12) +
    theme(
      legend.position = "top",
      legend.text = element_text(size = rel(0.9)),
      plot.title = element_text(hjust = 0.5, size = rel(1.2)),
      axis.title = element_text(size = rel(1.1))
    )
  
  # Plot of maximum recovery error multiplied by N
  title_p_max_err_mult_N_text <- sprintf("Maximum recovery error $L \\sim N/%f$, multiplied by $N$", div)
  title_p_max_err_mult_N <- TeX(title_p_max_err_mult_N_text)
  p_max_recovery_error_mult_N <- ggplot(df_recovery_error, aes(x = N_iteration)) +
    geom_line(aes(y = SSA_Error_N, color = "SSA Error"), linewidth = size_param) +
    geom_line(aes(y = Linear_Estimate_N, color = "Linear Approximation"), linewidth = size_param, linetype = "dashed") +
    labs(
      title = title_p_max_err_mult_N,
      x = TeX(r"($N$)"),
      y = TeX(r"(Max. Error $\times N$)")
    ) +
    scale_color_manual(
      values = c("SSA Error" = "black", "Linear Approximation" = "red"),
      name = NULL
    ) +
    theme_minimal(base_size = 12) +
    theme(
      legend.position = "top",
      legend.text = element_text(size = rel(0.9)),
      plot.title = element_text(hjust = 0.5, size = rel(1.1)), # Slightly smaller if title is long
      axis.title = element_text(size = rel(1.1))
    )
  
  return(list(
    p_graph = p_graph,
    p_max_recovery_error = p_max_recovery_error,
    p_max_recovery_error_mult_N = p_max_recovery_error_mult_N,
    df_graph = df_graph,
    df_recovery_error = df_recovery_error,
    df_timing = df_timing,
    N_overall = N_overall,
    d_rank = d,
    div_param = div,
    n_vector = n_vector,
    L_vector = L_vector
  ))
}


################################################################################
# Block 4: Example of using the main analysis function
################################################################################
# Comment or uncomment to run the example
# 
# # Parameters for the example
# N_example <- 700
# d_example <- 4
# div_example <- 4
# by_example <- 30 # Increase step for faster example
# delta_example <- 1.0
# size_param_example <- 0.7
# 
# # Generate signal H (polynomial of degree 3)
# theta_example <- c(2020/1000, -2141/10^4, 122/10^4, -1/10^3)
# H_example <- CreatePolynomialTimeSeries(coefficientVector = theta_example, N = N_example)
# 
# # Generate noise E (harmonic)
# df_E_param_example <- data.frame(
#   A = c(12, -6, -10, 4),
#   omega = c(1/sqrt(10), sqrt(3)/10, 1/31, sqrt(2)/5), # These are frequencies f = omega / (2*pi)
#   varphi = c(7*PI/5, 13*PI/17, PI/2, 4*PI/7), # Phases
#   alpha = rep.int(0, 4) # Decay/growth coefficients
# )
# 
# E_example <- CreateExponentialTimeSeries(
#   A = df_E_param_example$A,
#   alpha = df_E_param_example$alpha,
#   freq = df_E_param_example$omega, # Assuming omega here is freq (f_i)
#   angle = df_E_param_example$varphi,
#   N = N_example
# )
# 
# # Run the function
# analysis_results <- analyze_signal_noise(
#   H = H_example,
#   signal_type = "polyn (3)",
#   E = E_example,
#   noise_type = "harm",
#   d = d_example,
#   delta = delta_example,
#   div = div_example,
#   by = by_example,
#   size_param = size_param_example
# )
# 
# # Output results
# print("--- Signal Plot ---")
# print(analysis_results$p_graph)
# 
# print("--- Maximum Recovery Error Plot ---")
# print(analysis_results$p_max_recovery_error)
# 
# print("--- Maximum Recovery Error Multiplied by N Plot ---")
# print(analysis_results$p_max_recovery_error_mult_N)
# 
# print("--- Error Table (first rows) ---")
# print(head(analysis_results$df_recovery_error))
# 
# print("--- Computation Time Table (first rows) ---")
# print(head(analysis_results$df_timing))
# 
# print("--- Main Parameters ---")
# cat("N (overall length):", analysis_results$N_overall, "\n")
# cat("d (rank):", analysis_results$d_rank, "\n")
# cat("div (divisor):", analysis_results$div_param, "\n")
# cat("Vector n (first elements):", head(analysis_results$n_vector), "\n")
# cat("Vector L (first elements):", head(analysis_results$L_vector), "\n")
#
#
# print("--- Saving plots ---")
#
# cairo_pdf("Graph.pdf", width=6, height=4)
# print(analysis_results$p_graph)
# dev.off()
# 
# cairo_pdf("MaxRecoveryError.pdf", width=6, height=4)
# print(analysis_results$p_max_recovery_error)
# dev.off()
# 
# cairo_pdf("MaxRecoveryErrorMultN.pdf", width=6, height=4)
# print(analysis_results$p_max_recovery_error_mult_N)
# dev.off()
