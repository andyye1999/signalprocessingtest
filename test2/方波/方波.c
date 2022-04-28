#include <stdio.h>
#define DUTY 0.5
#define N 100000

int main() {

	short x;
	int n, f0 = 330, fs = 8000, pha;
	FILE* fp;
	fopen_s(&fp, "·½²¨.txt", "w");
	for (pha = n = 0; n < N; n++)
	{
		x = (pha < DUTY* fs) ? 10000 : -10000;
		pha += f0;
		if (pha >= fs) {
			pha -= fs;
		}
		printf("%d %d\n", n, x);
		fprintf(fp, "%d\n", x);
	}
	fclose(fp);


	
	return 0;

}
