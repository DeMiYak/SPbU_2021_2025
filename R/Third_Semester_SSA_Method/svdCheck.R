s = matrix(c(1122,-388,-234,-143,-181,-368,563,
             -388,321,156,39,-37,55,-50
             ,-234,156,170,9,-9,300,-113,
             -143,39,9,31,40,-8,-239,
             -181,-37,-9,40,94,65,-351,
             -368,55,300,-8,65,866,-152,
             563,-50,-113,-239,-351,-152,3545), nrow = 7, ncol = 7)

svdCheck <- function(x) {
  # ���������� svd
  x <- as.matrix(x)
  s <- svd(x)$d # ����� ����������� �����
  u <- svd(x)$u # ����� u-��������
  v <- svd(x)$v # ����� v-��������
  L <- dim(x)[1] # ����� ����� �������
  K <- dim(x)[2] # ����� �������� �������
  
  
  # �������� �� ������� ������������� ����������� �����
  if(length(s[s<0])) stop("Negative singular value")
  
  
  # �������� �� �����������������
  tempU<-t(u)%*%u
  tempV<-t(v)%*%v
  if(!(norm(tempU-diag(min(L,K)))<1e-9)|!(norm(tempV-diag(min(L,K)))<1e-9)) stop("Found a non-biorthogonal matrix") 
  
  # �������������� ������� X
  xf<-u%*%diag(s)%*%t(v)
  
  dif <- xf - x
  
  # ����� ��������� �������
  print("difference")
  
  print(dif)
  
  print("xf")
  
  print(xf)
  
  print("x")
  
  print(x)
  
  # ������� �����������:
  # ���� ��������� ����� �� ����������� �����������
  # �� ������� �����
  # ����� ���
  
  if (norm(dif)<1e-9)
    print("res == x")
  else
    print("res != x")
}


svdCheck(s)

test<-matrix(runif(6*4, -18, 18), 6, 4)
svdCheck(test)




# ������ �������


# L = 2, K = 4

# Rank = 2
m1<-matrix(c(1,2,-1,3,0,5,-1,8),2,4)

matplot(m1[1,], m1[2,], pch = "o")
paste("Rank = ", length(svd(m1)$d[abs(svd(m1)$d)>1e-9]))

# Rank = 1
# All points are on the linear function
m2<-matrix(c(1,2,2,4,-1,-2,5,10),2,4)

matplot(m2[1,], m2[2,], pch = "o")
paste("Rank = ", length(svd(m2)$d[abs(svd(m2)$d)>1e-9]))

# L = 3, K = 4

# Rank = 3 
# Any of the three points make a basis
# in the three-dimensional field
# with one extra point, that is a sum of
# bases' radius-vectors

m3<-matrix(c(1,2,3,-1,4,5,2,0,7,1,4,12),3,4, byrow = TRUE)

paste("Rank = ", length(svd(m3)$d[abs(svd(m3)$d)>1e-9]))

# Rank = 2 
# All the points are laying in the
# plane, created by any of the two points
m4<-matrix(c(1,2,3,4,5,6,7,8,9,5,7,9),3,4)

paste("Rank = ", length(svd(m4)$d[abs(svd(m4)$d)>1e-9]))

# Rank = 1
# All points are on the linear function

m5<-matrix(c(1,2,3,2,4,6,-3,-6,-9,5,10,15),3,4)

paste("Rank = ", length(svd(m5)$d[abs(svd(m5)$d)>1e-9]))





# ��������� �������
# ������ ������� �� �� �����, 
# �� ����� �� ������ ������ ������� ������� �������������� (���������� ��������������).

centralize<-function(m)
{
  m<-as.matrix(m)
  dim<-dim(m)[1]
  x<-vector()
  for(i in 1:dim){x[i]<-mean(m[i,])}
  m1<-t(sweep(t(m),2, x, FUN="-"))
  print("Mean values: ")
  print(x)
  m1
}

