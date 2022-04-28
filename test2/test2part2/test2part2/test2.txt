#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double sa(double x)
{
	if (0 != x)
		return (sin(x) / x);
	else return 1;
}

double sumpower(double duty)
{
	int amplitude = 10000;
	double power , harmonic;
	power = 0.9 * (amplitude * amplitude * duty - amplitude * amplitude * duty * duty);
	int n;
	double sum_power = 0;
	//double sum_power = amplitude * amplitude * duty * duty;
	for (n = 1; n <= 12; n++)
	{
		harmonic = 2 * duty * amplitude * sa(n * PI * duty);
		sum_power += harmonic * harmonic / 2;
	}

	return (sum_power - power);
}


int main(void)
{
	double high = 0.13;
	double low = 0.09;

	while ((high - low) > 0.000001)
	{
		if ((sumpower(high) > 0) && (sumpower((high + low) / 2) > 0))
			high = (high + low) / 2;
		if ((sumpower(low) < 0) && (sumpower((high + low) / 2) < 0))
			low = (high + low) / 2;
		printf("high = %lf , low = %lf\n",high ,low);

	}
	printf("%lf\n", (high + low) / 2);

	return 0;
}
