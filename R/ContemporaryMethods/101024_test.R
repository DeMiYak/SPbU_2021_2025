# ���������� � ���������

# 4.1-2. ���������� ����� �����������
# n = 6

# �������
age<-c(18, 26, 39, 48, 53, 58)

# ��� �������
days<-c(16, 12, 9, 5, 6, 2)

# �������������� �������� ������� (cor.test)
cor.test(age, days)

# cor<- -0.9790796
# t<- -9.6235
# pval<- 0.0006519

# 4.1-4. ������ ���������
# n = 7

# ������� ��������
age<-c(3, 5, 2, 1, 2, 4, 3)
# ��������� ������������
upkeep<-c(80, 100, 75, 60, 80, 93, 84)

cor.test(age, upkeep)

# cor <- 0.9620716
# t <- 7.8859
# p-value <- 0.0005272

# 4.1-6. ������� ������ ������ ��������
# (������������� ������)

# ������� ��� ������
duration<-c(22, 14, 31, 36, 9, 41, 19)
# ����������� ������ (� ���������)
damage<-c(20, 14, 54, 63, 17, 71, 23)

# �) ������
plot(duration, damage, type="p", pch=16)
grid(nx = NULL, ny = NULL,
     lty = 2,
     col = "gray", 
     lwd = 2)

# �) �������� ������������ ����������
cor.test(duration, damage)
correl<-0.9562245
t<-7.3067
pval<-0.0007521

# �) �������������� ������� � �������������� ��������
# H0: rho = 0, H1: rho != 0

# �) ��������� ��� ������ ���������� alpha = 0.05
alpha<-0.05
alpha>pval

# �) ����� ��������� ���������
linear_model<-lm(damage~duration)
b<-coef(linear_model)[1]
a<-coef(linear_model)[2]

# �) ����� ��������� �� �������
abline(lm(damage~duration), col="red", lwd=2)

# �) ������

# ������������� ������

# 4.2-2. ��� �������������

# ������� ����������
alpha<-0.10

# ����� 4 ������
k<-4

# ������� 1
gas1<-c(95,101,108,107,97,101)
s_gas1<-length(gas1)
# ������� 2
gas2<-c(73,69,72,71,67,62,68,71)
s_gas2<-length(gas2)
# �������������
el<-c(55,52,51,37,57,54,34,45,41,53)
s_el<-length(el)
# ������
man<-c(37,24,25,29,22,17,17,22,20,18,21)
s_man<-length(man)

df<-data.frame(gas1, gas2, el, man)
# N
N<-sum(c(s_gas1,s_gas2,s_el, s_man))

# ������� �� �������

m_gas1<-mean(gas1)
m_gas2<-mean(gas2)
m_el<-mean(el)
m_man<-mean(man)

# ����� �������
mean_gen<-mean(c(gas1, gas2, el, man))

# Sum Square Between Groups
ssb_gen<-s_gas1*(m_gas1-mean_gen)^2+s_gas2*(m_gas2-mean_gen)^2+s_el*(m_el-mean_gen)^2+s_man*(m_man-mean_gen)^2 
# Sum Square Within Groups
ssw_gas1<-sum((gas1 - m_gas1)^2)
ssw_gas2<-sum((gas2 - m_gas2)^2)
ssw_el<-sum((el - m_el)^2)
ssw_man<-sum((man - m_man)^2)

# Sum Square
ssw_gen<-ssw_gas1+ssw_gas2+ssw_el+ssw_man
ss_gen<- ssb_gen + ssw_gen


# Mean Square Between Groups
msb<-ssb_gen/(k-1)

# Mean Square Within Groups
msw<-ssw_gen/(N-k)

f<-msb/msw
# ����������� ��������
crit_val<-qf(1-alpha, k-1, N-k)
f
crit_val<f
## �����-�� �������� ����������. ���� ���-�� �������, ���� �� ��� �����.