centralize_print<-function(m)
{
  m<-as.matrix(m)
  m1<-centralize(m)
  rnkm<-length(svd(m)$d[abs(svd(m)$d)>1e-9])
  rnkm1<-length(svd(m1)$d[abs(svd(m1)$d)>1e-9])
  
  print("Centralizing:")
  
  print("Before:")
  print(m)
  print(paste("Rank = ", rnkm))
  
  print("After:")
  print(m1)
  print(paste("Rank = ", rnkm1))
}

# 1. ���� ����� ������������� ����� ����������� ����������� ������������
# �� ���� �� ����������

# ����� ������� �������, ������������ �������������� ������ �� ������� ������
# ��������� ������� ������� �� 4-�� ����������� �����, �� ���� �� ��������


# L = 2, K = 4

# Rank = 2
centralize_print(m1)

# Rank = 1
centralize_print(m2)



# L = 3, K = 4


# Rank = 3
centralize_print(m3)


# Rank = 2
centralize_print(m4)


# Rank = 1
centralize_print(m5)


# 2. ����� ����� �� ����������� �����������
# ����� ������� ������� ������, ��������� �� �������� ����� �����
# (��������� ����� ������ �����������)


# � ���� ������� ������� ���������� �� ���� �����
# �� �������� ��������: ((1,2),(3,4))
# �������� �������� �������������� �������: ((1,1))
# ��� ������������� ������ �������� ����� ����� ���������
# ��-�� ���� ������-������� ���� ����� ���������� �����������
# Rank = 2 -> 1
m_242<-matrix(c(1,2,3,4), 2, 2)
centralize_print(m_242)


# � ���� ������� ������� ���������� �� ����� �����
# �� �������� ��������: ((1,2))
# �������� �������� �������������� �������: ((0,0)) - ����������� 0
# ��� ������������� ����� ���������� ������� ���������
# Rank = 1 -> 0
m_241<-matrix(c(1,2), 2, 1)
centralize_print(m_241)


# L = 3, K = 4

# � ���� ������� ������� ���������� �� ���� �����
# �� �������� �������� ((1,2,3), (-1,-4,-5), (2,3,1))
# �������� �������� �������������� �������: ((0.25,1.25,2.5), (1.25,2.25,0.5))
# ����� ����� ��� ����� ����� ��������� ���������
# ��� ������������� ��������� ���������� � ����� ���������
# ��������� ����� ��������� ���������� ����� ������� ������������ ���������
# (����������� 2), �� � ���� ������� ����� ����� 2
# Rank = 3 -> 2
m_343<-matrix(c(1,2,3,-1,-4,-5,2,3,1),3,3)
centralize_print(m_343)

# � ���� ������� ������� ���������� �� ���� �����
# �� �������� ��������: ((2,5,6), (1,7,-2))
# �������� �������� �������������� �������: ((0.25,-0.5,2))
# ��� � � ������ � ����� ���������� �������� ������� (2x4),
# ������, ��������� � ����� ���������, ����� ����������� 1.
# Rank = 2 -> 1
m_342<-matrix(c(2,5,6,1,7,-2),3,2)
centralize_print(m_342)

# � ���� ������� ������� ���������� �� ����� �����
# �� �������� ��������: ((2,5,-1))
# �������� �������� �������������� �������: ((0,0,0))
# ����� ���������� � ����� ���������
# Rank = 1 -> 0
m_341<-matrix(c(2,5,-1),3,1)
centralize_print(m_341)

# ����� �������, ���� ������� �� ����� �������� ��� ������������� � ���� �������
# 1. ����� ����� > �����������
# 2. ������� ��� ������������ 

# ���� ������� ��������� (���������� �� �������) � ������, ����
# 1. ����� ����� <= �����������
# 2. ������� �� ������������
# 3. (���� ����� ������ �����������) ����� ����������� �� ����������� ����������� 1<=d<=dim(X)

m_344<-matrix(c(1,2,3,2,4,6,0,1,5,3,1,2),3,4)
centralize_print(m_344)


m_345<-matrix(c(1,1,1,2,2,1,3,3,1,4,4,1),3,4)
centralize_print(m_345)

# ����� �������

