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

    for(int i = args->id; i < args->m->nrows; i += NUM_THREADS)
    {
        for(int j = 0; j < args->m->ncols; j++)
        {
            args->t->data[i][j] = args->m->data[i][j] + args->n->data[i][j];
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

    pthread_t ptids[NUM_THREADS];

    thread_arg_t args[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        args[i] = (thread_arg_t) {i, m, n, t};
    }



    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(& (ptids[i]) , NULL, &thread_main, & (args[i]) );
    }

    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join( ptids[i] , NULL);
    }

    return t;
}
