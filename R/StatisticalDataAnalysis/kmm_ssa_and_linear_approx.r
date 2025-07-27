#%%
library(Rssa)
library(hrbrthemes)
library(ggplot2)
library(parallel)
library(reshape2)
library(latex2exp)
library(patchwork)
library(dplyr)

options(repr.plot.width = 20, repr.plot.height = 10)
PI <- asin(1)
THREADS <- detectCores()
true <- TRUE
false <- FALSE
RECALC <- false
DUMMY_GRAPHS <- false
HOLD <- 400

if (startsWith(getwd(), "/root")) {
  RECALC <- true
  DUMMY_GRAPHS <- true
  setwd("/root/redo/diploma/data")
} else {
  RECALC <- false
  DUMMY_GRAPHS <- false
  setwd("/home/kit/spbu/diploma/diploma/data")
}

dir.create("pic", showWarnings = FALSE)
dir.create("csv", showWarnings = FALSE)

save.df <- function(df, name) {
  if (!startsWith(name, "csv/")) {
    name <- paste0("csv/", name)
  }
  write.csv(df, name, row.names = FALSE)
  print(paste(">>", Sys.time(), "saved to", name))
  df
}

name.signal <- function(func, d, name) {
  list(func = func, d = d, name = name)
}

name.noise <- function(func, name, delta) {
  list(func = func, name = name, delta = delta)
}

df.join <- function(df.list) {
  do.call(rbind, df.list)
}

corner <- function(df) {
  c(as.numeric(df[, 1]), as.numeric(df[nrow(df), 2:ncol(df)]))
}

diag_averaging <- function(matr) {
  for (i in 0:(nrow(matr) + ncol(matr) - 2)) {
    matr[row(matr) + col(matr) - 2 == i] <- mean(matr[row(matr) + col(matr) - 2 == i])
  }
  matr
}

self.dot <- function(matrix, d) {
  ret <- matrix(0, nrow = nrow(matrix), ncol = nrow(matrix))
  for (i in d) {
    col_i <- matrix[, i]
    ret <- ret + col_i %*% t(col_i)
  }
  ret
}

calc.p_q <- function(H, d) {
  ssa.obj <- ssa(H)
  ssa.rec <- reconstruct(ssa.obj, groups = d)

  eig <- ssa.obj$sigma
  U <- ssa.obj$U[, 1:d]
  V <- calc.v(ssa.obj, 1:d)[, 1:d]

  P <- U %*% t(U)
  Q <- V %*% t(V)

  list(P = P, Q = Q)
}

calc.pe_eq <- function(pq, E) {
  P <- pq$P
  Q <- pq$Q
  E <- hankel(E)
  P %*% E + E %*% Q
}

calc.pe_eq_peq <- function(pq, E) {
  P <- pq$P
  Q <- pq$Q
  E <- hankel(E)
  P %*% E + E %*% Q - P %*% E %*% Q
}

calc.pe_eq.pe_eq_peq <- function(pq, E) {
  P <- pq$P
  Q <- pq$Q
  E <- hankel(E)
  PE_EQ <- P %*% E + E %*% Q
  PE_EQ_PEQ <- PE_EQ - P %*% E %*% Q
  list(PE_EQ = PE_EQ, PE_EQ_PEQ = PE_EQ_PEQ)
}

ssa.compare.pe_eq.pe_eq_peq.single_thread <- function(ns, signal, d, noise, delta) {
  F_n <- (1:max(ns)) |> sapply(signal)
  E_n <- (1:max(ns)) |> sapply(noise)

  df.per_n <- ns |> lapply(function(n) {
    f_n <- F_n[1:n]
    e_n <- E_n[1:n]
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  })

  do.call(rbind, df.per_n)
}

# !SSA


name.signal <- function(func, d, name) {
  list(func = func, d = d, name = name)
}

name.noise <- function(func, name, delta) {
  list(func = func, name = name, delta = delta)
}

df.join <- function(df.list) {
  do.call(rbind, df.list)
}

corner <- function(df) {
  c(as.numeric(df[, 1]), as.numeric(df[nrow(df), 2:ncol(df)]))
}

diag_averaging <- function(matr) {
  for (i in 0:(nrow(matr) + ncol(matr) - 2)) {
    matr[row(matr) + col(matr) - 2 == i] <- mean(matr[row(matr) + col(matr) - 2 == i])
  }
  matr
}

self.dot <- function(matrix, d) {
  ret <- matrix(0, nrow = nrow(matrix), ncol = nrow(matrix))
  for (i in d) {
    col_i <- matrix[, i]
    ret <- ret + col_i %*% t(col_i)
  }
  ret
}

calc.p_q <- function(H, d) {
  ssa.obj <- ssa(H)
  ssa.rec <- reconstruct(ssa.obj, groups = d)

  eig <- ssa.obj$sigma
  U <- ssa.obj$U[, 1:d]
  V <- calc.v(ssa.obj, 1:d)[, 1:d]

  P <- U %*% t(U)
  Q <- V %*% t(V)

  list(P = P, Q = Q)
}

calc.pe_eq <- function(pq, E) {
  P <- pq$P
  Q <- pq$Q
  E <- hankel(E)
  P %*% E + E %*% Q
}

