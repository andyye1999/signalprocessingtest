#include <stdio.h>
#define DUTY 0.5



int main(void)
{
	int n, f0 = 330, fs = 8000, amp, pha;

	for (pha = n = 0; n < 100; n++)
	{
		
		if (pha <= DUTY * fs) {
			amp = 1;
			pha += f0;
		}
		else
		{
			amp = -1;
			pha += f0;
		}

		if (pha >= fs) {
			pha -= fs;
		}

		printf("%d, %d\n", n, amp);
	}

	return 0;
}
