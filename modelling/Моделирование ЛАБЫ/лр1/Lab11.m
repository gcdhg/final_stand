%---------Апериодическое звено-------------------------
k=8;
T=0.5;%T1=0.5;
T1=0.05;
T2=5;
eps=0.08;
w=0:0.05:50;
   %%%A,fi,U,V,L от w
%(T*s+1)y = k*u;
%W(s)=k/(T*s+1);
%W(jw)=k/(T*j*w+1);
U=k./(T.*w*T.*w+1);
    figure; plot(w,U); grid; title('U(w)'); xlabel('w');
V=-k.*T.*w./(T.*w*T.*w+1);
    figure; plot(w,V); grid; title('V(w)'); xlabel('w');
A=k./sqrt(T.*w.*T.*w+1);A1=k./sqrt(T1.*w.*T1.*w+1);
        A2=k./sqrt(T2.*w.*T2.*w+1);
    figure; plot(w,A); grid; title('A(w)'); xlabel('w');
%1-1-2
fi=-atan(w.*T);fi1=-atan(w.*T1);fi2=-atan(w.*T2);
    figure; plot(w,fi); grid; title('fi(w)'); xlabel('w');
    hold on; plot(w,fi1,'Color','r');plot(w,fi2,'Color','g');
L=20*log10(A);L1=20*log10(A1);L2=20*log10(A2);
    figure; semilogx(w,L); grid; title('L(w)'); xlabel('w, dB');
        hold on;semilogx(w,L1,'Color','r');semilogx(w,L2,'Color','g');
%1-1-3
sys=tf([k], [T 1])
ltiview(sys)
figure
impulse(sys)
figure
nyquist(sys)