calc.pe_eq_peq <- function(pq, E) {
  P <- pq$P
  Q <- pq$Q
  E <- hankel(E)
  P %*% E + E %*% Q - P %*% E %*% Q
}

calc.pe_eq.pe_eq_peq <- function(pq, E) {
  P <- pq$P
  Q <- pq$Q
  E <- hankel(E)
  PE_EQ <- P %*% E + E %*% Q
  PE_EQ_PEQ <- PE_EQ - P %*% E %*% Q
  list(PE_EQ = PE_EQ, PE_EQ_PEQ = PE_EQ_PEQ)
}

ssa.compare.pe_eq.pe_eq_peq.single_thread <- function(ns, signal, d, noise, delta) {
  F_n <- (1:max(ns)) |> sapply(signal)
  E_n <- (1:max(ns)) |> sapply(noise)

  df.per_n <- ns |> lapply(function(n) {
    f_n <- F_n[1:n]
    e_n <- E_n[1:n]
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  })

  do.call(rbind, df.per_n)
}

ssa.makeCluster <- function() {
  cl <- makeCluster(THREADS)
  clusterExport(cl,
                c("ssa", "reconstruct", "calc.v", "hankel", "PI", "name.signal", "name.noise", "true", "false", "mutate",
                  "corner", "diag_averaging", "self.dot", "calc.p_q", "calc.pe_eq.pe_eq_peq"),
                envir = environment()
  )
  cl
}

CLUSTER <- ssa.makeCluster()

# !COMPARE

ssa.compare.pe_eq.pe_eq_peq.synced <- function(ns, signal, d, noise, delta, seed = 0) {
  F_n <- (1:max(ns)) |> sapply(signal)
  E_n <- (1:max(ns)) |> sapply(noise)

  compare.per.n <- function(n) {
    set.seed(n + seed)

    f_n <- F_n[1:n]
    e_n <- E_n[1:n]
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  }

  df.per_n <- lapply(ns, compare.per.n)

  do.call(rbind, df.per_n)
}

ssa.compare.pe_eq.pe_eq_peq.synced.with_maker <- function(ns, signal_maker, d, noise, delta, seed = 0) {
  E_n <- (1:max(ns)) |> sapply(noise)

  compare.per.n <- function(n) {
    set.seed(n + seed)

    signal <- signal_maker(n)$func
    F_n <- (1:n) |> sapply(signal)
    f_n <- F_n[1:n]
    e_n <- E_n[1:n]
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  }

  ns |>
    lapply(compare.per.n) |>
    df.join()
}

ssa.compare.pe_eq.pe_eq_peq.with_const_back_noise <- function(ns, signal, d, noise_pos, noise_size, seed = 0, cl = CLUSTER) {
  F_n <- (1:max(ns)) |> sapply(signal)

  compare.per.n <- function(n) {
    set.seed(n + seed)

    f_n <- F_n[1:n]
    e_n <- noise.const(1:n, pos = n - noise_pos, size = noise_size)
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  }

  clusterExport(cl, c("compare.per.n", "noise.const",
                      "ns", "signal", "d", "noise_pos", "noise_size", "seed",
                      "F_n"), envir = environment())
  df.per_n <- cl |> parLapply(ns, compare.per.n)

  do.call(rbind, df.per_n)
}

ssa.compare.pe_eq.pe_eq_peq <- function(ns, signal, d, noise, delta, seed = 0, cl = CLUSTER) {
  F_n <- (1:max(ns)) |> sapply(signal)
  E_n <- (1:max(ns)) |> sapply(noise)

  compare.per.n <- function(n) {
    set.seed(n + seed)

    f_n <- F_n[1:n]
    e_n <- E_n[1:n]
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  }

  clusterExport(cl, c("compare.per.n",
                      "ns", "signal", "d", "noise", "delta", "seed",
                      "F_n", "E_n"), envir = environment())
  df.per_n <- cl |> parLapply(ns, compare.per.n)

  do.call(rbind, df.per_n)
}

ssa.compare.pe_eq.pe_eq_peq.multisample <- function(sample_size, ns, signal, d, noise, delta, cl = CLUSTER) {

  lambda <- function(seed, ns, signal, d, noise, delta) {
    ssa.compare.pe_eq.pe_eq_peq.synced(ns = ns, signal = signal, d = d, noise = noise, delta = delta, seed = seed)
  }

  clusterExport(cl, c("ssa.compare.pe_eq.pe_eq_peq.synced", "lambda",
                      "ns", "signal", "d", "noise", "delta"), envir = environment())

  dfs <- cl |> parLapply(1:sample_size, lambda, ns = ns, signal = signal, d = d, noise = noise, delta = delta)

  do.call(rbind, dfs)
}

ssa.compare.pe_eq.pe_eq_peq.multisample <- function(sample_size, ns, signal, d, noise, delta, cl = CLUSTER) {

  lambda <- function(seed, ns, signal, d, noise, delta) {
    ssa.compare.pe_eq.pe_eq_peq.synced(ns = ns, signal = signal, d = d, noise = noise, delta = delta, seed = seed)
  }

  clusterExport(cl, c("ssa.compare.pe_eq.pe_eq_peq.synced", "lambda",
                      "ns", "signal", "d", "noise", "delta"), envir = environment())

  dfs <- cl |> parLapply(1:sample_size, lambda, ns = ns, signal = signal, d = d, noise = noise, delta = delta)

  do.call(rbind, dfs)
}

