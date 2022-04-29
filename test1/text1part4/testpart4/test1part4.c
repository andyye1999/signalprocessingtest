#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.1415926535

char frequency[50];
int wei;                                                   //wei位数

void shuru()
{
	
	int j, flag;
	scanf("%s", frequency);                                //将浮点数按字符串处理
	for (flag = wei = j = 0; j < strlen(frequency); j++)   //计算位数
	{
		if (frequency[j] == '.')
			flag = 1;
		else if (flag == 1)
			wei++;
	}
}


int main(void) 
{
	shuru();
	while (wei > 5)
	{
		printf("errow，The number of decimal places exceeds 5, please re-enter\n");
		shuru();
	}
	printf("位数%d\n", wei);
	
	int i, pha, after_fs;                                 //after_f_zero处理过的fs
	long long int after_f_zero;                           //after_f_zero处理过的f0
	int amplitude = 10000, points = 30, fs = 8000;
	double x, f_zero;                                     // f_zero为f0
	f_zero = atof(frequency);                             //字符串转换为浮点数
	after_f_zero = f_zero * pow(10,wei);
	after_fs = fs * pow(10, wei);
	for (pha = i = 0; i < points; i++)
	{
		x = amplitude * sin(2 * PI * pha / after_fs);
		pha += after_f_zero;
		if (pha > after_fs)
		{
			pha -= after_fs;
		}

		printf("%d,%lf\n", i, x);
	}
	return 0;
}