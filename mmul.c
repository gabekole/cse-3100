#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;


static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *args = (thread_arg_t *) p_arg;
    TMatrix *m = args->m;
    TMatrix *n = args->n;
    TMatrix *t = args->t;

    if (     m == NULL || n == NULL
          || m->ncols != n->nrows   )
        return NULL;

    if (t == NULL)
        return t;
    for (unsigned int i = args->id; i < m->nrows; i+=NUM_THREADS)  {
        for (unsigned int j = 0; j < n->ncols; j++) {
            TElement sum = (TElement)0;
            for (unsigned int k = 0; k < m->ncols; k++)
                sum += m->data[i][k] * n->data[k][j];
            t->data[i][j] = sum;
        }
    }
    return t;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t thread1;
    pthread_t thread2;

    thread_arg_t args1 = {0, m, n, t};
    thread_arg_t args2 = {1, m, n, t};

    pthread_create(&thread1, NULL, &thread_main, &args1);
    pthread_create(&thread2, NULL, &thread_main, &args2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return t;
}
