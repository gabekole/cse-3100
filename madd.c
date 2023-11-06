#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t * args = (thread_arg_t *) p_arg;
    double **result = args->t->data;
    double **addend1 = args->m->data;
    double **addend2 = args->n->data;
    
    for(int i = args->id; i < args->m->nrows; i += NUM_THREADS)
    {
        for(int j = 0; j < args->m->ncols; j++)
        {
            result[i][j] = addend1[i][j] + addend2[i][j];
        }
    }

    return NULL;
}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t ptid1; 
    pthread_t ptid2; 

    thread_arg_t arg1 = {0, m, n, t};
    thread_arg_t arg2 = {1, m, n, t};

    pthread_create(&ptid1, NULL, &thread_main, &arg1);
    pthread_create(&ptid2, NULL, &thread_main, &arg2);

    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);

    return t;
}
