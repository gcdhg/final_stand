t = 0.2
t1 = 1
t2 = 0.1
eps = 0.01
k = 1

w1 = tf([0 k],[0 1]) %���������������� ����� 
w2 = tf([0 k],[1 0]) %������������� �����
w3 = tf([k 0],[0 1]) %���������������� ����� 
w4 = tf([0 k],[t 1]) %�������������� ����� 
w5 = tf([0 k],[t2 2*t1*eps 1]) %�������������� ����� 2
w6 = tf([k*t k],[0 1]) %����������� �����
w7 = tf([k*t^2 2*k*eps*t k],[0 1]) %����������� ����� 2
w8 = tf([0 k], [t^2 2*eps*t 1]) %������������� �����

ltiview(w1)

ltiview(w2)

ltiview(w3)

ltiview(w4)

ltiview(w5)

ltiview(w6)

ltiview(w7)

ltiview(w8)