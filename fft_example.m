f=@(t) exp(-t).*sin(2*pi.*t);
%the observation interval T determines the frequency resolution of the DFT
%the longer the signal is observed, the lower the frequencies we can
%observe. The frequency resolution is given by 1/T.
T=100;
%the sampling interval determines the fastest frequency that the DFT
%detects. The fastest frequency is given by 1/deltat
deltat=0.01;

ts=linspace(0,T,T/deltat);
xs=f(ts);
xs_fft=fft(xs);
frequencies=1/T*[-length(xs)/2:1:length(xs)/2-1]

subplot(1,2,1);
plot(frequencies,fftshift(abs(xs_fft)));
title("linear frequency plot");
grid()
subplot(1,2,2);
semilogy(frequencies,fftshift(abs(xs_fft)));
title("logarithmic frequency plot");
grid()