#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535
#define F0 330
#define FS 8000
#define N 800
#define COS 1.933200204
#define SIN 0.2562893731
#define Q 16384

FILE* fr;

void fib(int n, double f0, double fs) {
	//n 抽样点数 f0 信号频率 fs 采样频率
	fopen_s(&fr, "sin.txt", "w");
	double p = 0, q = 0, r = SIN;
	
	if (n == 0) fprintf(fr, "%lf\n", 0);
	else if (n >= 1) {
		fprintf(fr, "%lf\n", 0);
		fprintf(fr, "%lf\n", 10000 * r);
	}
	//动态规划
	//p是y(n-2),q是y(n-1),r是yn
	for (int i = 2; i <= n; ++i) {
		p = q;
		q = r;
		r = q * COS - p;
		fprintf(fr, "%lf\n", 10000 * r);
	}
	fclose(fr);
}


int main() {
	fib(100000, F0, FS);
	int i;
	double xn, xn2, Asin, Acos, Ps, Pn, SNR;
	fopen_s(&fr, "sin.txt", "r");
	for (i = 0; i < 10 * N; i++) fscanf_s(fr, "%lf", &xn);
	for (Asin = Acos = i = 0; i < N; i++) {
		fscanf_s(fr, "%lf", &xn);
		Asin += xn * cos(2 * PI * F0 * i / FS);
		Acos += xn * sin(2 * PI * F0 * i / FS);
	}
	fclose(fr);
	Asin = Asin * 2 / N;
	Acos = Acos * 2 / N;
	fopen_s(&fr, "sin.txt", "r");
	for (i = 0; i < 10 * N; i++) fscanf_s(fr, "%lf", &xn);
	for (Ps = Pn = i = 0; i < N; i++) {
		xn2 = Asin * cos(2 * PI * F0 * i / FS) + Acos * sin(2 * PI * F0 * i / FS);
		Ps += xn2 * xn2;
		fscanf_s(fr, "%lf", &xn);
		Pn += (xn - xn2) * (xn - xn2);
	}
	fclose(fr);
	SNR = 10 * log10(Ps / Pn);
	printf("SNR = %lf\n", SNR);
	return 0;
}