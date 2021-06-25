#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void swap(int *x, int *y){
  int temp = *x;
  *x = *y;
  *y = temp;
}

int separate(int *x, int low, int high){
  int i, pivot, last;
  pivot = x[low]; 
  swap(x+low, x+high);
  last = low;
  for(i = low; i<high; i++){
    if(x[i] <= pivot){
      swap(x+last, x+i);
      last += 1;
    }
  }
  swap(x+last, x+high);
  return last;
}

void qs(int *z, int zstart, int zend, int firstcall){
  int pivot;
  if(firstcall == 1) {
    qs(z,0,zend,0);
  } 
  else {
    if(zstart < zend) {
      pivot = separate(z, zstart,zend);
      #pragma omp task firstprivate(z, zstart, pivot) 
      {
        qs(z, zstart, pivot - 1, 0);
      }
        qs(z, pivot + 1, zend, 0);
    }
  }
}

int main(int argc, char **argv){
  double start_time, run_time;
  int i,n,*w;
  n = atoi(argv[1]);
  w = malloc(n*sizeof(int));

  for(i = 0; i < n; i++){
    w[i] = rand()%100;
  }
  
  omp_set_num_threads(2);

  start_time = omp_get_wtime();

  #pragma omp parallel 
  {
    int id = omp_get_thread_num();
    int nthrds = omp_get_num_threads();
    #pragma omp single nowait
      qs(w, 0, n-1, 1);
  }

  if(n < 25) {
    for(i=0;i<n;i++){
      printf("%d\n",w[i]);
    }
  }

  run_time = omp_get_wtime() - start_time;
	printf("Execution time was %lf seconds\n ",run_time);

  return 0;
} 
