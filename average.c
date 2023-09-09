// Only this line of comment is provided 
#include <stdio.h>

int main(void){

    double total = 0;
    int count = 0;
    double n;
    int result;

    while(1){
        result = scanf("%1f", &n);

        if(result != 1)
            break;

        total += n;
        count += 1;

        printf("Total=%f Average=%f\n", total, total/((double) count));
    }


    return 0;
}