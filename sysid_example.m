s=tf('s');
%transfer function of the system
T=1/((1+s)*(s+2));
%transfer function of the input
U=1/s*1/(1+s);
%transfer function of the response
Y=T*U;

Tend=10;
N=1000;
deltaT=Tend/N;

ts=linspace(0,Tend,N);
ys=impulse(Y,ts);
us=impulse(U,ts);

subplot(1,2,1);
plot(ts,ys);
title("System response")
subplot(1,2,2);
plot(ts,us);
title("Input")

data=iddata(ys,us,deltaT);
T_est=tfest(data,3);

Y_est=T_est*U;
ys_est=impulse(Y_est,ts);

figure(2)
plot(ts,ys,"r--");
hold on
plot(ts,ys_est,"b--");