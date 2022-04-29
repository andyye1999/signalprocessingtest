#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592653589
long M_fre[15] = { 262,262,392,392,440,440,392,0,349,349,330,330,294,294,262 };

int main()
{
    FILE* text13_Tone;
    long L, i, j, g, front, xx;
    double a, b, x, y, x_temp, y_temp, t;
    double yy[1000] = { 0 };

    if ((text13_Tone = fopen("Tone.txt", "w")) == NULL)
    {
        printf("Fail to open file Tone\n");
        exit(0);
    }

    b = 0.1;
    a = 1 - b;

    for (xx = 511, g = 0; g < 15; g++)
    {
        if (M_fre[g] != 0)
        {
            L = 48000 / M_fre[g];
            front = 0;
            for (x_temp = y_temp = 0, i = 0; i < 24000; i++)
            {
                xx = (2045 * xx + 1) & 1048575;
                x = (xx - 524288.0) / 256.0;
                if (i > 3000) x = 0;

                y = x + a * yy[front] + b * (y_temp - x_temp);
                y_temp = yy[front] = y;
                x_temp = x;
                front++;
                if (front >= L) front = front - L;
                fprintf(text13_Tone, "%.4lf\n", y);
            }
            for (i = 0; i < 5000; i++)
            {
                fprintf(text13_Tone, "%d\n", 0);
            }
        }
        else
        {
            for (i = 0; i < 10000; i++)
            {
                fprintf(text13_Tone, "%d\n", 0);
            }
        }
    }

    fclose(text13_Tone);
    return 0;
}