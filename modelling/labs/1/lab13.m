W1 = tf([1 0], [0 1])
W2 = tf([0 1], [0.2 1])
W3 = tf([0 1], [0.01 0.001 1])

W= W1*W2*W3;

figure
grid on
bode(W,0.01:0.01:2)
title('W')

figure
bode(W1,0.01:0.01:2)
grid on
title('W1')

figure
bode(W2,0.01:0.01:2)
grid on
title('W2')

figure
bode(W3,0.01:0.01:2)
grid on
title('W3')
