#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h> 

//write an integer to a pipe
void write_int(int pd, int value)
{
	write(pd, &value, sizeof(int));
}
//read an integer from a pipe
//the function returns the number of bytes read
int read_int(int pd, int *value)
{
	return read(pd, value , sizeof(int));
}

//TODO
//implement the function using binary search
//if v is in array a[], whose length is n, return 1
//otherwise, return 0
int in_array(int a[], int n, int v)
{
        int l = 0;
        int r = n;
        int mid = l + (r - l)/2;

        while(l <= r)
        {
                mid = l + (r - l)/2;

                if(a[mid] == v)
                        return 1;
                
                if(a[mid] > v)
                        r = mid - 1;
                else
                        l = mid + 1;
        }

        return 0;
}

void run_search(int n, int m)
{
        int pd1[2];
        //pipe creation
        if(pipe(pd1) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd2[2];
        //pipe creation
        if(pipe(pd2) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t pid = fork();
        if(pid == 0)
        {
                //TODO
                //fill in code below
		//note this is process A
                close(pd2[1]);
                close(pd1[0]);

		srand(3100);

                //now generate array A

                int A[n];
                A[0] = rand() % 10 +1;
                for(int i = 1; i < n; i++)
                {
                        A[i] = A[i-1] + rand() % 10 + 1; 
                }

                int v;
                int round = 0;
		//TODO
		//complete the following line of code

                while(read_int(pd2[0], &v)!=0)
                {
			//TODO
			//fill in code below
                        write_int(pd1[1], A[round]);
                        round++;
                }
		//TODO
		//fill in code below
                close(pd2[0]);
                close(pd1[1]);
                exit(0);
        }
	//TODO
	//fill in code below
        close(pd2[0]);
        close(pd1[1]);


        int pd3[2];
        //pipe creation
        if(pipe(pd3) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd4[2];
        //pipe creation
        if(pipe(pd4) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t pid1 = fork();
		
        if(pid1 == 0)
        {
		//fill in code below
		//note this is process B
                close(pd3[0]);
                close(pd4[1]);

		srand(3504);

                //now generate array B

                int B[n];
                B[0] = rand() % 10 +1;
                for(int i = 1; i < n; i++)
                {
                        B[i] = B[i-1] + rand() % 10 + 1; 
                }
                int v;
                //TODO
                //complete the following line of code
                while(read_int(pd4[0], &v)!=0)
                {
                        //TODO
                        //fill in code below
                        int res = in_array(B, n, v);
                        write_int(pd3[1], res);
                }

		//fill in code below
                close(pd3[1]);
                close(pd4[0]);
                close(pd2[1]);
                close(pd1[0]);
                exit(0);
	}
        //TODO
        //fill in code below
        close(pd3[1]);
        close(pd4[0]);

	int v1, v2;
        int count = 0;
        for(int i = 0; i < n; i++)
        {
		write_int(pd2[1], 1);
                read_int(pd1[0], &v1);
		write_int(pd4[1], m - v1);
		read_int(pd3[0], &v2);

                if(v2)
                {
                        printf("%d + %d = %d\n", v1, m - v1, m);
                        count ++;
                }
        }
	printf("There are %d pairs that add up to %d.\n", count, m);
	//TODO
	//fill in code below
        close(pd3[0]);
        close(pd4[1]);
        close(pd2[1]);
        close(pd1[0]);
}
