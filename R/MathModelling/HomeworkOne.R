# Упражнение 1 (e)
x <- 1e-20
m<-exp(log(1+x)*(1/x))
m<-exp(log1p(x)*(1/x))
# Упражнение 2 (Кость)
dieMean<-c()
for(i in 1:6){
  dieMean <- c(dieMean, 1+mean(rgeom(10^i,1/6)))
}
dieMean
# Упражнение 3 (Крэпс)
Craps<-function(){
  # Первый бросок
  score<-sum(sample(1:6,2))
  # Случай "Выигрыш"
  if(score %in% c(7,11)){
    return(FALSE)
  }
  # Случай "Проигрыш"
  else if(score %in% c(2,3,12)){
    return(TRUE)
  }
  else{
    # Случай "Пойнт"
    scorePoint<-sum(sample(1:6,2))
    while(!(scorePoint %in% c(7, score))){
      scorePoint<-sum(sample(1:6,2))
    }
    if(scorePoint==7){
      return(TRUE)
    }
    else{
      return(FALSE)
    }
  }
}
result<-c()
for(i in 1:5){
  num<-10^i
  prob<-mean(replicate(num, Craps()))
  result<-c(result, prob)
}
result

# Упражнение 4 (Фальшивомонетчик)
n<-100
m<-60
r<-20
dbinom(r, n, m/n)
# Упражнение 5 (Желатин)
res<-c()
lambda<-3
for(i in 1:5){
  temp<-rpois(10^i,lambda)
  res<-c(res, length(temp[temp==3])/length(temp))
}
res
# Упражнение 6 (Булочник)
res<-c()
lambda<-1
for(i in 1:5){
  temp<-rpois(10^i,lambda)
  res<-c(res, length(temp[(temp%%2)==0])/length(temp))
}
res
# Упражнение 7 (Колода)
deckgame<-c()
N<-10^5
for(i in 1:N){
  first_deck<-sample(1:54)
  second_deck<-sample(1:54)
  deckgame<-c(deckgame, sum(second_deck==first_deck))
}
mean(deckgame)
# Упражнение 8 (Конверты)
post<-c()
N<-10^5
mailbox<-40
box<-c(1:mailbox)
for(i in 1:N){
  letters<-sample(1:mailbox)
  post<-c(post, sum(letters==box))
}
mean(post)
# Упражнение 9 (Игла Бюффона, подсчёт Пи)
N<-10^7
a<-1;l<-1
center_x<-a*runif(N)
proj_angle<-runif(N,min=0, max=pi/2)
print(2/mean(center_x<l*cos(proj_angle)))
# Упражнение 10 (Именная задача: Звонарёв)
# Упражнение 11 (Именная задача: Шпилёв)