#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n)
{

	//Fill in code below
	//When deciding which way to go for the next step, generate a random number as follows.
	//r = rand() % 4;
	//Treat r = 0, 1, 2, 3 as up, right, down and left respectively.

	//The random walk should stop once the x coordinate or y coordinate reaches $-n$ or $n$. 
	//The function should return the fraction of the visited $(x, y)$ coordinates inside (not including) the square.

	int visited[2*n-1][2*n-1];
	for(int i = 0; i < 2*n-1; i++)
	{
		for(int j = 0; j < 2*n-1; j++)
		{
			visited[i][j] = 0;
		}
	}


	int x = 0;
	int y = 0;

	while(-n < x && x < n && -n < y && y < n)
	{
		visited[y+n-1][x+n-1] = 1;

		int r = rand() % 4;
		if(r == 0)
			y++;
		else if(r == 1)
			x++;
		else if(r == 2)
			y--;
		else if(r == 3)
			x--;

	}

	int totalVisited = 0;
	for(int i = 0; i < 2*n-1; i++)
	{
		for(int j = 0; j < 2*n-1; j++)
		{
			totalVisited += visited[i][j];
		}
	}

	return ((double) totalVisited)/((2.0*n-1.0)*(2.0*n-1.0));
}

//Do not change the code below
int main(int argc, char** argv)
{
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	// printf("%lf\n", two_d_random(2));
	return 0;
}

