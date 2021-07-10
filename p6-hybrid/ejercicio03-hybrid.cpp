#include <iostream>
#include <mpi.h>
#include <ctime>
#include <omp.h>
const int N = 16;
//const int N = 16;

void leer(int n, int A[][N], int v[N])
{
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
    {
        // v[i] = rand() % 10;
        v[i] = 2;
        printf("%d - ", v[i]);
        for (int j = 0; j < n; j++)
        {
            // A[i][j] = rand() % 10;
            A[i][j] = 1;
            printf("%d, ", A[i][j]);
        }
        printf("\n");
    }
}

void escribir(int x[], int n)
{

    for (int i = 0; i < n; i++)
        printf("%d, ", x[i]);
}

int main(int argc, char *argv[])
{
    int i, j, k, rank, p;
    int A[N][N], B[N][N], v[N], x[N], y[N];
    double t0, t1, t2, t3;

    //int nthread = atoi(argv[1]); // Define threads de openmp

    //omp_set_num_threads(4);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        leer(N, A, v);
    k = N / p;
    t0 = MPI_Wtime();

// Operate
#pragma parallel num_threads(4) shared(A, v)
    {
#pragma parallel for private(i)
        for (i = 0; i < k; i++)
        {
            x[i] = 0;
            for (j = 0; j < N; j++)
                x[i] += A[i][j] * v[j];
        }
    }

    t2 = MPI_Wtime();
    if (rank == 0)
        escribir(x, N);

    t3 = MPI_Wtime();
    if (rank == 0)
    {
        printf("\nTcomm= %2.10f \n", (t1 - t0) + (t3 - t2));
        printf("Tcomp= %2.10f \n", (t2 - t1));
        printf("Total= %2.10f \n", (t3 - t0));
    }
    MPI_Finalize();
    return 0;
}