# ������� ���������� Z_i ����� ������������ ��� ����� ��������, Z_i = X^T U_i, 
# �.�. ����� �������� ���������� ����� ������ ��� �������� ���������� � �������������� �� U_i.
# ����� X_1, X_2, � , X_p \in R^n � ������ �������� (������� ������� X).  
# ���������� ��� �������� (������ �� �����, ���� �������������/������������, ��� ���),  
# p=2, ������ � ������ �� ����������, ������ � ������ �� ������. ������� (����������) � ��������.
# ����� ��������: U_1 = (1,1)^T / \sqrt(2), U_2 = (1,-1)^T/ sqrt(2). 

# ����� ����� � ����� ��������� (������������� ����������) Z_1 � Z_2, ����� �������� ��������� ��� ��������?


U_1<-matrix(c(1,1),2,1)/sqrt(2) # ������������� ������ 1 (������� 1)
U_2<-matrix(c(1,-1),2,1)/sqrt(2) # ������������� ������ 2 (������� 2)


# ������� ������ ��������
grade<-matrix(c(1,1,1,2,1,3,1,4,1,5,2,1,2,2,2,3,2,4,2,5,3,1,3,2,3,3,3,4,3,5,4,1,4,2,4,3,4,4,4,5,5,1,5,2,5,3,5,4,5,5),25,2,byrow=TRUE)
rownames(grade)=c(paste("S",1:25,sep=''))
colnames(grade)=c("Math","Phys")
grade



# ������� 1: 
# ������� ����� ������������ (������ ������������, ������ ����
# ���������� ��� �������� �������)

# ��� ������ ��������, ��� ����� ������������
Z_1<-grade%*%U_1 
rownames(Z_1)=c(paste("S",1:25,sep=''))
Z_1



# ������� 2: 
# ������� ������������� ������������ (� ���������� ������������ ������
# �� ������)

# ���� �������� � ������ > 0 - ������������ �� ���������� �����, ��� �� ������
# ���� = 0 - ������������ �� ���������� ����� ��, ��� � �� ������
# ���� < 0 - ������������ �� ���������� ����, ��� �� ������
Z_2<-grade%*%U_2
rownames(Z_2)=c(paste("S",1:25,sep=''))
Z_2



# ���������� �������� 2, ����� ��������� ������� 3:
# ������� ������������ ������������ ����������

U_3<-matrix(c(-1,1),2,1)/sqrt(2) # ������������� ������ 3 (������� 3)

# ���� �������� � ������ > 0 - ������������ �� ������ �����, ��� �� ����������
# ���� = 0 - ������������ �� ������ ����� ��, ��� � �� ����������
# ���� < 0 - ������������ �� ������ ����, ��� �� ����������
Z_3<-grade%*%U_3
rownames(Z_3)=c(paste("S",1:25,sep=''))
Z_3


# ��������������� ������� �����������.
# ������ ����� ����������� ��� ����� ������� ��� SVD.
# �� ���� ��������� ������� ������ X^T (�.�. ��� �������� � �������) ������� n �� p.
# �� ��� �������� (�� �������) ����������� � ���������� (���������� ���������������).
# ����� ����� ������� SVD (��� X, �� X^T, ����� ���� ������������ � ������������� � ��.�������).
# �������� ����������� ����� (�� ������ � ���������) � ����������� �������, �� ������ �������  ��������������� ����� ��������.
# ������� ��� ���������� ����������� (Z1,Z2), ��� �� ��� X ������������ �������� Z_1, �� ��� Y � �������� Z_2 
# (����������� ��������� � ��������� ������ ���� ������� ���������).
# 
# ������ � ��������� ���� ����������. ��� ������ ���������� ��� ����������� � ���-����.����� �� ������ �� ���������� � ������. 
# ������� res � ������ ��� �� ������ ��� ��� ���, �� � ��� �� ���������, ������ ����� �� ������.
# ���������������� ������ ����������� ����� � ������������������ ������ ��� ������� ���������� 
# (���������, ����� ����� � ���� ���� ����� �������������).
# 
# �� ������� (Z1,Z2) ���������� ����� �������� �������� res, 
# ����������, ����� �� �������, ��� ��������, �������� �������� �� ������ ��� ��� ���.
# ���� �����-�� ����� ��������� ����� �� ���������, 
# �� �� ������ ������������� ������� ��������� ���������, ��� ������ ���������� ���� ��������.