ssa.compare.random_multisample <- function(sample.n, ns, signal, noise, delta, seed = 0, cl = CLUSTER) {
  set.seed(seed)

  delta <- delta * noise$delta
  F_series <- 1:max(ns) |>
    sapply(signal$func)
  E_series <- 1:sample.n |>
    lapply(function(sample.i) {
      1:max(ns) |>
        sapply(noise$func)
    })
  d <- signal$d

  clusterExport(cl, c("sample.n", "ns", "signal", "noise", "delta",
                      "F_series", "d", "E_series"
  ), envir = environment())

  ns |>
    lapply(function(n) {
      clusterExport(cl, c("n"), envir = environment())
      df <- cl |>
        parLapply(1:sample.n, function(sample.i) {
          f_n <- F_series[1:n]
          e_n <- E_series[[sample.i]][1:n]
          x_n <- f_n + delta * e_n

          ssa.obj <- ssa(x_n, kind = "1d-ssa")
          ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
          pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

          data.frame(
            N = 1:n,
            old.ssa = ssa.f.reconstructed - f_n,
            old.peeq = pe_eq.pe_eq_peq$PE_EQ |>
              diag_averaging() |>
              corner() * delta,
            old.peeqpeq = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
              diag_averaging() |>
              corner() * delta
          ) |> mutate(
            ssa = abs(old.ssa),
            peeq = abs(old.peeq),
            peeqpeq = abs(old.peeqpeq)
          )
        }) |>
        df.join()

      info.df <- 1:n |>
        lapply(function(sub.n) {
          per_n.df <- df |> slice(seq(sub.n, n * sample.n, by = sample.n))
          data.frame(
            N = sub.n,

            ssa.mean = per_n.df |> pull(ssa) |> mean(),
            ssa.var = per_n.df |> pull(ssa) |> var(),
            peeq.mean = per_n.df |> pull(peeq) |> mean(),
            peeq.var = per_n.df |> pull(peeq) |> var(),
            peeqpeq.mean = per_n.df |> pull(peeqpeq) |> mean(),
            peeqpeq.var = per_n.df |> pull(peeqpeq) |> var(),

            old.ssa.mean = per_n.df |> pull(old.ssa) |> mean() |> abs(),
            old.ssa.var = per_n.df |> pull(old.ssa) |> var(),
            old.peeq.mean = per_n.df |> pull(old.peeq) |> mean() |> abs(),
            old.peeq.var = per_n.df |> pull(old.peeq) |> var(),
            old.peeqpeq.mean = per_n.df |> pull(old.peeqpeq) |> mean() |> abs(),
            old.peeqpeq.var = per_n.df |> pull(old.peeqpeq) |> var()
          )
        }) |>
        df.join()

      data.frame(
        N = n,
        ssa.mean = info.df |> pull(ssa.mean) |> max(),
        ssa.var = info.df |> pull(ssa.var) |> max(),
        peeq.mean = info.df |> pull(peeq.mean) |> max(),
        peeq.var = info.df |> pull(peeq.var) |> max(),
        peeqpeq.mean = info.df |> pull(peeqpeq.mean) |> max(),
        peeqpeq.var = info.df |> pull(peeqpeq.var) |> max(),

        old.ssa.mean = info.df |> pull(old.ssa.mean) |> max(),
        old.ssa.var = info.df |> pull(old.ssa.var) |> max(),
        old.peeq.mean = info.df |> pull(old.peeq.mean) |> max(),
        old.peeq.var = info.df |> pull(old.peeq.var) |> max(),
        old.peeqpeq.mean = info.df |> pull(old.peeqpeq.mean) |> max(),
        old.peeqpeq.var = info.df |> pull(old.peeqpeq.var) |> max()
      )
    }) |>
    df.join()
}

plot.ssa.compare.random_multisample <- function(df, threshold = HOLD, size = 1) {
  if (DUMMY_GRAPHS) {
    return(data.frame(x = seq_len(nrow(df)), y = seq_len(nrow(df))^2) |>
             ggplot(aes(x = x, y = y)) +
             geom_line())
  }

  plot.mean <- df |>
    select(N, ssa.mean, peeq.mean, peeqpeq.mean) |>
    melt(id.vars = "N",
         value.name = "Value",
         variable.name = "Method") |>
    filter(N >= threshold) |>
    ggplot(aes(x = N, y = Value, group = Method, color = Method)) +
    geom_line(linewidth = 1.1 * size, alpha = 0.5, show.legend = FALSE) +
    scale_color_manual(values = c("green", "red", "blue"),
                       breaks = c("ssa.mean", "peeq.mean", "peeqpeq.mean")
    ) +
    theme_ipsum(base_size = 20 * size, axis_title_size = 18 * size) +
    theme(legend.position = "right") +
    ylab("Средние ошибки восстановления")

  plot.var <- df |>
    select(N, ssa.var, peeq.var, peeqpeq.var) |>
    melt(id.vars = "N",
         value.name = "Value",
         variable.name = "Method") |>
    filter(N >= threshold) |>
    ggplot(aes(x = N, y = Value, group = Method, color = Method)) +
    geom_line(linewidth = 1.1 * size, alpha = 0.5, show.legend = TRUE) +
    scale_color_manual(values = c("green", "red", "blue"),
                       breaks = c("ssa.var", "peeq.var", "peeqpeq.var"),
                       labels = c(
                         TeX("SSA"),
                         "НЛП",
                         "ПЛП")
    ) +
    theme_ipsum(base_size = 20 * size, axis_title_size = 18 * size) +
    theme(legend.position = "right") +
    guides(color = guide_legend(title = "Методы")) +
    ylab("Дисперсия ошибок восстановления")

  plot.mean + plot.var
}

