function f=u_mikh(A)
n=3
a0 = A(1);
a1 = A(2);
a2 = A(3);
a3 = A(4);

fuck = [];
q = 1;

maxx=0; maxy=0; minx=0; miny=0;
for w=0.01:0.005:5,
    Njw= a0*((w*i)^3) + a1*((w*i)^2) + a2*(w*i) + a3;
    Re = real(Njw);
    Im = imag(Njw);
    
    if(Njw == 0)
        fuck(q) = w;
        q = q + 1;
    end
    
    if(Re>maxx)
        maxx=Re;
    end
    if(Im>maxy)
        maxy=Im;
    end
    if(Re<minx)
        minx=Re;
    end
    if(Im<miny)
        miny=Im;
    end
    plot(Re, Im, 'x')
    hold on
end
fuck
x=0; y=miny-20:0.1:maxy+20;
plot(x,y, 'x')
hold on
x=minx-20:0.1:maxx+20; y=0;
plot(x,y, 'x')
hold off
grid on
axis([minx-20 maxx+20 miny-20 maxy+20])


end
