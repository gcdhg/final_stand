function f=u_gurv
n = 3
A=zeros(3,3);
A(2,1) = input('������� �0=');
A(1,1) = input('������� �1=');
A(3,2) = A(1,1);
A(2,2) = input('������� �2=');
A(3,3) = input('������� �3=');
A(1,2) = A(3,3);
A(1,3)=0;
A(2,3)=0;
A(3,1)=0;
A
A1=[A(1,1:2);A(2,1:2)];
b=0;
 if A(1,1)>0
 b=b+0;
 else
 b=b+1;
 end
 if det(A1)>0
 b=b+0;
 else
 b=b+1;
 end
 if det(A)>0
 b=b+0;
 else
 b=b+1;
 end
if b==0 disp('������� ���������');
else disp('������� �����������');
end 