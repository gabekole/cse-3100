#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;

	printf("n = ");
	scanf("%d", &n);

	double pi = 0.0;
	//TODO
	
	for(int i = 0; i <= n; i++)
	{
		double internal = (4.0 / (8.0*i + 1.0)) - (2.0/(8.0*i+4.0))
			- (1.0/(8.0*i+5)) - (1.0/(8.0*i+6.0));

		double denominator = 1;
		for (int j = 0; j < i; j++){
			denominator *= 16; 
		}

		pi += internal/denominator;
	}
	







	printf("PI = %.10f\n", pi);
	return 0;
}
