#include <stdio.h>
#include <mpi.h>

#define FRIENDS 3
#define TESTS 10000.0

#define TRIES 1000.0

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
    int rank, size, x, res[FRIENDS], success_counter, failure_counter, guess, success_rate;
    double rate;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* execute the code */
    srand(time(NULL) + rank);

    if (rank == 0)
    {
        printf("incia calculo random \n");
        success_rate = 0;
        success_counter = 0;
        failure_counter = 0;       // counter de intentos fallidos inicializado en cero
        guess = (rand() % 99) + 1; // Numero de Gabriel
    }

    for (int t = 0; t < TESTS; t++)
    {
        for (int i = 0; i < TRIES; i++) // Intentos que tienen los 5 amigos
        {

            x = (rand() % 99) + 1;
            //printf("Desde %i de %i x: %i \n", rank, size, x);

            MPI_Gather(&x, 1, MPI_INT, &res[0], 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);
            //printf("holaa procesos");
            if (rank == 0)
            {
                if (is_equal(res, FRIENDS))
                {
                    success_counter++;
                    if (res[0] == guess)
                    {
                        success_rate++;
                    }
                }
                else
                {
                    failure_counter++;
                }
            }
            //    }
        }
    }

    if (rank == 0)
    {
        rate = ((double)success_rate / TESTS) * 100;
        printf("Cantidad de fallos: %i\n", failure_counter);
        printf("Cantidad de aciertos: %i\n", success_counter);
        printf("Numero de aciertos: %i\n", success_rate);
        printf("Ratio de exito: %5.5f % \n", rate);
    }
    MPI_Finalize();
}