plot.ssa.compare.random_multisample_oldstyle <- function(df, threshold = HOLD, size = 1) {
  df.plot <- data.frame(N = df$N,
                        ssa.mean = df$old.ssa.mean, peeq.mean = df$old.peeq.mean, peeqpeq.mean = df$old.peeqpeq.mean,
                        ssa.var = df$old.ssa.var, peeq.var = df$old.peeq.var, peeqpeq.var = df$old.peeqpeq.var
  )
  plot.ssa.compare.random_multisample(df.plot, threshold = threshold, size = size)
}

# !MULTISAMPLE REBUILD

ssa.compare.pe_eq.pe_eq_peq.synced.per_n <- function(n, F_n, d, E_n, delta, seed = 0) {
  f_n <- F_n[1:n]
  e_n <- E_n[1:n]
  x_n <- f_n + delta * e_n

  ssa.obj <- ssa(x_n, kind = "1d-ssa")
  ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
  pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

  data.frame(
    ssa = abs(ssa.f.reconstructed - f_n),
    peeq = pe_eq.pe_eq_peq$PE_EQ |>
      diag_averaging() |>
      corner() |>
      abs() * delta,
    peeqpeq = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
      diag_averaging() |>
      corner() |>
      abs() * delta
  )
}

ssa.compare.pe_eq.pe_eq_peq.multisample.per_n <- function(n, sample_size, signal, d, noise.per_sample, delta, cl = CLUSTER) {

  per_sample <- function(n, sample_size, signal, d, noise, delta) {

  }

  lambda <- function(n, sample_size, signal, d, noise, delta) {
    clusterExport(cl, c("n"), envir = environment())

    cl |>
      parLapply(1:sample_size, ssa.compare.pe_eq.pe_eq_peq.synced.per_n, n = n,)
    ssa.compare.pe_eq.pe_eq_peq.synced(ns = ns, signal = signal, d = d, noise = noise, delta = delta, seed = n)
  }

  clusterExport(cl, c("ssa.compare.pe_eq.pe_eq_peq.synced.per_n", "lambda", "per_sample",
                      "ns", "signal", "d", "noise", "delta"), envir = environment())

  dfs <- cl |> parLapply(1:ns, lambda, sample_size = sample_size, signal = signal, d = d, noise = noise, delta = delta)

  do.call(rbind, dfs)
}

# !PLOT

save.plot <- function(plot, name, width = 40, height = 20) {
  print(paste0("++ ", name))
  ggsave(paste0("pic/", name), plot, bg = "#FFFFFF", width = width, height = height, units = "cm", dpi = 150)
  plot
}

plot.save <- save.plot

plot.compare.pe_eq.pe_eq_peq <- function(df, threshold = HOLD, size = 1) {
  if (DUMMY_GRAPHS) {
    return(data.frame(x = seq_len(nrow(df)), y = seq_len(nrow(df))^2) |>
             ggplot(aes(x = x, y = y)) +
             geom_line()
    )
  }

  df |>
    melt(id.vars = "N",
         value.name = "Value",
         variable.name = "Method") |>
    filter(N >= threshold) |>
    ggplot(aes(x = N, y = Value, group = Method, color = Method)) +
    geom_line(linewidth = 1.1 * size, alpha = 0.5) +
    scale_color_manual(values = c("green", "red", "blue"),
                       breaks = c("SSA", "PE_EQ", "PE_EQ_PEQ"),
                       labels = c(
                         TeX("SSA"),
                         "НЛП",
                         "ПЛП")
    ) +
    theme_ipsum(base_size = 20 * size, axis_title_size = 18 * size) +
    theme(legend.position = "right") +
    guides(color = guide_legend(title = "Методы")) +
    ylab("Ошибки восстановления")
}

plot.compare.pe_eq.pe_eq_peq.relative <- function(df, threshold = HOLD) {
  df |>
    melt(id.vars = "N",
         value.name = "Value",
         variable.name = "Method") |>
    filter(N >= threshold) |>
    ggplot(aes(x = N, y = Value, group = Method, color = Method)) +
    geom_line(linewidth = 1.1, alpha = 0.5) +
    scale_color_manual(values = c("green", "red", "blue"),
                       breaks = c("SSA", "PE_EQ", "PE_EQ_PEQ"),
                       labels = c(
                         TeX("SSA"),
                         "НЛП",
                         "ПЛП")
    ) +
    theme_ipsum(base_size = 20, axis_title_size = 18) +
    theme(legend.position = "right") +
    guides(color = guide_legend(title = "Методы")) +
    ylab("Ошибки восстановления")
}

