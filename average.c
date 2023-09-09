// Only this line of comment is provided 
#include <stdio.h>

int main(void){

    float total = 0;
    int count = 0;
    float n;
    int result;

    while(1){
        result = scanf("%f", &n);

        if(result != 1)
            break;

        total += n;
        count += 1;

        printf("Total=%f Average=%f\n", total, total/count);
    }


    return 0;
}