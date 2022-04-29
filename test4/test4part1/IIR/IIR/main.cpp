#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535
#define ORD2 4
#define NUM 20000
//b是分子，a是分母系数
const double b[ORD2] = { 0.01379348564724,-0.009563608593466,-0.009563608593466,  0.01379348564724};
const double a[ORD2] = { 1,   -2.699286943033,    2.484870605052,  -0.7771239079117};

int main()
{
	long i, k;
	double vv, x[ORD2], y[ORD2];
	FILE *fq, *fr;

	for (k = 0; k < ORD2; k++) x[k] = y[k] = 0;

	fopen_s(&fq, "work1.txt", "r");//读方波 100000点数，幅值为10000
	fopen_s(&fr, "work2.txt", "w");//写滤出的正弦波
	//IIR滤波器
	for (i = 0; i < NUM; i++)
	{
		for (k = ORD2 - 1; k > 0; k--) y[k] = y[k - 1];
		for (k = ORD2 - 1; k > 0; k--) x[k] = x[k - 1];
		fscanf_s(fq, "%lf", &x[0]);
		for (vv =x[0]*b[0], k = 1; k < ORD2; k++) vv += x[k] * b[k]- y[k] * a[k];
		y[0] = vv;

		fprintf(fr, "%d\n", (short)vv);
	}
    fclose(fr);
	fclose(fq);

	int low, high, N = 800; //需要周期的整数点数
	double w, xn, xn2, Asin, Acos, Ws, Ps, Wn, Pn, SNR, SNR1, SNR2, P, W;
	Ws = Wn = W = 0;
	w = 2 * PI * 330 / 8000;
	fopen_s(&fr, "work2.txt", "r");
	for (i = 0; i < 10*N; i++) fscanf_s(fr, "%lf", &xn);
	for (Asin=Acos=i = 0; i < N; i++) {
		fscanf_s(fr, "%lf", &xn);
		Asin += xn * cos(w * i);
		Acos += xn * sin(w * i);
	}
	fclose(fr);
	Asin = Asin * 2 / N;
	Acos = Acos * 2 / N;

	fopen_s(&fr, "work2.txt", "r");
	for (i = 0; i < 10 * N; i++) fscanf_s(fr, "%lf", &xn);
	for (Ps= Pn=i = 0; i < N; i++) {
		xn2 = Asin*cos(w * i)+ Acos* sin(w * i);
		Ps += xn2 * xn2;
		fscanf_s(fr, "%lf", &xn);
		Pn += (xn - xn2) * (xn - xn2);
	}
	fclose(fr);
	SNR = 10 * log10(Ps / Pn);
	printf("SNR = %lf\n", SNR);
	double f0; //等效的频率
	for (low=0, high=4000, i = 6; i < 100; i++) {
		f0 = (330 * (2 * i + 1)) % 8000;
		if (f0 > 4000) f0 = 8000 - f0;  //4000翻折
		if (f0 < 330)
		{
			if (low < f0) low = f0;  //250
		}
		else if (f0 > 330)
		{
			if (high > f0) high = f0;  //410
		}
		//printf("%d %d\n", low, high);
		if(f0==250)
			printf("%d %lf\n", 2 * i + 1, f0);
		else if(f0==410)
			printf("%d %lf\n", 2 * i + 1, f0);
	}
	
	SNR1 = 10 * log10(25 * 25);
	printf("Astop1 = %lf\n", 40-SNR1);
	SNR2 = 10 * log10(23 * 23);
	printf("Astop2 = %lf\n", 40-SNR2);
	return 0;
}