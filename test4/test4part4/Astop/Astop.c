#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	
	double x1, x2, f0;
	int i;
	x1 = x2 = f0 = 0;
	for (i = 1; i < 100; i++) {
		f0 = (330 * (2 * i + 1)) % 8000;
		if (f0 > 4000) f0 = 8000 - f0;  //4000З­ел
		if (f0 < 330)
		{
			printf("%d %f\n", 2 * i + 1, f0);
			x1 += (double) 1 / ((2 * i + 1) * (2 * i + 1));
		}
		else if (f0 > 330)
		{
			printf("%d %lf\n", 2 * i + 1, f0);
			x2 += (double) 1 / ((2 * i + 1) * (2 * i + 1));
		}
		printf("%lf %lf\n", x1, x2);
	}
	printf("%lf %lf\n", x1, x2);
	x1 = pow(x1, 10) * pow(10, -39);
	printf("%lf %lf\n", x1, x2);
	printf("Astop1 = %lf\n", pow(x1, 10) * pow(10, -39));
	printf("Astop2 = %lf\n", pow(x2, 10) * pow(10, -39));

	return 0;
}