#!/bin/bash
#SBATCH --exclusive
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=8
#SBATCH --job-name=mpihello_job
echo -----------------------------------
echo -----------------------------------
echo -----------------------------------
echo ---------- ATENCAO: usar --exclusive na linha de comando
echo -----------------------------------

##### SBATCH --output=saida.out

echo "$0 rodando no host " `hostname`  
echo "$0 rodando no host " `hostname` >saida.txt

echo "SLURM_JOB_NAME: "	$SLURM_JOB_NAME	
echo "SLURM_NODELIST: " $SLURM_NODELIST 
echo "SLURM_JOB_NODELIST: " $SLURM_JOB_NODELIST
echo "SLURM_JOB_CPUS_PER_NODE: " $SLURM_JOB_CPUS_PER_NODE

# Load necessary modules (adjust paths as needed)
#module load openmpi/4.1.4

# Run the MPI program
# mpirun ./mpiHello

NTIMES=10
echo "nt " $NTIMES
MAX_EXECS=10
echo "MAX_EXECS " $MAX_EXECS


echo "Executando $NTIMES vezes com $1 elementos e 1 nodo, e 8 processos MPI:"
for j in $(seq 1 $NTIMES);
do
      mpirun -np ./main $1
      # ./multi_partition $1 | tee -a saida.txt | grep -oP '(?<=total_time_in_seconds: )[^ ]*'

done


echo "O tempo total dessa shell foi de" $SECONDS "segundos"
echo "SLURM_JOB_NAME: "	$SLURM_JOB_NAME	
echo "SLURM_NODELIST: " $SLURM_NODELIST 
echo "SLURM_JOB_NODELIST: " $SLURM_JOB_NODELIST
echo "SLURM_JOB_CPUS_PER_NODE: " $SLURM_JOB_CPUS_PER_NODE
#imprime infos do job slurm (e.g. TEMPO até aqui no fim do job)
squeue -j $SLURM_JOBID
