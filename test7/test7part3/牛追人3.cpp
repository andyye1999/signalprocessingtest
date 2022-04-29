#include <stdio.h>
#include <math.h>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>



double point(double v) {
	int i;
	double people_y[3000], people_x[3000], cow_y[3000], cow_x[3000]; //人和牛的坐标
	double angle, tan_angle, d;  //angle角度 d距离 tan_angle 斜率
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
		putpixel(people_x[i], 50 - people_y[i], WHITE); //画点
		putpixel(cow_x[i], 50 - cow_y[i], WHITE);

	}
}

int main(void)
{
	initgraph(600, 600);    // 创建绘图窗口，大小为 640x480 像素
	//y轴向下
	setaspectratio(2, 2); //  设置当前缩放因子  放大10倍
	rectangle(0, 0, 60, 50);   //画矩形
	double v1, x;
	v1 = 3.55;
	x = point(v1);
	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口

	return 0;
}