#include <stdio.h>
#include <math.h>
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>

#define PI 3.14159265358979323846

int main(void)
{
	initgraph(600, 600);    // ������ͼ���ڣ���СΪ 640x480 ����
	//y������
	//setaspectratio(2, 2); //  ���õ�ǰ��������  �Ŵ�10��
	rectangle(0, 0, 60, 50);   //������
	
	
	int i;
	double people_y[3000], people_x[3000], cow_y[3000], cow_x[3000];
	double angle, tan_angle, d;
	double v = 3;
	double dt = 0.01;
	people_x[0] = 10, people_y[0] = 50, cow_x[0] = 0, cow_y[0] = 0;
	for (i = 0; i < 2000; i++) {
		tan_angle = (50 * sqrt(5) - sqrt(5) * cow_y[i] - v * dt * i) / (10 * sqrt(5) - sqrt(5) * cow_x[i] + 2 * v * dt * i);
		angle = atan(tan_angle);
		cow_x[i + 1] = cow_x[i] + 5 * dt * cos(angle);
		//printf("%lf\n", cow_x[i]);
		cow_y[i + 1] = cow_y[i] + 5 * dt * sin(angle);
		//printf("%lf\n", cow_y[i]);
		people_x[i + 1] = 10 + 2 * v * dt * i / sqrt(5);
		people_y[i + 1] = 50 - v * dt * i / sqrt(5);
		d = (people_x[i + 1] - cow_x[i + 1]) * (people_x[i + 1] - cow_x[i + 1]) + (people_y[i + 1] - cow_y[i + 1]) * (people_y[i + 1] - cow_y[i + 1]);
		if (d < 1) {
			printf("%lf\n", people_x[i]);
		}
		putpixel(people_x[i], 50 - people_y[i], WHITE);
		putpixel(cow_x[i], 50 - cow_y[i], WHITE);

	}
	_getch();				// �����������
	closegraph();			// �رջ�ͼ����

	return 0;
}