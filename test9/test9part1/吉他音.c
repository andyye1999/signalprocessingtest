#include <stdio.h>
#include <stdlib.h>

#define MUSICHZ 262



int main()
{
	FILE* fr;
	FILE* fp;
	long int s = 13579;
	int L, i, points;
	double a, b, x, y, x_temp, y_temp;
	double yn[240] = { 0 };
	L = 48000 / MUSICHZ;
	b = 0.1;
	a = 1 - b;
	x_temp = 0;
	y_temp = 0;
	points = 0;
	//fopen_s(&fr, "白噪声.txt", "r");
	fopen_s(&fr, "高斯分布.txt", "r");
	fopen_s(&fp, "声音.txt", "w");
	for (i = 0; i < 24000; i++) {
		fscanf_s(fr, "%lf\n", &x);
		if (i > 3000) x = 0;
		y = x + a * yn[points] + b * (y_temp - x_temp);
		yn[points] = y;
		y_temp = y;
		x_temp = x;
		points++;
		if (points >= L) points = points - L;
		fprintf(fp, "%lf\n", 1000 * y);
	}
	fclose(fr);
	fclose(fp);
	return 0;
}