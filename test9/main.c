#include <stdio.h>
#include <stdlib.h>

#define M_fre 200

int main()
{
    FILE* text13_Gaus;
    FILE* text13_Tone;
	long L,i, front;
    double a, b, x,y, x_temp, y_temp;
    double yy[240] = { 0 };

	L = 48000 / M_fre;



    if ((text13_Gaus = fopen("Gaussian.txt", "r")) == NULL)
    {
        printf("Fail to open file Gaussian\n");
        exit(0);
    }
    if ((text13_Tone = fopen("Tone.txt", "w")) == NULL)
    {
        printf("Fail to open file Tone\n");
        exit(0);
    }

    a = 1000;
    b = 1000;
    x_temp = 0;
    y_temp = 0;
    front = 0;
    for (i = 0; i < 1000; i++)
    {
        fscanf(text13_Gaus, "%lf", &x);
        y = x + a * yy[front] + b * (y_temp - x_temp);
        printf("%lf\n",y);;

        yy[front] = y;
        y_temp = y;
        x_temp = x;
        front++;
        if (front >= L) front = front - L;

        fprintf(text13_Tone, "%.4lf\n", y);
    }

    fclose(text13_Gaus);
    fclose(text13_Tone);



	return 0;
}
