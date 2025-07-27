library("lobstr")

a <- 1:10
b <- a
c <- b
d <- 1:10

lobstr::obj_addr(mean)
lobstr::obj_addr(base::mean)
lobstr::obj_addr(get("mean"))
lobstr::obj_addr(evalq(mean))
lobstr::obj_addr(match.fun("mean"))    


View(eraseNullRows)
View(m)

x <- setNames(a, letters[1:10])
lobstr::obj_size(x) # more compact than
lobstr::obj_size(a, letters[1:10]) # this

#mtcars[-1:4,]
rbind(mtcars[-1,],mtcars[1:4,])
mtcars[2:4,]
mtcars[mtcars$cyl == 4,]
mtcars[mtcars$cyl <= 5,]
mtcars[mtcars$cyl == c(4,6),]


# Note that if you don’t want names in the result, use unname() to remove them.

# The magrittr package35 provides a third option: the binary operator %>%, 
# which is called the pipe and is pronounced as “and then”.

View(plot)

# The way you most commonly see a call stack in R is by looking at 
# the traceback() after an error has occurred:

data(iris)
iris
numeric.cols <- names(iris)[sapply(iris, is.numeric)]
mapping <- setNames(1:length(numeric.cols), numeric.cols)


do.call(
  rbind,
  lapply(
    levels(iris[['Species']]),
    function(x, cols = numeric.cols)
    {
      df <- iris[iris[['Species']] == x, cols]
      res <- data.frame(
        do.call(
          list, 
          lapply(
            c('min', 'mean', 'median', 'max'), 
            function(f)
              setNames(
                lapply(df, f), 
                paste(cols, f, sep = '.')
              )
          )
        )
      )
      res[
        order(
          mapping[sapply(strsplit(names(res), "\\.(?=[^.]+$)", perl = TRUE), function(x) x[1])],
          sapply(strsplit(names(res), "\\."), function(x) x[3]),
          decreasing = c(FALSE, TRUE),
          method = "radix"
        )
      ]
    }
  )
)

premiumDataFrame <- data.frame(row.names = 1:3)

do.call(
  cbind,
  cbind.data.frame(
   premiumDataFrame,
   for(x in c('min', 'mean', 'median', 'max')){
     for(y in )
   }
  )
)

# rewrite the above do.call operation with for and premade data.frame

# idea: create an empty data.frame to which a columns with certain data will be applied
# via for-loop

x <- list(a = 1:10, beta = exp(-3:3), logic = c(TRUE,FALSE,FALSE,TRUE))
# compute the list mean for each list element
lapply(x, mean)
# median and quartiles for each list element
lapply(x, quantile, probs = 1:3/4)
lapply(x, quantile)
i39 <- sapply(3:9, seq) # list of vectors
lapply(i39, fivenum)
i39


x <- map(1:3, ~ runif(2))
str(x)


a3d <- array(1:24, c(2, 3, 4))
apply(a3d, 1, mean)
#> [1] 12 13
apply(a3d, c(1, 2), mean)
#>      [,1] [,2] [,3]
#> [1,]   10   12   14
#> [2,]   11   13   15

# r_iris2.html

numeric.cols <- names(iris)[sapply(iris, is.numeric)]
mapping <- setNames(1:length(numeric.cols), numeric.cols)


x <- list(
  c(0.512, 0.165, 0.717),
  c(0.064, 0.781, 0.427),
  c(0.890, 0.785, 0.495),
  "oops"
)

out <- rep(NA_real_, length(x))
for (i in seq_along(x)) {
  out[[i]] <- sum(x[[i]])
}
#> Error in sum(x[[i]]): invalid 'type' (character) of argument
out
#> [1] 1.39 1.27 2.17   NA
