# ���������� 1 (e)
x <- 1e-20
m<-exp(log(1+x)*(1/x))
m<-exp(log1p(x)*(1/x))
# ���������� 2 (�����)
dieMean<-c()
for(i in 1:6){
  dieMean <- c(dieMean, 1+mean(rgeom(10^i,1/6)))
}
dieMean
# ���������� 3 (�����)
Craps<-function(){
  # ������ ������
  score<-sum(sample(1:6,2))
  # ������ "�������"
  if(score %in% c(7,11)){
    return(FALSE)
  }
  # ������ "��������"
  else if(score %in% c(2,3,12)){
    return(TRUE)
  }
  else{
    # ������ "�����"
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

# ���������� 4 (����������������)
n<-100
m<-60
r<-20
dbinom(r, n, m/n)
# ���������� 5 (�������)
res<-c()
lambda<-3
for(i in 1:5){
  temp<-rpois(10^i,lambda)
  res<-c(res, length(temp[temp==3])/length(temp))
}
res
# ���������� 6 (��������)
res<-c()
lambda<-1
for(i in 1:5){
  temp<-rpois(10^i,lambda)
  res<-c(res, length(temp[(temp%%2)==0])/length(temp))
}
res
# ���������� 7 (������)
deckgame<-c()
N<-10^5
for(i in 1:N){
  first_deck<-sample(1:54)
  second_deck<-sample(1:54)
  deckgame<-c(deckgame, sum(second_deck==first_deck))
}
mean(deckgame)
# ���������� 8 (��������)
post<-c()
N<-10^5
mailbox<-40
box<-c(1:mailbox)
for(i in 1:N){
  letters<-sample(1:mailbox)
  post<-c(post, sum(letters==box))
}
mean(post)
# ���������� 9 (���� �������, ������� ��)
N<-10^7
a<-1;l<-1
center_x<-a*runif(N)
proj_angle<-runif(N,min=0, max=pi/2)
print(2/mean(center_x<l*cos(proj_angle)))
# ���������� 10 (������� ������: ��������)
# ���������� 11 (������� ������: ������)