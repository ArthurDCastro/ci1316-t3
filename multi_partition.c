#include <pthread.h>
#include <limits.h> // Para LLONG_MAX
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "multi_partition.h"

void count_partition(int start, int end, long long *Input, long long *P, int np, int *counts)
{
    // Contagem local com busca binária
    for (int i = start; i < end; i++)
    {
        int partition = binary_search(P, 0, np - 1, Input[i]);
        counts[partition]++;
    }
}

void fill_output(long long *Input, int n, long long *P, int np, long long *Output, int *Pos)
{
    // Vetores temporários para cada faixa no Output
    int *current_index = malloc(np * sizeof(int));
    for (int i = 0; i < np; i++)
    {
        current_index[i] = Pos[i];
    }

    // Preenche o vetor Output particionado
    for (int i = 0; i < n; i++)
    {
        // Determina a partição do elemento atual de Input
        int partition = binary_search(P, 0, np - 1, Input[i]);

        // barreira
        Output[current_index[partition]] = Input[i];
        current_index[partition]++;
    }

    free(current_index);
}

void multi_partition(long long *Input, int n, long long *P, int np, long long *Output, int *Pos)
{

    int *counts = malloc(sizeof(int) * np); // Inicializa contagens locais
    for (int i = 0; i < np; i++)
    {
        counts[i] = 0;
    }

    count_partition(0, n - 1, Input, P, np, counts);

    // Global counts agora pode ser usado para calcular Pos (prefix sum)

    // Inicializa o vetor Pos com o prefix sum de global_counts
    Pos[0] = 0;
    for (int i = 1; i < np; i++)
    {
        Pos[i] = Pos[i - 1] + counts[i - 1];
    }

    fill_output(Input, n, P, np, Output, Pos);

    free(counts);
}

void verifica_particoes(long long *Input, int n, long long *P, int np, long long *Output, int *Pos)
{
    int erro = 0;

    // Verifica cada partição
    for (int i = 0; i < np - 1; i++)
    {
        for (int j = Pos[i]; j < Pos[i + 1]; j++)
        {
            // Verifica se o elemento está na partição correta
            if (Output[j] >= P[i])
            {
                erro = 1;
                break;
            }
        }

        if (erro)
        {
            break;
        }
    }

    // Resultado da verificação
    if (erro)
    {
        printf("\n===> particionamento COM ERROS\n");
    }
    else
    {
        printf("\n===> particionamento CORRETO\n");
    }
}

int binary_search(long long *arr, int l, int r, long long value)
{
    int left = l, right = r;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (value < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    // `left` é o índice da partição em que o valor pertence
    return left;
}
