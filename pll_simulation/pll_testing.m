s=tf('s');
flp=5;
fsampl=10;
fsig=1;

T_LP=1/(1+s/(2*pi*flp));

N=100
ts=linspace(0,N*1/fsig,N*500)';
xs=sin(2*pi*fsig*ts);
xs_sampled=zeros(length(xs)-1,1)

mod=fsampl/fsig;
for i=1:1:length(xs_sampled)
    index=uint16(floor(i/mod)*mod)+1;
    xs_sampled(i)=xs(index);
end

error=xs_sampled-xs(1:end-1);
xs_fft=fft(xs);
error_fft=fft(error);

figure(1);
subplot(2,2,1);
plot(ts,xs);
title("original signal and sampled signal")
grid();
hold on
plot(ts(1:end-1),xs_sampled);
subplot(2,2,2);
plot(ts(1:end-1),error);
title("error signal")
grid;

subplot(2,2,3);
semilogy(fsig/N*(-length(xs_fft)/2:1:length(xs_fft)/2-1),abs(fftshift(xs_fft)),"o-","color","black");
title("FFT of signal")
grid()
subplot(2,2,4);
semilogy(fsig/N*(-length(error_fft)/2:1:length(error_fft)/2-1),abs(fftshift(error_fft)),"o-","color","black");
grid()
title("FFT of error")