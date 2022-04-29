#include <stdio.h>
#include <stdlib.h>
long int musichz[6][7] = {
	{262,262,392,392,440,440,392},
	{349,349,330,330,294,294,262},
	{392,392,349,349,330,330,294},
	{392,392,349,349,330,330,294},
	{262,262,392,392,440,440,392},
	{349,349,330,330,294,294,262}
};
double uniform(double a, double b, long int* seed)
{
	//*seed 任意的种子数
	//随机数的值区间:a~b
	double t;
	*seed = 2045 * (*seed) + 1;
	*seed = *seed - (*seed / 1048576) * 1048576;
	t = (*seed) / 1048576.0;
	t = a + (b - a) * t;
	return t;
}
double gauss(double mean, double sigma, long int* s) {
	int i;
	double x, y;
	double uniform_1();
	for (x = 0, i = 0; i < 12; i++) {
		x += uniform(0.0, 1.0, s);
	}
	x = x - 6.0;
	y = mean + x * sigma;
	return y;
}

int main() {
	FILE* fp;
	fopen_s(&fp, "声音.txt", "w");
	long int s = 13579;
	int L, i, points, j, k;
	double a, b, x, y, x_temp, y_temp, left, right;
	double yn[1000] = { 0 };
	b = 0.1;
	a = 1 - b;
	left = 0.0, right = 1.0;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			L = 48000 / musichz[i][j];
			points = 0;
			for (x_temp = 0, y_temp = 0, k = 0; k < 24000; k++) {
				x = gauss(left, right, &s);
				if (k > 3000) x = 0;
				y = x + a * yn[points] + b * (y_temp - x_temp);
				yn[points] = y;
				y_temp = y;
				x_temp = x;
				points++;
				if (points >= L) points = points - L;
				fprintf(fp, "%lf\n", 1000 * y);
			}
			for (k = 0; k < 5000; k++)
			{
				fprintf(fp, "%d\n", 0);
			}
		}
		//最后一个音是又延长符号，所以单独一个循环
		L = 48000 / musichz[i][6];
		points = 0;
		for (x_temp = 0, y_temp = 0, k = 0; k < 48000; k++) {
			x = gauss(left, right, &s);
			if (k > 3000) x = 0;
			y = x + a * yn[points] + b * (y_temp - x_temp);
			yn[points] = y;
			y_temp = y;
			x_temp = x;
			points++;
			if (points >= L) points = points - L;
			fprintf(fp, "%lf\n", 1000 * y);
		}
		for (k = 0; k < 10000; k++)
		{
			fprintf(fp, "%d\n", 0);
		}
	}
	fclose(fp);
}