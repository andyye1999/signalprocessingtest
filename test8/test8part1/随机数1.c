#include <stdio.h>
#include <stdlib.h>

#define N 500

//生成均匀分布随机数
int uniform(double a, double b, long int* seed)
{
	//*seed 任意的种子数
	//随机数的值区间:a~b
	double t;
	*seed = 2045 * (*seed) + 1;
	*seed = *seed % 1048576;
	t = (*seed) / 1048576.0;
	t = a + (b - a) * t;
	return (int)t;
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
double mode(FILE* fr) {
	double numbers[N] = { 0 }, counts[N] = { 0 };
	int count = 0;
	int i, j;
	for (i = 0; i < N; i++) {
		fscanf_s(fr, "%lf\n", &numbers[i]);
	}
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			if (numbers[i] == numbers[j])
				count++;
		}
		counts[i] = count;//保存
		count = 0;
	}
	int maxIndex = 0;
	for (i = 1; i < N; i++)//查询最多的数字
	{
		if (counts[i] > counts[maxIndex])
			maxIndex = i;
	}
	int maxCount = counts[maxIndex];
	if (maxCount == 1) {
		return -1;
	}
	else {
		return numbers[maxIndex];
	}
}
//中位数
double median(FILE* fr) {
	double numbers[N];
	double temp;
	int i, j;
	for (i = 0; i < N; i++) {
		fscanf_s(fr, "%lf\n", &numbers[i]);
	}
	for (i = 0; i < N - 1; i++) {//冒泡排序将数组排序
		for (j = 0; j < N - 1 - i; j++)
			if (numbers[j] > numbers[j + 1]) {
				temp = numbers[j + 1];
				numbers[j + 1] = numbers[j];
				numbers[j] = temp;
			}
	}
	int b;
	double mid;
	if (N % 2 == 0) {
		b = N / 2;
		mid = (numbers[b] + numbers[b - 1]) / 2.0;
	}
	else mid = numbers[(N - 1) / 2];
	return mid;
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
	double mode1 = mode(fr);
	printf("%lf\n", mode1);
	fclose(fr);
	fopen_s(&fr, "均匀分布.txt", "r");
	double median1 = median(fr);
	printf("%lf\n", median1);
	fclose(fr);
	return 0;

}