plot.compare.pe_eq.pe_eq_peq.multisample <- function(df, threshold = HOLD, size = 1) {
  df |>
    filter(N >= threshold) |>
    melt(id.vars = "N", measure.vars = c("SSA", "PE_EQ", "PE_EQ_PEQ")) |>
    group_by(N, variable) |>
    summarise(Mean = mean(value),
              SD = sd(value)) |>
    ggplot(aes(x = N, y = Mean, color = variable)) +
    geom_line(linewidth = 1.1 * size, alpha = 0.5) +
    geom_errorbar(aes(ymin = Mean - SD,
                      ymax = Mean + SD),
                  width = 20 * size, alpha = 0.5, size = 1.1) +
    scale_color_manual(values = c("green", "red", "blue"),
                       breaks = c("SSA", "PE_EQ", "PE_EQ_PEQ"),
                       labels = c(
                         TeX("$SSA$"),
                         "НЛП",
                         "ПЛП")
    ) +
    theme_ipsum(base_size = 20 * size, axis_title_size = 18 * size) +
    theme(legend.position = "right") +
    guides(color = guide_legend(title = "Методы")) +
    ylab("Ошибки восстановления")
}

# !SIGNALS

signal.maker <- function(signal) {
  function(n) {
    signal
  }
}

signal.const <- (function(n) {
  n |> sapply(function(n) 1)
}) |> name.signal(1, "const")
1
signal.exp <- (function(n, a = 1.011) {
  a^n
}) |> name.signal(1, "exp")
# № 1.011
make.signal.exp_discr <- (function(N, a = 1.05, T = 10) {
  signal <- (function(n) {
    ifelse(n <= N, a^(1.0 * T * n / N), a^T)
  }) |> name.signal(1, "expdiscr")
  signal
})
#signal.exp_d <- (function(n, a = 1.011, T = ) {
#  a^n
#}) |> name.signal(1, "exp_d")

signal.linear <- (function(n) {
  n |> sapply(function(n) n)
}) |> name.signal(2, "linear")

signal.sinusoid <- (function(n, omega = 1.0 / sqrt(6), gamma = 0) {
  cos(2 * PI * omega * n + gamma)
}) |> name.signal(2, "sin")

signal.expsin <- (function(n, a = 1.011, omega = 1.0 / sqrt(6), gamma = 0) {
  a^n * cos(2 * PI * omega * n + gamma)
}) |> name.signal(2, "expsin")

signal.sqr <- (function(n) {
  n * n
}) |> name.signal(3, "sqr")

# !NOISES


noise.const <- (function(n, pos = 50, size = 10) {
  ifelse(n == pos, size, 0)
}) |> name.noise("const", 1)

noise.const.10 <- (function(n, pos = 10, size = 100) {
  ifelse(n == pos, size, 0)
}) |> name.noise("const", 1)

make.noise.const_back.10 <- (function(N, pos = 10, size = 100) {
  noise <- (function(n) {
    ifelse(n == N - pos, size, 0)
  }) |> name.noise(name = "constback", delta = 1)
  noise
})

noise.sinusoid <- (function(n, omega = 1.0 / sqrt(99), gamma = PI) {
  cos(2 * PI * omega * n + gamma)
}) |> name.noise("sin", 0.3)

noise.exp <- (function(n, base = 0.99) {
  n |> sapply(function(n) base^n)
}) |> name.noise("exp", 1)

noise.exp.10 <- (function(n, base = 0.999) {
  n |> sapply(function(n) base^n)
}) |> name.noise("exp", 1)

noise.gauss <- (function(n) {
  n |> sapply(function(n) rnorm(1))
}) |> name.noise("gauss", 0.2)

noise.uniform <- (function(n) {
  n |> sapply(function(n) runif(1, -sqrt(6), sqrt(6)))
}) |> name.noise("uniform", 0.2)

make.noise.const_back <- (function(N, pos = 50, size = 10) {
  noise <- (function(n) {
    ifelse(n == N - pos, size, 0)
  }) |> name.noise(name = "constback", delta = 1)
  noise
})

make.noise.const_back.maker <- function(pos = 50, size = 10) {
  (function(N) {
    noise <- (function(n) {
      ifelse(n == pos, size, 0)
    }) |> name.noise(name = "constback", delta = 1)
    noise
  })
}

noise.maker <- function(noise) {
  function(n) {
    noise
  }
}

noises.det <- list(noise.const, noise.sinusoid, noise.exp)
noises.rnd <- list(noise.gauss, noise.uniform)

# !PLAN

