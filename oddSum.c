#include <stdio.h>
#include <stdlib.h>

int oddSumHelp(int count, int bound, int target)
{
	if(count == 0)
		return target == 0;
	if(bound <=0 )
		return 0;
	
	int addCurrent = oddSumHelp(count-1, bound-2, target-bound);

	if(addCurrent){
		printf("%d ", bound);
		return 1;
	}

	int dontAddCurrent = oddSumHelp(count, bound-2, target);

	if(dontAddCurrent){
		return 1;
	}

	return 0;
}

//Do not change the code below
void oddSum(int count, int bound, int value)
{
    	if(value <= 0 || count <= 0 || bound <= 0) return;
    
    	if(bound % 2 == 0) bound -= 1;

    	if(!oddSumHelp(count, bound, value)) printf("No solutions.\n");
	else printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc != 4) return -1;

	int count = atoi(argv[1]);
	int bound = atoi(argv[2]);
	int value = atoi(argv[3]);

	//oddSum(12,30,200);
	//oddSum(10,20,100);
	//oddSum(20,20,200);
	oddSum(count, bound, value);
	return 0;
}
