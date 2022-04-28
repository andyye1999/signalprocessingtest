#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double sa(double x);
double sum(double alpha);
int main()
{
	//	int f0, fs;
	int n;
	double alpha, alpha_temp;
	//	f0 = 330;
	//	fs = 8000;
	alpha_temp = 0.01;
	alpha = 0.4;

	while (alpha - alpha_temp > 0.000001)
	{
		if (sum(alpha_temp) * sum((alpha_temp + alpha) / 2) > 0) alpha_temp = (alpha_temp + alpha) / 2;
		if (sum((alpha_temp + alpha) / 2) * sum(alpha) > 0) alpha = (alpha_temp + alpha) / 2;
		printf("alpha = %lf, alpha_temp = %lf\n", alpha, alpha_temp);
	}
	printf("alpha = %lf\n", alpha);
	return 0;
}

double sa(double x)
{
	if (0 != x) return (sin(x) / x);
	else return 1;
}

double sum(double alpha)
{
	int n = 0;
	int A = 10000;
	double sum_power, An, power;
	//	power = 0.9 * A * A * alpha;   //Total mean power  * 0.9
	power = 0.9 * (A * A * alpha - A * alpha * A * alpha);
	//	sum_power = A * alpha * A * alpha;    //A0 = 2 * A * alpha, DC_power = (A0/2)^2 = A*a*A*a;
											  //Sum of component average power, initialize to DC power.
											  //NO DC_POWER.
	sum_power = 0;
	for (n = 1; n <= 12; n++)
	{
		An = 2 * A * alpha * sa(n * PI * alpha);
		sum_power += An * An / 2;        //Parseval's theory
	}
	return (sum_power - power);
	//return 1 means alpha is larger than RIGHT.
	//return 0 means  alpha is less than RIGHT. //330*12 = 3960;

}