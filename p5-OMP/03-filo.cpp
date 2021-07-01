// Mac: g++ -Xpreprocessor -fopenmp 03-filo.cpp -o 03-filo -lomp
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

#define FILOSOFOS   5

int main(int argc, char ** argv) {
  int i;
  int id;
  int tenedor_derecho;
  int tenedor_izquierdo;
  static omp_lock_t tenedores[FILOSOFOS]; // array de locks que representan los tenedores

  omp_set_num_threads (4);

  //Inicializa locks
  for(i = 0; i < FILOSOFOS; i++) {
      omp_init_lock(&tenedores[i]);
  }

  //Crea los threads para cada filosofo.
  #pragma omp parallel shared ( tenedores ) private ( id, tenedor_derecho, tenedor_izquierdo )
  {
    //Es necesario esperar a que todos los threads comienzen
    #pragma omp barrier

    id = omp_get_thread_num();

    //el primer filosofo y hasta FILOSOFOS-1 consigue el tenedor izquierdo primero, despues el derecho
    if(id < FILOSOFOS -1)
    {
        tenedor_derecho = id;
        tenedor_izquierdo = id+1;
    } else { // los demas filosofos tienen los tenedores intercambiados
        tenedor_derecho = 0;
        tenedor_izquierdo = id;
    }

    //Acquire tenedores (semaphores), eat, wait for 100 microseconds, then release 
    //tenedores (semaphores).
    omp_set_lock(&tenedores[tenedor_izquierdo]);
    omp_set_lock(&tenedores[tenedor_derecho]);

    printf("filosofo %d comiendo...\n", id);

    omp_unset_lock(&tenedores[tenedor_izquierdo]);
    omp_unset_lock(&tenedores[tenedor_derecho]);
  }

  //Elimina los locks despues de acabar de comer.
  for(i = 0; i < FILOSOFOS; i++) {
      omp_destroy_lock(&tenedores[i]);
  }

  return 0;
}