#%%
ssa.compare.random_multisample.with_maker <- function(sample.n, ns, signal_maker, noise, delta, seed = 0, cl = CLUSTER) {
  set.seed(seed)

  delta <- delta * noise$delta

  E_series <- 1:sample.n |>
    lapply(function(sample.i) {
      1:max(ns) |>
        sapply(noise$func)
    })
  d <- signal_maker(1)$d

  clusterExport(
    cl,
    c("sample.n", "ns", "noise", "delta", "signal_maker", "d", "E_series"),
    envir = environment()
  )

  ns |>
    lapply(function(n) {
      signal <- signal_maker(n)
      F_series <- 1:n |> sapply(signal$func)
      clusterExport(cl, c("n", "signal", "F_series"), envir = environment())
      df <- cl |>
        parLapply(1:sample.n, function(sample.i) {
          f_n <- F_series[1:n]
          e_n <- E_series[[sample.i]][1:n]
          x_n <- f_n + delta * e_n

          ssa.obj <- ssa(x_n, kind = "1d-ssa")
          ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
          pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

          data.frame(
            N = 1:n,
            old.ssa = ssa.f.reconstructed - f_n,
            old.peeq = pe_eq.pe_eq_peq$PE_EQ |>
              diag_averaging() |>
              corner() * delta,
            old.peeqpeq = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
              diag_averaging() |>
              corner() * delta
          ) |> mutate(
            ssa = abs(old.ssa),
            peeq = abs(old.peeq),
            peeqpeq = abs(old.peeqpeq)
          )
        }) |>
        df.join()

      info.df <- 1:n |>
        lapply(function(sub.n) {
          per_n.df <- df |> slice(seq(sub.n, n * sample.n, by = sample.n))
          data.frame(
            N = sub.n,

            ssa.mean = per_n.df |> pull(ssa) |> mean(),
            ssa.var = per_n.df |> pull(ssa) |> var(),
            peeq.mean = per_n.df |> pull(peeq) |> mean(),
            peeq.var = per_n.df |> pull(peeq) |> var(),
            peeqpeq.mean = per_n.df |> pull(peeqpeq) |> mean(),
            peeqpeq.var = per_n.df |> pull(peeqpeq) |> var(),

            old.ssa.mean = per_n.df |> pull(old.ssa) |> mean() |> abs(),
            old.ssa.var = per_n.df |> pull(old.ssa) |> var(),
            old.peeq.mean = per_n.df |> pull(old.peeq) |> mean() |> abs(),
            old.peeq.var = per_n.df |> pull(old.peeq) |> var(),
            old.peeqpeq.mean = per_n.df |> pull(old.peeqpeq) |> mean() |> abs(),
            old.peeqpeq.var = per_n.df |> pull(old.peeqpeq) |> var()
          )
        }) |>
        df.join()

      data.frame(
        N = n,

        ssa.mean = info.df |> pull(ssa.mean) |> max(),
        ssa.var = info.df |> pull(ssa.var) |> max(),
        peeq.mean = info.df |> pull(peeq.mean) |> max(),
        peeq.var = info.df |> pull(peeq.var) |> max(),
        peeqpeq.mean = info.df |> pull(peeqpeq.mean) |> max(),
        peeqpeq.var = info.df |> pull(peeqpeq.var) |> max(),

        old.ssa.mean = info.df |> pull(old.ssa.mean) |> max(),
        old.ssa.var = info.df |> pull(old.ssa.var) |> max(),
        old.peeq.mean = info.df |> pull(old.peeq.mean) |> max(),
        old.peeq.var = info.df |> pull(old.peeq.var) |> max(),
        old.peeqpeq.mean = info.df |> pull(old.peeqpeq.mean) |> max(),
        old.peeqpeq.var = info.df |> pull(old.peeqpeq.var) |> max()
      )
    }) |>
    df.join()
}


plan.callback.multisample_alt.with_maker <- function(signal_maker, noise, delta, ns = multisample.ns) {
  signal <- signal_maker(1)
  name <- paste0("peeqpeq_3_", signal$name, "_", noise$name)
  name.df <- paste0("csv/", name, "_", delta * noise$delta, ".csv")
  name.pic <- paste0(name, ".jpg")

  df <- data.frame()
  if (RECALC | !file.exists(name.df)) {
    print(paste("- ", Sys.time(), "recalculating", name.df))
    df <- ssa.compare.random_multisample.with_maker(multisample, ns, signal_maker, noise, delta) |>
      save.df(name.df)
  } else {
    print(paste("**", Sys.time(), "loading", name.df))
    df <- read.csv(name.df)
  }

  df |>
    plot.ssa.compare.random_multisample() |>
    save.plot(name.pic) |>
    print()

  df |>
    plot.ssa.compare.random_multisample_oldstyle() |>
    save.plot(paste0(name, "_old.jpg")) |>
    print()
}

# callback: function(signal, noise)
plan.experiments <- function(callback, signals, noises, delta = 1, ns = ns, with_make = false) {
  start <- Sys.time()
  . <- signals |>
    sapply(function(signal) {
      noises |> sapply(function(noise) {
        print.signal <- signal
        if (!is.list(signal)) {
          print.signal <- signal(1)
        }
        print.noise <- noise
        if (!is.list(noise)) {
          print.noise <- noise(1)
        }
        print(paste(">>", Sys.time(), "start", print.signal$name, print.noise$name))
        callback(signal, noise, delta, ns = ns)
      })
    })
  end <- Sys.time()
  print(paste(end - start, "|", (end - start) / (length(signals) * length(noises))))
  print("-----")
}

