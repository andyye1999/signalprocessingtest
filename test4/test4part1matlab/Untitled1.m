clf;

fp=fopen("work2.txt","r");

x = fscanf(fp,'%f');

fs=8000;N=128;   %����Ƶ�ʺ����ݵ���

n=0:N-1;

t=n/fs;   %ʱ������

y=fft(x,N);    %���źŽ��п���Fourier�任

mag=abs(y);     %���Fourier�任������

f=n*fs/N;    %Ƶ������

stem(f,mag);   %�����Ƶ�ʱ仯�����

xlabel('Ƶ��/Hz');

ylabel('���');title('N=100');grid on;