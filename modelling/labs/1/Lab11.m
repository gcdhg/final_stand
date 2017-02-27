close

k = 0.1;
T = 1.4;
T1 = T;
T2 = 0.35;
xi = 0.2;

W = 0:0.05:50;

H = @(s) 1 ./ T .* s + 1;

figure
hold on
grid on
xlabel('w')
ylabel('A(w)')
A = k ./ sqrt(T .* W + 1);
A1 = k ./ sqrt(T1 .* T1 .* W .* W + 1);
A2 = k ./ sqrt(T2 .* T2 .* W .* W + 1);
plot(w, A, 'r');
plot(w, A1, 'g');
plot(w, A2, 'b');
hold off

figure
hold on
grid on
xlabel('w')
ylabel('U(w)')
U = k ./ (T .* T .* W .* W + 1);
U1 = k ./ (T1 .* T1 .* W .* W + 1);
U2 = k ./ (T2 .* T2 .* W .* W + 1);
plot(w, U, 'r')
plot(w, U1, 'g')
plot(w, U2, 'b')
hold off

figure
hold on
grid on
xlabel('w')
ylabel('\phi(w)')
PHI = -atan(T .* W);
PHI1 = -atan(T1 .* W);
PHI2 = -atan(T2 .* W);
plot(w, PHI, 'r')
plot(w, PHI1, 'g')
plot(w, PHI2, 'b')
hold off

figure
hold on
grid on
xlabel('w')
ylabel('V(w)')
V = -k .* T .* W ./ (T .* T .* W .* W + 1);
V1 = -k .* T1 .* W ./ (T1 .* T1 .* W .* W + 1);
V2 = -k .* T2 .* W ./ (T1 .* T1 .* W .* W + 1);
plot(w, V, 'r')
plot(w, V1, 'g')
plot(w, V2, 'b')
hold off

figure
hold on
grid on
xlabel('w')
ylabel('L(w)')
L = 20 * log10(A);
L1 = 20 * log10(A1);
L2 = 20 * log10(A2);
plot(w, L, 'r')
plot(w, L1, 'g')
plot(w, L2, 'b')
hold off

%----------

close all

sys = tf([k], [T 1]);
ltiview(sys)
figure
impulse(sys)
figure
nyquist(sys)