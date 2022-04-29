#include <stdio.h>
#include <stdlib.h>

#define N 20000

//生成均匀分布随机数
int uniform(double a, double b, long int* seed)
{
	//*seed 任意的种子数
	//随机数的值区间:a~b
	double t;
	*seed = 2045 * (*seed) + 1;
	*seed = *seed - (*seed / 1048576) * 1048576;
	t = (*seed) / 1048576.0;
	t = a + (b - a) * t;
	return (int)t;
}
double uniform_1(double a, double b, long int* seed)
{
	//*seed 任意的种子数
	//随机数的值区间:a~b
	double t;
	*seed = 2045 * (*seed) + 1;
	*seed = *seed - (*seed / 1048576) * 1048576;
	t = (*seed) / 1048576.0;
	t = a + (b - a) * t;
	return t;
}
//高斯分布
double gauss(double mean, double sigma, long int* s) {
	int i;
	double x, y;
	double uniform_1();
	for (x = 0, i = 0; i < 12; i++) {
		x += uniform_1(0.0, 1.0, s);
	}
	x = x - 6.0;
	y = mean + x * sigma;
	return y;
}

//均值
double mean(FILE* fr) {
	int i;
	double sum, t;
	int val;
	sum = 0;
	for (i = 0; i < N; i++) {
		fscanf_s(fr, "%d\n", &val);
		sum += val;
	}
	t = sum / N;
	return t;
}
//方差 只用一个for
double variance(FILE* fr) {
	int i, val;
	double sum1, sum2, t;
	sum1 = 0, sum2 = 0;
	for (i = 0; i < N; i++) {
		fscanf_s(fr, "%d\n", &val);
		sum1 += val;
		sum2 += val * val;
	}
	t = sum2 / N - (sum1 / N) * (sum1 / N);//DX^2=EX^2-(EX)^2
	return t;
}
//众数
int mode(FILE* fr) {
	int numbers[N] = { 0 }, counts[N] = { 0 };
	int t = 0, max = 0;
	int i;
	for (i = 0; i < N; i++) {
		fscanf_s(fr, "%d\n", &numbers[i]);
		counts[numbers[i]]++;
	}
	for (i = 0; i < N; i++) {
		if (counts[i] > t) {
			t = counts[i];
			max = i;
		}
	}
	return max;
}
//中位数
double median(FILE* fr) {
	int numbers[N] = { 0 }, counts[N] = { 0 };
	int t = 0, max = 0;
	int i;
	for (i = 0; i < N; i++) {
		fscanf_s(fr, "%d\n", &numbers[i]);
		counts[numbers[i]]++;
	}
	int b;
	double mid;
	int left = 0, right = counts[0];
	for (i = 0; i < N; i++) {
		left += counts[i];
		right += counts[i + 1];
		if ((left < (N / 2)) && (right >= (N / 2))) {
			return i + 1;
		}
	}
}

int main(void)
{
	double a, b;
	int x;
	a = 0.0, b = 100.0;
	long int s = 13579;
	int i;
	FILE* fr;
	fopen_s(&fr, "均匀分布.txt", "w");
	for (i = 0; i < N; i++)
	{
		x = uniform(a, b, &s); //x 均匀分布的随机数
		fprintf(fr, "%d\n", x);
	}
	fclose(fr);
	fopen_s(&fr, "均匀分布.txt", "r");
	double mean1 = mean(fr); //mean1 均匀分布的均值
	printf("%lf\n", mean1);
	fclose(fr);
	fopen_s(&fr, "均匀分布.txt", "r");
	double variance1 = variance(fr); //variance1 均匀分布的方差
	printf("%lf\n", variance1);
	fclose(fr);
	fopen_s(&fr, "均匀分布.txt", "r");
	int mode1 = mode(fr);//mode1 均匀分布的众数
	printf("%d\n", mode1);
	fclose(fr);
	fopen_s(&fr, "均匀分布.txt", "r");
	double median1 = median(fr);//median1 均匀分布的中位数
	printf("%lf\n", median1);
	fclose(fr);
	FILE* fp;
	fopen_s(&fp, "高斯分布.txt", "w");
	double mean = 0.0, sigma = 1.0;
	double y;
	long int v = 13579;
	for (i = 0; i < N; i++) {
		y = gauss(mean, sigma, &v);
		fprintf(fp, "%lf\n", y);
	}
	fclose(fp);

	fopen_s(&fr, "白噪声.txt", "w");
	long int w = 13579;
	double x1 = 0;
	double a0 = 0.0, b0 = 1.0;
	for (i = 0; i < N; i++)
	{
		x1 = uniform_1(a0, b0, &w);
		fprintf(fr, "%lf\n", x1);
	}
	fclose(fr);
	return 0;

}