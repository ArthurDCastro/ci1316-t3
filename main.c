#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "multi_partition.h"
#include "util.h"

int main(int argc, char *argv[])
{
    // Inicialização do MPI
    MPI_Init(&argc, &argv);

    // Variáveis do MPI
    int rank, np;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &name_len); // Nome do processador

    // Imprimir o nome e rank de cada processo
    printf("Processo %d rodando no processador %s\n", rank, processor_name);

    // Configuração dos parâmetros do programa
    if (argc < 2)
    {
        if (rank == 0)
        {
            printf("Uso: %s <nTotalElements>\n", argv[0]);
        }
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    int nTotalElements = atoi(argv[1]); // Número total de elementos
    int n = nTotalElements / np;        // Elementos locais por processo

    // Alocação dos vetores
    long long *Input = create_vector(n);  // Vetor de entrada local
    long long *Output = create_vector(n); // Vetor de saída local
    int *Pos = create_pos_vector(np);     // Índices iniciais das partições
    long long *P;                         // Vetor de partições

    // Inicialização do vetor de entrada local
    srand(2024 * 100 + rank); // Semente única para cada processo
    for (int i = 0; i < n; i++)
    {
        Input[i] = geraAleatorioLL();
    }

    // Geração e distribuição do vetor de partições
    if (rank == 0)
    {
        P = generate_random_vector(np, 1);                  // Gera o vetor de partições
        qsort(P, np, sizeof(long long), compare_long_long); // Ordena o vetor
    }
    else
    {
        P = create_vector(np); // Aloca espaço para receber P
    }
    MPI_Bcast(P, np, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    int NTIMES = 10; // Número de repetições
    double total_time = 0.0;

    for (int t = 0; t < NTIMES; t++)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        multi_partition(Input, n, P, np, Output, Pos);
        MPI_Barrier(MPI_COMM_WORLD);
        double end_time = MPI_Wtime();
        total_time += (end_time - start_time);
    }

    if (rank == 0)
    {
        printf("Tempo médio de particionamento: %.6f segundos\n", total_time / NTIMES);
    }

    // Verificação das partições
    verifica_particoes(P, np, Output, Pos);

    // Limpeza de memória
    destroy_vector(Input);
    destroy_vector(Output);
    destroy_vector(P);
    destroy_pos_vector(Pos);

    // Finalização do MPI
    MPI_Finalize();
    return EXIT_SUCCESS;
}
