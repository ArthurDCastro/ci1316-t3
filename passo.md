### Passo 1: **Preparar o Ambiente**

1. Certifique-se de que o ambiente MPI está corretamente configurado no cluster ou na sua máquina local.
   - Instale o MPI, como **MPICH** ou **OpenMPI**, caso não esteja instalado.
   - Teste o exemplo fornecido pelo professor para garantir que MPI está funcionando:
     ```bash
     mpicc -o mpi_hello mpi_hello.c
     mpirun -np 4 ./mpi_hello
     ```
   - Verifique se as saídas mostram diferentes `ranks` e o nome dos processadores.

---

### Passo 2: **Definir Estrutura do Programa**

1. Baseie-se no exemplo do professor para expandir o código e adicionar:
   - Geração e distribuição dos dados.
   - Particionamento utilizando `multi_partition`.
   - Redistribuição dos dados entre processos usando funções coletivas do MPI.

---

### Passo 3: **Implementar Geração e Distribuição de Dados**

1. **Distribuir Tarefas por Processos:**

   - Cada processo deve gerar localmente seu segmento do vetor de entrada (`Input`) de tamanho `n = nTotalElements / np`.
   - Apenas o processo de `rank 0` cria o vetor de partições (`P`) e transmite para os demais processos usando `MPI_Bcast`.

2. **Exemplo de Código:**

   ```c
   int nTotalElements = 8000000; // Total de elementos
   int np, rank, n;
   long long *Input, *P;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &np);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   n = nTotalElements / np;
   Input = malloc(n * sizeof(long long));

   srand(2024 * 100 + rank); // Inicializa semente para números aleatórios
   for (int i = 0; i < n; i++) {
       Input[i] = geraAleatorioLL();
   }

   if (rank == 0) {
       P = generate_random_vector(np, 1); // Vetor de partições
       qsort(P, np, sizeof(long long), compare_long_long);
   } else {
       P = malloc(np * sizeof(long long));
   }

   MPI_Bcast(P, np, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
   ```

---

### Passo 4: **Integrar a Função `multi_partition`**

1. **Chamar a Função de Particionamento:**

   - Use a função `multi_partition` em cada processo para organizar os dados localmente.
   - Garanta que a saída (`Output`) e os índices iniciais das partições (`Pos`) sejam corretamente calculados.

2. **Exemplo de Código:**

   ```c
   long long *Output = malloc(n * sizeof(long long));
   int *Pos = malloc(np * sizeof(int));

   multi_partition(Input, n, P, np, Output, Pos);
   ```

---

### Passo 5: **Redistribuição de Dados**

1. Use **funções coletivas do MPI** para redistribuir os dados particionados.

   - Cada processo deve enviar sua partição correspondente para o processo adequado.
   - Utilize `MPI_Alltoallv` para redistribuir os dados:

     ```c
     int *sendcounts = malloc(np * sizeof(int)); // Tamanhos dos envios
     int *recvcounts = malloc(np * sizeof(int)); // Tamanhos dos recebimentos
     int *sdispls = malloc(np * sizeof(int));    // Deslocamentos dos envios
     int *rdispls = malloc(np * sizeof(int));    // Deslocamentos dos recebimentos

     // Preencher sendcounts e sdispls com base em Pos
     // ...

     MPI_Alltoallv(local_data, sendcounts, sdispls, MPI_LONG_LONG,
                   global_data, recvcounts, rdispls, MPI_LONG_LONG, MPI_COMM_WORLD);
     ```

---

### Passo 6: **Verificação**

1. Após a redistribuição, utilize `verifica_particoes` em cada processo para validar os resultados.

2. **Exemplo:**
   ```c
   verifica_particoes(Input, n, P, np, Output, Pos);
   ```

---

### Passo 7: **Medição de Tempo**

1. Meça o tempo de execução da função `multi_partition` e das redistribuições.

   - Utilize `MPI_Wtime()` para medir o tempo:

     ```c
     double start_time, end_time;
     start_time = MPI_Wtime();

     // Chamada de multi_partition
     multi_partition(Input, n, P, np, Output, Pos);

     end_time = MPI_Wtime();
     if (rank == 0) {
         printf("Tempo de execução: %f segundos\n", end_time - start_time);
     }
     ```

---

### Passo 8: **Experimentos com SLURM**

1. **Criar scripts SLURM** para rodar os testes:

   - Experimento 1: 1 nó com 8 processos MPI.
   - Experimento 2: 2 nós com 8 processos MPI por nó (16 processos no total).
   - Experimento 3: 4 nós com 8 processos MPI por nó (32 processos no total).

2. **Exemplo de Script SLURM:**

   ```bash
   #!/bin/bash
   #SBATCH --job-name=multi_partition_exp1
   #SBATCH --nodes=1
   #SBATCH --ntasks-per-node=8
   #SBATCH --exclusive
   #SBATCH --output=exp1_output.txt

   mpirun ./multi_partition_program
   ```

---

### Passo 9: **Gerar Resultados e Relatório**

1. **Resultados em Planilhas**:

   - Preencha as planilhas com os tempos de execução e cálculos de throughput (EPS - elementos particionados por segundo).
   - Calcule o speedup comparando os tempos entre os diferentes experimentos.

2. **Relatório Final**:
   - Inclua descrição do algoritmo, configuração do ambiente, tabelas com resultados e conclusões.
   - Adicione os comandos `lscpu` e `lstopo` no apêndice.

---

### Passo 10: **Testes Finais**

1. Execute o programa com os scripts SLURM.
2. Valide os resultados.
3. Submeta o código, scripts e relatório conforme solicitado.
