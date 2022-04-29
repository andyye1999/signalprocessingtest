#include <stdio.h>
#include<string.h>
#include<math.h>

int main(void)
{
	char frequency[15];
	int f0;
	int i, flag;
	scanf("%s", frequency);

	for (flag = f0 = i = 0; i < 15; i++, flag*=10)  
	{
		if (('0' <= frequency[i]) && (frequency[i] <= '9')) 
			f0 = 10 * f0 + (frequency[i] - '0');
		else if (frequency[i] == '.') 
			flag = 1;
		else if (frequency[i] == '\0')  
			break;
		else { printf("error!\n"); break; }
	}
}