# ���� 0 (���������� ������� ����� ���������������)

exboy<-read.table("EXBOY.DAT", header=TRUE, row.name=1)
exboy
# exboy
exboy$col="green"
exboy$col[(exboy$RES==0)]="red"
exboy

mexboy<-matrix(as.numeric(as.matrix(exboy[1:dim(exboy)[1], 1:(dim(exboy)[2]-2)])), dim(exboy)[1],dim(exboy)[2]-2)
mexboy
# exboy
n<-dim(mexboy)[1]
p<-dim(mexboy)[2]
colnames(mexboy)=c(paste("M",1:4, sep=''), paste("P", 1:7,sep=''))
rownames(mexboy)=c(1:n)
mexboy


# ���� 1 (��������������)

standartize<-function(m)
{
  m<-as.matrix(m)
  p<-dim(m)[2]
 
  for(i in 1:p){
    # �������������
    m[,i]<-m[,i]-mean(m[,i])
    # ������������ (������� ������������� ������ u 
    # �� ������������ ����������)
    m[,i]<-svd(m[,i])$u
  }
  m
}

str(exboy)
mexboy<-standartize(mexboy)
mexboy
sum(diag(t(mexboy)%*%mexboy))


# ���� 2 (����������� ����������)

# ���������: ���� ������� ���������� Z_i = X^T*U_i, 
# �� Z_i = V_i*s_i, ��� V_i - ������ ����������� �������,
# � s_i - ����������� �����. �� ����� �������, ��� s_i ����� ����������������
# ��� ��������� �������� �� V_i. �������, � ���������� �����������, ����������� (�����������)
# ����� ������������ ��������� ������� ������� ������������ �������



tr_mexboy<-t(mexboy)
svd(tr_mexboy)
# svd(tr_mexboy)$d

tr_mexboy_dp<-(svd(tr_mexboy)$d*svd(tr_mexboy)$d)/(sum(svd(tr_mexboy)$d*svd(tr_mexboy)$d))
svd(tr_mexboy)$d*svd(tr_mexboy)$d

tr_mexboy_u<-svd(tr_mexboy)$u
tr_mexboy_v<-svd(tr_mexboy)$v
tr_mexboy_u
tr_mexboy_v
svdCheck(tr_mexboy)
options(digits=4)
tr_mexboy_u[,1]
tr_mexboy_u[,2]
Z_1<-mexboy%*%tr_mexboy_u[,1]
Z_2<-mexboy%*%tr_mexboy_u[,2]


# ���� 3 (��������� ����� �� ������������)


plot(Z_1,Z_2, pch=16, col=exboy$col)
text(Z_1,Z_2, rownames(exboy), cex=0.5, pos=3)



# ���� 4 (�������� ����� �� �������)


# stat - ������ ����������� ����� � ���������� ����������� 
# (������� ������������ ������� - ������� - �� ����������� �� ������ ���)
tr_mexboy_dp
stat<-c(paste(round(tr_mexboy_dp*100,digits=1),"%",sep=''))
stat



# ����������� ������ 1 - ������� � ������. ������ �� ������ �� ���������� � ������
# ������������� ��-�������, �� ����� ���� ����. ����� ���� ������ ������
# ����� ���������� ���������  
#
# �������� ������ ������ ������ �� ������������� (���.��������):
# (�1, �4, �5, �6, �3, �2, �2, �3, �4, �7, �1)
tr_mexboy_u[,1]


# ����������� ������ 2 - ������� � ������. ������ �� ������ �� ���������� � ������
# ������������� ��-�������. ��� ������ �� ���������� ����� ��������������� �������
# �� ������ ����. ����� ���� ������ ������
# ������� ����� ����������� ���������� �������� �� ���������� � �� ������
#
# �������� ������ ������ ������ �� ���������� � �� ������ (���.��������) �� �������������:
# (�2,�3,�4,�1);(�2,�3,�7,�4,�1,�6,�5)
tr_mexboy_u[,2]

