#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "fdacoefs.h"
#include "tmwtypes.h"
#include <math.h>
#define PI 3.1415926535
#define ORD2 4
#define NUM 20000
//b是分母，a是分子系数
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

	int N = 800; //需要周期的整数点数
	double w, xn, sum1, sum2, A, Asin, Acos, tanphase, phase, Ws, Ps, Wn, Pn, SNR, P, W;
	sum1 = sum2 = A = Ws = Wn = W = 0;
	w = 2 * PI * 330 / 8000;
	fopen_s(&fr, "work2.txt", "r");
	for (i = 0; i < 10*N; i++) fscanf_s(fr, "%lf", &xn);

	for (i = 0; i < N; i++) {
		fscanf_s(fr, "%lf", &xn);
		sum1 += xn * cos(w * i);
		sum2 += xn * sin(w * i);
		W += xn * xn;
	}
	fclose(fr);
	printf("sum1 = %lf\n", sum1);
	printf("sum2 = %lf\n", sum2);
	Asin = sum1 * 2 / N;
	printf("Asin = %lf\n", Asin);
	Acos = sum2 * 2 / N;
	printf("Acos = %lf\n", Acos);
	A = -sqrt(Asin * Asin + Acos * Acos);
	printf("A = %lf\n", A);
	tanphase = Asin / Acos;
	printf("tanphase = %lf\n", tanphase);
	phase = atan(tanphase);
	printf("phase = %lf\n", phase);

	fopen_s(&fr, "work2.txt", "r");
	for (i = 0; i < N; i++) {
		
		Ws += (A * sin(w * i + phase)) * (A * sin(w * i + phase));
		fscanf_s(fr, "%lf", &xn);
		//printf("%lf   %lf   %lf  %lf  %lf\n", xn, A * sin(w * i) * cos(phase), A * sin(w * i + phase), xn - A * sin(w * i) * cos(phase),xn- A * sin(w * i + phase));
		Wn += (xn - A * sin(w * i + phase)) * (xn - A * sin(w * i + phase));
	}
	fclose(fr);
	Ps = Ws / N;
	printf("Ps = %lf\n", Ps);
	Pn = Wn / N;
	printf("Pn = %lf\n", Pn);
	P = W / N;
	SNR = 10 * log10(Ps / Pn);
	printf("SNR = %lf\n", SNR);
	//SNR = 10 * log10(Ps / (P - Ps));
	//printf("P = %lf\n", P);
	//printf("SNR = %lf\n", SNR);
	return 0;
}