plan.callback.simple <- function(signal, noise, delta, ns = ns) {
  name <- paste0("peeqpeq_3_", signal$name, "_", noise$name)
  name.df <- paste0("csv/", name, "_", delta * noise$delta, ".csv")
  name.pic <- paste0(name, ".jpg")

  df <- data.frame()
  if (RECALC ||
    !file.exists(name.df) ||
    (ncol(read.csv(name.df)) != 4)) {
    print(paste("- ", Sys.time(), "recalculating", name.df))
    df <- ssa.compare.pe_eq.pe_eq_peq(ns, signal = signal$func, d = signal$d, noise = noise$func, delta = delta * noise$delta) |>
      save.df(name.df)
  } else {
    print(paste("**", Sys.time(), "loading", name.df))
    df <- read.csv(name.df)
  }
  df |>
    plot.compare.pe_eq.pe_eq_peq() |>
    save.plot(name.pic) |>
    print()
}

plan.callback.multisample <- function(signal, noise, delta, ns = multisample.ns) {
  name <- paste0("peeqpeq_3_old_", signal$name, "_", noise$name)
  name.df <- paste0("csv/", name, "_", delta * noise$delta, ".csv")
  name.pic <- paste0(name, ".jpg")

  df <- data.frame()
  if (RECALC | !file.exists(name.df)) {
    df <- ssa.compare.pe_eq.pe_eq_peq.multisample(
      multisample, ns,
      signal = signal$func, d = signal$d,
      noise = noise$func, delta = delta * noise$delta
    ) |>
      save.df(name.df)
  } else {
    print(paste("**", Sys.time(), "loading", name.df))
    df <- read.csv(name.df)
  }

  df |>
    plot.compare.pe_eq.pe_eq_peq.multisample() |>
    save.plot(paste0(name, ".jpg")) |>
    print()
}

plan.callback.multisample_alt <- function(signal, noise, delta, ns = multisample.ns) {
  name <- paste0("peeqpeq_3_", signal$name, "_", noise$name)
  name.df <- paste0("csv/", name, "_", delta * noise$delta, ".csv")
  name.pic <- paste0(name, ".jpg")

  df <- data.frame()
  if (RECALC | !file.exists(name.df)) {
    print(paste("- ", Sys.time(), "recalculating", name.df))
    df <- ssa.compare.random_multisample(multisample, ns, signal, noise, delta) |>
      save.df(name.df)
  } else {
    print(paste("**", Sys.time(), "loading", name.df))
    df <- read.csv(name.df)
  }

  df |>
    plot.ssa.compare.random_multisample() |>
    save.plot(paste0(name, ".jpg")) |>
    print()

  df |>
    plot.ssa.compare.random_multisample_oldstyle() |>
    save.plot(paste0(name, "_old.jpg")) |>
    print()
}


ssa.compare.pe_eq.pe_eq_peq.with_signal_maker <- function(ns, signal_maker, d, noise, delta, seed = 0, cl = CLUSTER) {
  E_n <- (1:max(ns)) |> sapply(noise)

  compare.per.n <- function(n) {
    set.seed(n + seed)

    signal <- signal_maker(n)
    f_n <- (1:n) |> sapply(signal$func)
    e_n <- E_n[1:n]
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  }

  clusterExport(cl, c("compare.per.n",
                      "ns", "signal_maker", "d", "noise", "delta", "seed",
                      "E_n"), envir = environment())
  df.per_n <- cl |> parLapply(ns, compare.per.n)

  do.call(rbind, df.per_n)
}

plan.callback.simple.with_maker <- function(signal_maker, noise, delta, ns = ns) {
  signal <- signal_maker(1)
  name <- paste0("peeqpeq_3_", signal$name, "_", noise$name)
  name.df <- paste0("csv/", name, "_", delta * noise$delta, ".csv")
  name.pic <- paste0(name, ".jpg")

  df <- data.frame()
  if (RECALC ||
    !file.exists(name.df) ||
    (ncol(read.csv(name.df)) != 4)) {
    print(paste(Sys.time(), "recalculating", name.df))
    df <- ssa.compare.pe_eq.pe_eq_peq.with_signal_maker(ns, signal_make = signal_maker, d = signal$d, noise = noise$func, delta = delta * noise$delta) |>
      save.df(name.df)
  } else {
    print(paste("**", Sys.time(), "loading", name.df))
    df <- read.csv(name.df)
  }
  df |>
    plot.compare.pe_eq.pe_eq_peq() |>
    save.plot(name.pic) |>
    print()
}

