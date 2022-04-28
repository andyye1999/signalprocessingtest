#include <stdio.h>
#define DUTY 0.5
#define N 128

int main() {

	double x, y;
	int n, f0 = 330, fs = 8000, pha;
	FILE* fp;
	fopen_s(&fp, "·½²¨.txt", "w");
	for (pha = n = 0; n < N; n++)
	{
		x = (pha < DUTY* fs) ? 1 : -1;
		pha += f0;
		if (pha >= fs) {
			pha -= fs;
		}
		printf("%d %lf\n", n, x);
		fprintf(fp, "%d %lf\n", n, x);
	}
	fclose(fp);
	fopen_s(&fp, "·½²¨.txt", "r");

	for (n = 0; n < N; n++) {
		fscanf_s(fp, "%*d %lf\n", &y);
		printf("%lf\n", y);
	}
	fclose(fp);
	return 0;

}
