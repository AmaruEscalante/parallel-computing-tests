#include <iostream>
#include <mpi.h>
#include <algorithm>
#define DEBUG 0

#define SIZE (1 << 4) // 2^19  524288
using namespace std;

int main(int argc, char **argv)
{

    int rank;
    int size, i;
    double t0, t1, t2, t3, t4, t5;

    MPI_Init(&argc, &argv);               /*inicio MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /*determina el rank del proceso*/
    MPI_Comm_size(MPI_COMM_WORLD, &size); /*determina el numero de procesos*/
    float a[SIZE];
    int loc_size = SIZE / size;
    float loc_a[loc_size];

    // Generate random 2^n numbers evenly distributed across mpi processes
    t1 = MPI_Wtime();
    srand(time(NULL));
    if (rank == 0)
    {
        for (int k = 0; k < size; k++)
        {
            for (i = 0; i < loc_size; i++)
            {
                a[k * loc_size + i] = (float)(rand() % (2 * loc_size) + (k * 2 * loc_size));
                printf("%.2f ", a[k * loc_size + i]);
            }
        }
        printf("\n");
    }
    t2 = MPI_Wtime();
    // Scatter array of numbers
    MPI_Scatter(&a[0], loc_size, MPI_FLOAT, &loc_a[0], loc_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    t3 = MPI_Wtime();
    int n = sizeof(loc_a) / sizeof(loc_a[0]);
    sort(loc_a, loc_a + n);

#if DEBUG

    if (rank == 0)
    {
        printf("From p[%d] \n", rank);
        for (int i = 0; i < loc_size; i++)
        {
            printf("p[%d] %.2f ", rank, loc_a[i]);
            // int bi = n * arr[i]; // Index in bucket
            // b[bi].push_back(arr[i]);
        }
    }

#endif

    t4 = MPI_Wtime();
    MPI_Gather(&loc_a[0], loc_size, MPI_FLOAT, &a[0], loc_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    t5 = MPI_Wtime();
    if (rank == 0)
    {
        printf("\nSorted array is: ");
        for (int i = 0; i < SIZE; i++)
        {
            printf("%.2f ", a[i]);
        }
        printf("\n");
        printf("Bucket sort completed in %lf msecs \n", (t5 - t2) / 0.001);
    }
    printf("P[%d] Took %lf msecs \n", rank, (t4 - t3) / 0.001);

    MPI_Finalize();
}