ssa.compare.pe_eq.pe_eq_peq.with_both_makers <- function(ns, signal_maker, d, noise_maker, delta, seed = 0, cl = CLUSTER) {

  compare.per.n <- function(n) {
    set.seed(n + seed)

    signal <- signal_maker(n)
    noise <- noise_maker(n)
    f_n <- (1:n) |> sapply(signal$func)
    e_n <- (1:n) |> sapply(noise$func)
    x_n <- f_n + delta * e_n

    ssa.obj <- ssa(x_n, kind = "1d-ssa")
    ssa.f.reconstructed <- reconstruct(ssa.obj, groups = list(1:d))$F1
    pe_eq.pe_eq_peq <- calc.pe_eq.pe_eq_peq(calc.p_q(f_n, d), e_n)

    data.frame(
      N = n,
      SSA = max(abs(ssa.f.reconstructed - f_n)),
      PE_EQ = pe_eq.pe_eq_peq$PE_EQ |>
        diag_averaging() |>
        abs() |>
        max() * delta,
      PE_EQ_PEQ = pe_eq.pe_eq_peq$PE_EQ_PEQ |>
        diag_averaging() |>
        abs() |>
        max() * delta
    )
  }

  clusterExport(cl, c("compare.per.n",
                      "ns", "signal_maker", "d", "noise_maker", "delta", "seed"), envir = environment())
  df.per_n <- cl |> parLapply(ns, compare.per.n)

  do.call(rbind, df.per_n)
}

plan.callback.simple.with_both_makers <- function(signal_maker, noise_maker, delta, ns = ns) {
  signal <- signal_maker(1)
  noise <- noise_maker(1)
  name <- paste0("peeqpeq_3_", signal$name, "_", noise$name)
  name.df <- paste0("csv/", name, "_", delta * noise$delta, ".csv")
  name.pic <- paste0(name, ".jpg")

  df <- data.frame()
  if (RECALC ||
    !file.exists(name.df) ||
    (ncol(read.csv(name.df)) != 4)) {
    print(paste(Sys.time(), "recalculating", name.df))
    df <- ssa.compare.pe_eq.pe_eq_peq.with_both_makers(ns, signal_make = signal_maker, d = signal$d, noise_maker = noise_maker, delta = delta * noise$delta) |>
      save.df(name.df)
  } else {
    print(paste("**", Sys.time(), "loading", name.df))
    df <- read.csv(name.df)
  }
  df |>
    plot.compare.pe_eq.pe_eq_peq() |>
    save.plot(name.pic) |>
    print()
}

#!

ns <- seq(100, 1500, by = 100)
ns.exp <- seq(100, 1300, by = 100)
multisample.ns <- seq(100, 800, by = 100)
multisample <- 50


# plan.experiments(plan.callback.simple, list(signal.exp), list(noise.const.10), 1, ns = ns.exp)
# plan.experiments(plan.callback.simple, list(signal.exp), list(noise.exp.10), 1, ns = ns.exp)
# plan.experiments(plan.callback.simple, list(signal.exp), list(noise.sinusoid), 1, ns = ns.exp)
# plan.experiments(plan.callback.simple.with_both_makers, list(signal.maker(signal.exp)), list(make.noise.const_back.10), 1, ns = ns.exp)
#
# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(noise.maker(noise.const.10), make.noise.const_back.10), 0.5, ns = ns.exp)
# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(noise.maker(noise.exp.10)), 0.1, ns = ns.exp)
# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(noise.maker(noise.sinusoid)), 0.5, ns = ns.exp)

plan.experiments(plan.callback.multisample_alt, list(signal.exp), noises.rnd, 1, ns = multisample.ns)
plan.experiments(plan.callback.multisample_alt.with_maker, list(make.signal.exp_discr), noises.rnd, 0.5, ns = multisample.ns)


# plan.experiments(plan.callback.simple.with_both_makers, list(signal.maker(signal.exp)), list(make.noise.const_back.10), 1, ns = ns.exp)
# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(make.noise.const_back.10), 1, ns = ns.exp)


# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(noise.maker(noise.const), noise.maker(noise.exp)), 1000, ns = ns.exp)
# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(noise.maker(noise.sinusoid)), 0.3, ns = ns.exp)
# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(make.noise.const_back), 1000, ns = ns.exp)

# plan.experiments(plan.callback.multisample_alt, list(signal.exp), noises.rnd, 1, ns = multisample.ns)


# plan.experiments(plan.callback.simple, list(signal.exp), list(noise.sinusoid), 1, ns)

# plan.experiments(plan.callback.simple, list(signal.const, signal.sinusoid), noises.det, 0.5, ns)
# plan.experiments(plan.callback.multisample_alt, list(signal.const, signal.sinusoid), noises.rnd, 0.5, multisample.ns)
# plan.experiments(plan.callback.simple, list(signal.exp, signal.linear, signal.sqr), noises.det, 1, ns)
# plan.experiments(plan.callback.multisample_alt, list(signal.exp, signal.linear, signal.sqr), noises.rnd, 1, multisample.ns)
#
# plan.experiments(plan.callback.simple.with_both_makers, list(make.signal.exp_discr), list(noise.maker(noise.const)), 1, ns, with_make = true)
# plan.experiments(plan.callback.simple.with_both_makers, list(signal.maker(signal.const), signal.maker(signal.exp), make.signal.exp_discr), list(make.noise.const_back), 0.5, ns)
# plan.experiments(plan.callback.simple.with_both_makers, list(signal.maker(signal.exp), make.signal.exp_discr), list(make.noise.const_back), 1, ns)
# plan.experiments(plan.callback.simple.with_maker, list(make.signal.exp_discr), noises.det, 1, ns, with_make = true)
# plan.experiments(plan.callback.multisample_alt.with_maker, list(make.signal.exp_discr), noises.rnd, 1, multisample.ns, with_make = true)