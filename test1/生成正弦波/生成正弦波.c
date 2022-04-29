#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
#define N 100000

int main() {

	double x;
	int amp = 10000; // ·ùÖµ
	int n, f0 = 330, fs = 8000, pha;
	FILE* fp;
	fopen_s(&fp, "ÕýÏÒ²¨.txt", "w");
	for (pha = n = 0; n < N; n++)
	{
		x = amp * sin(2 * PI * pha / fs);
		pha += f0;
		if (pha >= fs) {
			pha -= fs;
		}
		printf("%d %lf\n", n, x);
		fprintf(fp, "%lf\n", x);
	}
	fclose(fp);



	return 0;

}
