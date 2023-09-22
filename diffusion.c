#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{

	int x = n;
	int y = n;
	int z = n;

	for(int i = 0; i < n; i++)
	{
		int direction = rand() % 6;
		if (direction == 0)
			x--;
		else if(direction == 1)
			x++;
		else if(direction == 2)
			y++;
		else if(direction == 3)
			y--;
		else if(direction == 4)
			z--;
		else if(direction == 5)
			z++;
	}
	int length = 2*n + 1;

	grid[z*length*length + y*length + x] += 1;
}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{
	int length = 2*n + 1;
	double max_dist_sqared = (r*((double)n)*(r*((double) n)));

	double total_count = 0;
	double inside_count = 0;
	for(int z = 0; z < 2*n + 1; z++)
	{
		for(int y = 0; y < 2*n + 1; y++)
		{
			for(int x = 0; x < 2*n + 1; x++)
			{
				double value = grid[x + length*y + length*length*z];
				total_count += value;
				double dist_sqared = (z - n)*(z - n) + (y - n)*(y - n)+(x - n)*(x - n);
				if ( dist_sqared <= max_dist_sqared )
					inside_count += value;
			}
		}	
	}

	return inside_count / total_count;
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below
	int * grid = calloc((2*n+1)*(2*n+1)*(2*n+1), sizeof(int));

	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);
	//fill in some code below

	free(grid);
}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}
