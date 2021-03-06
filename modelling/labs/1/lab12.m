close
clear

k = 0.1;
T = 1.4;
T1 = 0.35;
xi = 0.2;

W = 0:0.05:50;

H = @(s) 1 ./ (T .* T .* s .* s + 2 * T * xi *s + 1);

figure
hold on
grid on
xlabel('w')
ylabel('A(w)')
A = k ./ sqrt((1 - T .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T .* W) .^ 2);
A1 = k ./ sqrt((1 - T1 .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T1 .* W) .^ 2);
plot(W, A, 'r');
plot(W, A1, 'g');
hold off

figure
hold on
grid on
xlabel('w')
ylabel('U(w)')
U = k .* (1 - T .^ 2 .* W .^ 2) ./ ((1 - T .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T .* W) .^ 2);
U1 = k .* (1 - T1 .^ 2 .* W .^ 2) ./ ((1 - T1 .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T1 .* W) .^ 2);
plot(W, U, 'r')
plot(W, U1, 'g')
hold off

figure
hold on
grid on
xlabel('w')
ylabel('\phi(w)')
phi_t = @(x) atan((2 .* xi .* T .* x) ./ (1 - T .^ 2 .* x .^ 2));
phi_t1 = @(x) atan((2 .* xi .* T .* x) ./ (1 - T .^ 2 .* x .^ 2));
PHI = horzcat(phi_t(0:0.05:(1 / T)), phi_t((1 / T):0.05:50));
PHI1 = horzcat(phi_t1(0:0.05:(1 / T1)), phi_t1((1 / T1):0.05:50));
plot(W, PHI, 'r')
plot(W, PHI1, 'g')
hold off

figure
hold on
grid on
xlabel('w')
ylabel('V(w)')
V =  -2 .* k .* xi .* T .* W ./ ((1 - T .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T .* W) .^ 2);
V1 = -2 .* k .* xi .* T1 .* W ./ ((1 - T1 .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T1 .* W) .^ 2);
plot(W, V, 'r')
plot(W, V1, 'g')
hold off

figure
hold on
grid on
xlabel('w')
ylabel('L(w)')

L = 20 .* log10(k) - 20 .* log10(sqrt((1 - T .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T .* W) .^ 2));
L1 = 20 .* log10(k) - 20 .* log10(sqrt((1 - T1 .^ 2 .* W .^ 2) .^ 2 + (2 .* xi .* T1 .* W) .^ 2));
plot(W, L, 'r')
plot(W, L1, 'g')
hold off

%----------
% 
% close all
% 
% sys = tf([k], [T*2 2*T*xi 1]);
% ltiview(sys)
% figure
% impulse(sys)
% figure
% nyquist(sys)