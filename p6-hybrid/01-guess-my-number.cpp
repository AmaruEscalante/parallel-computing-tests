#include <stdio.h>
#include <mpi.h>

#define FRIENDS 5

bool is_equal(const int array[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (array[i] != array[i + 1])
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    int rank, size, x, res[FRIENDS], success_counter, failure_counter;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* execute the code */
    srand(time(NULL) + rank);

    if (rank == 0)
    {
        printf("incia calculo random \n");
        success_counter = 0;
        failure_counter = 0; // counter de intentos fallidos inicializado en cero
    }
    for (int i = 0; i < 1000; i++)
    {

        x = (rand() % 99) + 1;
        //printf("Desde %i de %i x: %i \n", rank, size, x);

        MPI_Gather(&x, 1, MPI_INT, &res[0], 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        //printf("holaa procesos");
        if (rank == 0)
        {
            if (is_equal(res, FRIENDS))
                success_counter++;
            else
                failure_counter++;
            // if (is_equal(res, FRIENDS))
            //     printf("Son iguales\n");
            // else
            //     printf("No son iguales\n");
        }
        //    }
    }
    if (rank == 0)
    {
        printf("Cantidad de fallos: %i\n", failure_counter);
        printf("Cantidad de aciertos: %i\n", success_counter);
    }
    MPI_Finalize();
}