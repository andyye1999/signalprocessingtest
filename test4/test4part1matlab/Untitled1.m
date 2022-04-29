clf;

fp=fopen("work2.txt","r");

x = fscanf(fp,'%f');

fs=8000;N=128;   %采样频率和数据点数

n=0:N-1;

t=n/fs;   %时间序列

y=fft(x,N);    %对信号进行快速Fourier变换

mag=abs(y);     %求得Fourier变换后的振幅

f=n*fs/N;    %频率序列

stem(f,mag);   %绘出随频率变化的振幅

xlabel('频率/Hz');

ylabel('振幅');title('N=100');grid on;