#include "matrix.h"

#include <stdlib.h>

/* Módulo de x*/
#define ABS(x) ((x > 0)? (x): -(x))


void matrix_fill_rand(int n, double *restrict _A)
{
    #define A(i, j) _A[n*(i) + (j)]
	int i, j;

	for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            A(i, j) = 10*(double) rand() / (double) RAND_MAX;

    #undef A
}

void matrix_dgemm_0(int n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    /* Macros para acessar os elementos das matrizes mais facilmente*/
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]
    int i, j, k;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            double sum = 0;
            for (k = 0; k < n; ++k)
                sum += A(i, k)*B(k, j);
            C(i, j) = sum;
        }

    #undef A
    #undef B
    #undef C
}

void matrix_dgemm_1(int n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    /* Macros para acessar os elementos das matrizes mais facilmente*/
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]
    int i, j, k;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            for (k = 0; k < n; ++k)
                C(i, j) += A(i, k)*B(k, j);

    #undef A
    #undef B
    #undef C
}

void matrix_dgemm_2(int n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]
    int ii, jj, kk;
    int i, j, k;
    int blocksize = 32;

    for(ii=0; ii<n; ii+=blocksize)
        for(jj=0; jj<n; jj+=blocksize)
            for(kk=0; kk<n; kk+=blocksize)
                for (i = ii; i < ii+blocksize; i++)
                    for (j = jj; j < jj+blocksize; j++)
                        for (k = kk; k < kk+blocksize; k++)
                            C(i, j) += A(i, k)*B(k, j);
                            //C((ii+i), (jj+j)) += A((ii+i), (kk+k))*B((kk+k), (jj+j));


/*
    for(ii=0; i<n; ii+=blocksize)
            for(jj=0; i<n; jj+=blocksize)
                for(kk=0; i<n; kk+=blocksize)
                    for (i = 0; i < 0+blocksize; i++)
                        for (j = 0; j < 0+blocksize; j++)
                            for (k = 0; k < 0+blocksize; k++)
                                //C(i, j) += A(i, k)*B(k, j);
                                C((ii+i), (jj+j)) += A((ii+i), (kk+k))*B((kk+k), (jj+j));
*/

    #undef A
    #undef B
    #undef C
}


bool matrix_eq(int n, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]

    int i, j;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (ABS (A(i, j) - B(i, j)) > 1e-15)
                return false;

    return true;
    #undef A
    #undef B
}


bool matrix_which_dgemm(int algorithm, int n,  double *restrict _C,
                        double *restrict _A, double *restrict _B)
{
    bool ret;
    switch(algorithm)
    {
        case 0:
            matrix_dgemm_0(n, _C, _A, _B);
            ret = true;
            break;

        case 1:
            matrix_dgemm_1(n, _C, _A, _B);
            ret = true;
            break;

        case 2:
            matrix_dgemm_2(n, _C, _A, _B);
            ret = true;
            break;

        default:
            ret = false;
    }
    return ret;
}

