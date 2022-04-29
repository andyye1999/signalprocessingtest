#include <stdio.h>
#include <math.h>




double point(double v) {
	int i;
	double people_y[3000], people_x[3000], cow_y[3000], cow_x[3000];
	double angle, tan_angle, d;
	double dt = 0.01;
	people_x[0] = 10, people_y[0] = 50, cow_x[0] = 0, cow_y[0] = 0;
	for (i = 0; i < 2500; i++) {
		tan_angle = (50 * sqrt(5) - sqrt(5) * cow_y[i] - v * dt * i) / (10 * sqrt(5) - sqrt(5) * cow_x[i] + 2 * v * dt * i);
		angle = atan(tan_angle);
		cow_x[i + 1] = cow_x[i] + 5 * dt * cos(angle);
		cow_y[i + 1] = cow_y[i] + 5 * dt * sin(angle);
		people_x[i + 1] = 10 + 2 * v * dt * i / sqrt(5);
		people_y[i + 1] = 50 - v * dt * i / sqrt(5);
		d = (people_x[i + 1] - cow_x[i + 1]) * (people_x[i + 1] - cow_x[i + 1]) + (people_y[i + 1] - cow_y[i + 1]) * (people_y[i + 1] - cow_y[i + 1]);
		if (d < 1) {
			return people_x[i];
		}
	}
}

int main(void)
{
	double v1,x;
	int j;
	for (v1 = 3, j = 0; j < 100; j++) {
		double step = 0.01;
		v1 += j * step;
		x = point(v1);
		if ((60 - x) < 0.000001) break;
	}
	printf("%lf\n",v1);//3.55

	return 0;
}