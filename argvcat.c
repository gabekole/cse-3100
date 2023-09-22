#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    unsigned int s1Length = strlen(s1);
    unsigned int s2Length = strlen(s2);
    unsigned int length =  s1Length + s2Length + 1; // + 1 for null byte

    char * s3 = calloc(length, sizeof(char));

    for(int i = 0; i < s1Length; i++)
    {
        s3[i] = s1[i];
    }
    for(int j = 0; j < s2Length; j++)
    {
        s3[j + s1Length] = s2[j];
    }
    s3[length - 1] = '\0'; // Set null byte

    return s3;
}

int main(int argc, char *argv[])
{
    char *s;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        char * temp = my_strcat(s, argv[i]);
        free(s); // Not sure how bad this is as a practice
        s = temp;
    }

    printf("%s\n", s);

    free(s);
    return 0;
}
