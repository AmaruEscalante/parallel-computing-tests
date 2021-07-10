#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
const int N = 512;

// Mac:  g++ -Xpreprocessor -fopenmp ejercicio3-OMP.cpp -o ejercicio3-OMP -lomp
// Linux: gcc -fopenmp ejercicio3-OMP.cpp -o ejercicio3-OMP

int main(int argc, char const *argv[])
{
	double start_time, run_time;
	int n = atoi(argv[1]);
	int v[n], A[n][n], y[n];
	int nthread = atoi(argv[2]);
	omp_set_num_threads(nthread);

	/* inicializacion */
	srand(time(NULL));
	for(int i = 0; i < n; i++)
	{
		v[i] = rand() % 10;
		for(int j = 0; j < n; j++)
		{
			A[i][j] = rand() % 10;
		}
	}

	start_time = omp_get_wtime();

	/* realizar la multiplicación en paralelo */
	#pragma omp parallel
	{
		int i, j, k, suma = 0;
		#pragma omp for 
		for(i = 0; i < n; i++)
		{
			y[i] = 0;
			for(j = 0; j < n; j++)
			{
				y[i] += (v[i] * A[j][k]);
			}
		}
	}

	run_time = omp_get_wtime() - start_time;
	printf("Execution time was %lf seconds\n",run_time);

	return 0;
}
