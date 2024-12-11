# Trabalho 3 - Multi-Particionamento com MPI

Este projeto implementa um particionamento de vetores utilizando **MPI**. O objetivo é dividir um vetor de números inteiros longos (`long long`) em faixas definidas, redistribuir os dados entre processos e medir o desempenho em um cluster.

## 🛠️ Compilação

1. Compile o projeto com:

   ```bash
   make
   ```

2. Para limpar os arquivos gerados:
   ```bash
   make clean
   ```

## 🏃‍♂️ Execução

Execute o programa com:

```bash
mpirun -np <n_processos> ./main <n_elementos> <n_particoes>
```

### Exemplo

```bash
mpirun -np 4 ./main 8000000 4
```

- `<n_processos>`: Número de processos MPI.
- `<n_elementos>`: Número total de elementos no vetor.
- `<n_particoes>`: Número de partições.

## 📝 Observações

- Certifique-se de que **MPI** está instalado e configurado.
- Utilize os scripts SLURM para experimentos em cluster.
