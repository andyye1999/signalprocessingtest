#include <stdio.h>
#include <stdlib.h>

#define N 20000

//���ɾ��ȷֲ������
int uniform(double a, double b, long int* seed)
{
	//*seed �����������
	//�������ֵ����:a~b
	double t;
	*seed = 2045 * (*seed) + 1;
	*seed = *seed - (*seed / 1048576) * 1048576;
	t = (*seed) / 1048576.0;
	t = a + (b - a) * t;
	return (int)t;
}
double uniform_1(double a, double b, long int* seed)
{
	//*seed �����������
	//�������ֵ����:a~b
	double t;
	*seed = 2045 * (*seed) + 1;
	*seed = *seed - (*seed / 1048576) * 1048576;
	t = (*seed) / 1048576.0;
	t = a + (b - a) * t;
	return t;
}
//��˹�ֲ�
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

//��ֵ
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
//���� ֻ��һ��for
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
//����
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
//��λ��
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
	fopen_s(&fr, "���ȷֲ�.txt", "w");
	for (i = 0; i < N; i++)
	{
		x = uniform(a, b, &s); //x ���ȷֲ��������
		fprintf(fr, "%d\n", x);
	}
	fclose(fr);
	fopen_s(&fr, "���ȷֲ�.txt", "r");
	double mean1 = mean(fr); //mean1 ���ȷֲ��ľ�ֵ
	printf("%lf\n", mean1);
	fclose(fr);
	fopen_s(&fr, "���ȷֲ�.txt", "r");
	double variance1 = variance(fr); //variance1 ���ȷֲ��ķ���
	printf("%lf\n", variance1);
	fclose(fr);
	fopen_s(&fr, "���ȷֲ�.txt", "r");
	int mode1 = mode(fr);//mode1 ���ȷֲ�������
	printf("%d\n", mode1);
	fclose(fr);
	fopen_s(&fr, "���ȷֲ�.txt", "r");
	double median1 = median(fr);//median1 ���ȷֲ�����λ��
	printf("%lf\n", median1);
	fclose(fr);
	FILE* fp;
	fopen_s(&fp, "��˹�ֲ�.txt", "w");
	double mean = 0.0, sigma = 1.0;
	double y;
	long int v = 13579;
	for (i = 0; i < N; i++) {
		y = gauss(mean, sigma, &v);
		fprintf(fp, "%lf\n", y);
	}
	fclose(fp);

	fopen_s(&fr, "������.txt", "w");
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