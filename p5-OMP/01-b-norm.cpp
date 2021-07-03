#include <iostream>
#include <omp.h>
#include <math.h>

#define N 8

using namespace std;

void print_matrix(float vec[][N], int dim)

{
    for (auto i = 0; i < dim; i++)
    {
        for (auto j = 0; j < dim; j++)
        {
            printf("%5.2f ", vec[i][j]);
        }
        printf("\n");
    };
};

// infNorm de una matriz
int main(int argc, char **argv)
{
    int i, j, chunk;
    float A[N][N], sum, factor;

    // Inicializar matriz con numeros random.
    for (auto i = 0; i < N; i++)
    {
        for (auto j = 0; j < N; j++)
            // A[i][j] = (rand() % 100) / 10.0;
            A[i][j] = 2;
    }
    // A[i][j] = 1;
    printf("Matriz inicializada por el proceso master \n");
    print_matrix(A, N);
    printf("\n");

    // Norm
#pragma omp parallel shared(A) private(i, j)
    {
#pragma omp for schedule(dynamic) reduction(+ \
                                            : sum)

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                sum += A[i][j];
            }
            printf("Suma parcial %5.2f en i =%i del hilo %i \n", sum, i, omp_get_thread_num());
        }

        printf("sum %5.2f desde el thread %d \n", sum, omp_get_thread_num());
        factor = 1.0 / sqrt(sum);

#pragma omp for schedule(dynamic)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                A[i][j] = factor * A[i][j];
    }

    printf("La matriz normalizada desde el thread %d es: \n", omp_get_thread_num());
    print_matrix(A, N);
}
