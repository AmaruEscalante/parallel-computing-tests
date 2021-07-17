#!/bin/bash
#SBATCH -J bucket2 # nombre del job
#SBATCH -p investigacion # nombre de la particion 
#SBATCH -N 16 # numero de nodos
#SBATCH --tasks-per-node=3 # numero de tasks por nodo

module load openmpi/2.1.6 # carga el modulo de openmpi version 2.1.6
srun bucketsort # bucketsort algorithm
module unload openmpi/2.1.6 