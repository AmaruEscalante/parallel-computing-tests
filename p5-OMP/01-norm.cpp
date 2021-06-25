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

    chunk = N / 4;

    // Inicializar matriz con numeros random.
    for (auto i = 0; i < N; i++)
    {
        for (auto j = 0; j < N; j++)
            A[i][j] = (rand() % 100) / 10.0;
    }
    // A[i][j] = 1;
    printf("Matriz inicializada por el proceso master \n");
    print_matrix(A, N);
    printf("\n");

    // Norm

#pragma omp parallel for default(shared) private(i, j) schedule(static, chunk) reduction(+ \
                                                                                         : sum)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            sum += A[i][j];
        }
        printf("Suma parcial %5.2f en i =%i del hilo %i \n", sum, i, omp_get_thread_num());
    }

    printf("sum %5.2f \n", sum);

    factor = 1.0 / sqrt(sum);
#pragma omp parallel for default(shared) private(i, j)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = factor * A[i][j];

    printf("La matriz normalizada es: \n");
    print_matrix(A, N);
}

// // Communication
// // Bcast the Matrix
// for (auto i = 0; i < N; i++)
// {
//     MPI_Bcast(&A[i], N, MPI_INT, 0, MPI_COMM_WORLD);
// }

// MPI_Barrier(MPI_COMM_WORLD); // barrera

// // Process
// local_norm = A[N / size * rank][0];
// for (int i = (N / size * rank); i < (N / size) * (rank + 1); i++)
// {
//     s = 0;
//     for (int j = 0; j < N; j++)
//     {
//         // printf("%d ", A[i][j]);
//         s += fabs(A[i][j]);
//     }

//     if (s > local_norm)
//     {
//         local_norm = s;
//     }
//     // printf("\n");
// }
// printf("local norm en rank %d es: %d \n", rank, local_norm);
// MPI_Reduce(&local_norm, &global_norm, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
// // Communication
// if (rank == 0)
//     printf("Global Norm es %d", global_norm);

// MPI_Finalize();
