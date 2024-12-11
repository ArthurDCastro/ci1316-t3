#ifndef MULTI_PARTITION_H
#define MULTI_PARTITION_H

#include <pthread.h>
#include <limits.h> // Para LLONG_MAX
#include <stdlib.h>

/**
 * @brief Conta o número de elementos em cada partição de um intervalo do vetor de entrada.
 *
 * @param start Índice inicial do intervalo no vetor de entrada.
 * @param end Índice final (exclusivo) do intervalo no vetor de entrada.
 * @param Input Ponteiro para o vetor de entrada contendo os valores a serem particionados.
 * @param P Ponteiro para o vetor de partições contendo os limites das faixas.
 * @param np Número de partições (tamanho do vetor P).
 * @param local_counts Ponteiro para o vetor onde será armazenada a contagem de elementos em cada partição.
 */
void count_partition(int start, int end, long long *Input, long long *P, int np, int *local_counts);

/**
 * @brief Preenche o vetor `Output` com os valores do vetor `Input`, particionados de acordo com as faixas definidas em `P`.
 *
 * @param Input Ponteiro para o vetor de entrada contendo os valores a serem particionados.
 * @param n Tamanho do vetor de entrada `Input` (número de elementos).
 * @param P Ponteiro para o vetor que define os limites das faixas de particionamento.
 * @param np Número de faixas de particionamento (tamanho do vetor `P`).
 * @param Output Ponteiro para o vetor de saída, onde os valores particionados serão armazenados.
 * @param Pos Ponteiro para um vetor que contém os índices iniciais para cada faixa no vetor `Output`.
 */
void fill_output(long long *Input, int n, long long *P, int np, long long *Output, int *Pos);

/**
 * @brief Realiza o particionamento do vetor de entrada `Input` em faixas definidas pelo vetor `P`,
 *        preenchendo o vetor de saída `Output` e calculando os índices iniciais de cada faixa em `Pos`.
 *
 * @param Input Ponteiro para o vetor de entrada contendo os valores a serem particionados.
 * @param n Número total de elementos no vetor de entrada `Input`.
 * @param P Ponteiro para o vetor que define os limites das partições (deve estar ordenado).
 * @param np Número de partições, ou seja, o tamanho do vetor `P`.
 * @param Output Ponteiro para o vetor de saída onde os valores serão armazenados particionados.
 * @param Pos Ponteiro para o vetor que conterá os índices iniciais de cada faixa no vetor `Output`.
 */
void multi_partition(long long *Input, int n, long long *P, int np, long long *Output, int *Pos);


/**
 * @brief Realiza uma busca binária para encontrar a partição à qual um valor pertence.
 *
 * @param arr Ponteiro para o vetor que define os limites das partições.
 * @param l Índice inicial do intervalo de busca (geralmente 0).
 * @param r Índice final do intervalo de busca (geralmente tamanho do vetor - 1).
 * @param value O valor para o qual a partição será determinada.
 * @return O índice da partição no vetor `arr` em que o valor pertence.
 */
int binary_search(long long *arr, int l, int r, long long value);


#endif // MULTI_PARTITION_H
