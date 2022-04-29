#include <stdio.h>
#include <stdlib.h>
#define POINTS 100000
#define STEP 0.3


int main() {


	long i, k, j;
	short xn, yn;
	double 	y[POINTS];
	FILE* fq, * fr;

	for (k = 0; k < 8000; k++) y[k] = 0;

	fopen_s(&fq, "demo1.pcm", "rb");
	fopen_s(&fr, "demo2.pcm", "wb");

	for (i = 0; i < 8000; i++) {
		fread(&xn, sizeof(short), 1L, fq);
		y[i] = xn;
		yn = xn;
		fwrite(&yn, sizeof(short), 1L, fr);

	}
	for (j = 0, i = 8000; i < POINTS; i++) {
		fread(&xn, sizeof(short), 1L, fq);
		yn = (short)(xn + STEP * y[i - 8000]);
		y[i] = yn;
		fwrite(&yn, sizeof(short), 1L, fr);

	}
	fclose(fr);
	fclose(fq);


	return 0;
}