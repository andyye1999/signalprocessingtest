#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846


int main(void)
{

	int M = 3;
	int pha;
	double frequency_sampling, phase, time, sinx, term, frequency_zero, processingTime; // phase:相位 frequency_zero:f0 frequency_sampling:fs time:原始的时间 term:余项 processingTime:处理过的时间
	phase = PI / 6;
	frequency_zero = 320;
	frequency_sampling = 3 * frequency_zero;
	term = 1;
	int n, i, j, symbol;  //symbol：正负号


	while (0.5 / (term * term) < 10000)
	{
		M += 2;
		for (term = i = 1; i <= M; i++)
			term *= PI / 2 / i;
	}


	for (n = pha = 0; n < 100; n++, pha += frequency_zero)
	{
		if (pha >= frequency_sampling)
			pha -= frequency_sampling;

		time = 2 * PI * pha / frequency_sampling + phase;

		while (time > 2 * PI)   //控制在0到2Π之间
		{
			time -= 2 * PI;
		}

		if (time >= 0 && time <= PI / 2)
			processingTime = time;
		if (time >= PI / 2 && time <= 1.5 * PI)
			processingTime = PI - time;
		if (time >= 1.5 * PI && time <= 2 * PI)
			processingTime = time - 2 * PI;   

	

		for (i = symbol = 1, sinx = 0; i < M; i += 2, symbol = -symbol)        //泰勒公式
		{
			for (term = 1, j = i; j > 0; j--)
				term *= processingTime / j;
			sinx += symbol * term;

		}
		printf("processingTime = %lf time = %lf sinx = %lf\n", processingTime, time, sinx);


	}

	printf("M=%d\n", M);

	return 0;
}