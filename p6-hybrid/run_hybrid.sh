#!/bin/bash
#SBATCH -J ej3_hybrid # nombre del job
#SBATCH -N 1 # numero de nodos
#SBATCH -c 16 # numero de tasks por nodo
#SBATCH --output=log_hybrid # numero de tasks por nodo

module load gcc/5.5.0
module load openmpi
srun mpirun -np 4 hybrid.out # siendo prueba_mpi el nombre del programa mpi
module unload gcc/5.5.0
module unload openmpi