# �� ������������ ����� �������� ��������� ��������� ����� 
# � ��������� � �������� � �������� �������
Z<-cbind(Z_1, Z_2);Z

# ���������� ������� ����� (��� ������� 77)
Z[(Z_1)<(-0.2)&(Z_2<(-0.2)),]
# ����� ��������, ��� �� Z_1 (����� ���������) �������� ����� �������� �����, ��� � ���
# ��� ������ �� ������ ���.
# � �� �� �����, �� �������� �� Z_2, �� ����� ������ ������ �� ������, ��� �� ����������.
# ���� �� �������������, �� �������� �� �� ������: �� ������ ����������� ���� �� ������� �� ���������� (1)
# ���� ������� ����� ���������� �������� �� ������ � ���������� (� ������ ������ ����������)  
# ��������� ���������� ����� (��� ������������� �����) (2)
# ���� (� ������ ������ ���������), �� ������� ���������� �����, ������� ���������� ��� (����������) (3) 
exboy["77",] 
# ������ �� �������� ������, ����� ������� �����, ��� �������� �������� ����
# ���������� ������ �� ����������


# ������� ����� ("10", "132") 
((((-0.1)>Z_1))&(Z_1>(-0.2))&(exboy$col=="red"))
exboy[c("10","132"),]
# �������������: (1),(2)


# ������� ����� ("31", "123")
# ������� ��������� ������ �� ���������� (������������ ������) ���
# ������� ��������� (����� Z_1<(-0.1))
exboy[c("31","123"),]


# ��������� ����� (����������� ����������) ��������� ������ ���� �����, �� �����
# ������ �����, ����������������, �� ��� �� ��������, 
# ��� � ������������� �� ����� �����
exboy[c("59","88","89","130"),]



# ������������� ��� ����������� �����:
# ��������� Z_i = V_i*s_i, V_i = X^T*U_i/s_i - ������ ����������� ������,
# �� ����������� ����� c_i = s_i^2 = Z_i^T*Z_i ���������� ���������� ������� ���������� ������������ ������
# �� ����, ��������� ������ ������� ���������� �������������� �������� ������� X


# ������� ����� ("45", "48")
# ����� 45 ����� �������� ����� ��������� (����� ������� �� Z_1),
# � ����� ������������ ������� ����� ����������� ���������� �������� �� ���������� � ������ (�� Z_2)
# ����� 48 ����� ����� ������� ���������� �� ������� ����� �������� �� ���������� � ������ (Z_2) 
# � ������� ����� ��������� (Z_1)
exboy[c("45","48"),]


# ������� ����� ("7")
# ����� 7 ����� �������� ����� ��������� (�� Z_1)
# � ��������� ������� � ������� ����� ����������� � ������� (�� Z_2)
exboy["7",]

# �������������� ������������� � ������� � ������� ������:
# ��� ��� �� ������� ��������������� ��� ������� ���������� �� �������������������
# ������� ������ X^T, �� ����� - ������� ������������ Z_1, Z_2, ��� ����� �������� ������ ���������� �
# ������� � ������� ����� ����������� � ������� ����� ���� ����������. �����, ����� �������, ��� ���� ��
# Z_1 ����� ����� ������ - �� ��������� ���� �������� (�� ���� ����������), � ��������.
# � ��� �����, ���� �� Z_2 ����� ���� ������ - �� ������� ����������� ������� ������� � ������� ����� 
# ���� ���������� � ������ ����������, ����� - ����������� ������� � ������ ������

# ������ �� �����, ������ ������������� ������� �� ��������.
# 1-�� �������� (Z_1 > 0, Z_2 > 0) - ����� ���� ��������, ������� � ������ ����������
# 2-�� �������� (Z_1 < 0, Z_2 > 0) - ����� ����� ��������, ������� � ������ ����������
# 3-�� �������� (Z_1 < 0, Z_2 < 0) - ����� ����� ��������, ������� � ������ ������
# 4-�� �������� (Z_1 > 0, Z_2 < 0) - ����� ���� ��������, ������� � ������ ������

# ��� ���� ������ ������������, ��� ����� �� ���, ��� ����� ��������� ���� ��������,
# �� ������ �� ������ ����

