clear
clc 
close all
T1 = 0.2;
k = 1;
sys = tf(k,[T1 2]);
ltiview(sys)
grid;
