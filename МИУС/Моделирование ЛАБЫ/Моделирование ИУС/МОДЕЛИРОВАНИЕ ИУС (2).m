%%
%Вариант 16


clc
clf
clear 
close all


epsil = 0.01;
pii = 3.14;
T1 = 0.2;
T2 = 0.1;
k = 1;
w = 0.01:0.01:100;
A = w.^2;
B = (T1^2);
C = 1 - A.*B;
D = 2.*epsil.*T1.*w;
E = D.^2;
F = C.^2;

A_w = k./(    sqrt(     ((1-(T1.^2).*(w.^2)).^2)   +    ((2*epsil*T1*w).^2)    )  );

figure
semilogx(w,A_w,'-r');
hold on; grid on;
xlabel('w');
ylabel('A(w)');

A_w = k./(sqrt((1-(T2).^2.*(w).^2).^2+ (2.*epsil.*T2.*w).^2));

semilogx(w,A_w,'-blue');
legend('A(w) при Т1','A(w) при Т2');
title('A(w)');

% фи от омЕга

figure;
w1 = 0.01:0.01:9.99;
w2 = 10.01:0.01:100;
phi_w = -acot((2.*epsil.*T1.*w1)./(1-(T1.^2).*(w1.^2)));
semilogx(w1,phi_w,'-r');
hold on; grid on;
phi_w = -acot((2.*epsil.*T1.*w2)./(1-(T1.^2).*(w2.^2)));
semilogx(w2,phi_w,'-r');
w1 = 0.01:0.01:19.99;
w2 = 20.01:0.01:100;
phi_w = -acot((2.*epsil.*T2.*w1)./(1-(T2.^2).*(w1.^2)));
semilogx(w1,phi_w,'-blue');
phi_w = -acot((2.*epsil.*T2.*w2)./(1-(T2.^2).*(w2.^2)));
semilogx(w2,phi_w,'-blue');
legend('phi(w) при Т1','','phi(w) при Т2','');
title('phi(w)');
xlabel('w');
ylabel('phi(w)');
grid on;


%U(w)
figure;

U_w = (k.*(1-(T1).^2.*(w).^2))./((1-(T1).^2.*(w).^2).^2+ (2.*epsil.*T1.*w).^2);
semilogx(w,U_w,'-r');
hold on; grid on;
U_w = (k.*(1-(T2).^2.*(w).^2))./((1-(T2).^2.*(w).^2).^2+ (2.*epsil.*T2.*w).^2);
semilogx(w,U_w,'-blue');
xlabel('w');
ylabel('U(w)');
legend('U(w) при Т1','T(w) при Т2');
title('T(w)');

%V(w)
figure;

V_w = -2*k*epsil*T1.*w./((1-(T1).^2.*(w).^2).^2+ (2.*epsil.*T1.*w).^2);
semilogx(w,V_w,'-r');
hold on; grid on;
V_w = -2*k*epsil*T2.*w./((1-(T2).^2.*(w).^2).^2+ (2.*epsil.*T2.*w).^2);
semilogx(w,V_w,'-blue');
legend('V(w) при Т1','V(w) при Т2');
title('V(w)');
xlabel('w');
ylabel('V(w)');
%L(w)
figure;

L_w = 20*log10(k)- 20*log10((1-(T1).^2.*(w).^2).^2+ (2.*epsil.*T1.*w).^2);
semilogx(w,L_w,'-r');
hold on; grid on;
L_w = 20*log10(k)- 20*log10((1-(T2).^2.*(w).^2).^2+ (2.*epsil.*T2.*w).^2);
semilogx(w,L_w,'-blue');

legend('L(w) при Т1','L(w) при Т2');
xlabel('w');
ylabel('L(w)');
title('L(w)');

w = 0:0.1:5;
y = zeros(1,51);
semilogx(w,y,'-cyan');
w = 5:0.1:100;
y = 20*log10(k)-80*log10(T1*w);
semilogx(w,y,'-cyan');
grid on;

sys = tf(k,[T1 2]);
ltiview(sys)
grid;



