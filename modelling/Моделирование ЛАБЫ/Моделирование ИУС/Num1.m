%Вариант 16


clc
clf
clear 
close all


Eps = 0.01;
T1 = 0.2;
T2 = 0.1;
k = 1;
w = 0.0001:0.01:100;
A_w = k./(sqrt((T1.*w).^2+1));
figure(1)
semilogx(w,A_w,'-r');
hold on; grid on;

xlabel('w');
ylabel('A(w)');

A_w = k./(sqrt((T2.*w).^2)+1);

semilogx(w,A_w,'-blue');
legend('A(w) при Т1','A(w) при Т2');
title('A(w)');

% фи от омЕга
figure;
 
phi_w = -atan(w.*T1);
semilogx(w,phi_w,'-r');
hold on; grid on;
phi_w = -atan(w.*T2);
semilogx(w,phi_w,'-blue');
legend('phi(w) при Т1','phi(w) при Т2');
title('phi(w)');
grid on;

%U(w)
figure;

U_w = k./((T1.*w).^2+1);
semilogx(w,U_w,'-r');
hold on; grid on;
U_w = k./((T2.*w).^2+1);
semilogx(w,U_w,'-blue');
xlabel('w');
ylabel('U(w)');
legend('U(w) при Т1','T(w) при Т2');
title('T(w)');

%V(w)
figure;

V_w = -k*T1.*w./((T1.*w).^2+1);
semilogx(w,V_w,'-r');
hold on; grid on;
V_w = -k*T1.*w./((T2.*w).^2+1);
semilogx(w,V_w,'-blue');
legend('V(w) при Т1','V(w) при Т2');
title('V(w)');
%L(w)
figure;

L_w = 20*log(k)-20*log10(sqrt((T1.*w).^2+1));
semilogx(w,L_w,'-r');
hold on; grid on;
L_w = 20*log(k)-20*log10(sqrt((T2.*w).^2+1));
semilogx(w,L_w,'-blue');
legend('L(w) при Т1','L(w) при Т2');
title('L(w)');
%точка излома при g = 1/Т
g = 1/T1
w = 0:0.1:g;
y = zeros(1,51);
semilogx(w,y,'-cyan');
w = g:0.1:100;
y = 20*log10(k)-20*log10(T1*w);
semilogx(w,y,'-cyan');

sys = tf(k,[T1 2]);
ltiview(sys)
grid;





