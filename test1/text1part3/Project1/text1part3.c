#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define PI 3.1415926535

int main(void)
{
	int amplitude = 10000, points = 30;  
	long long int f1 = 330333333333, fs = 8000000000000;
	double x;
	int i, pha;

	for (pha = i = 0; i < points; i++)
	{
		x = amplitude * sin(2 * PI * pha / fs);
		pha += f1;
		if (pha > fs)
		{
			pha -= fs;
		}

		printf("%d,%lf\n", i, x);
	}

	return 0;
}
