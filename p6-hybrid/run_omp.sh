#!/bin/bash
#SBATCH -J ej3_openmp # nombre del job
#SBATCH -N 2 # numero de nodos
#SBATCH --tasks-per-node=1 # numero de tasks por nodo
#SBATCH --output=log_openmp # numero de tasks por nodo

module load gcc/5.5.0
srun a.out 512 2 # siendo prueba_mpi el nombre del programa mpi
module unload gcc/5.5.0