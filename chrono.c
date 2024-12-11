// chrono.c
#include "chrono.h"
#include <stdio.h>

// Reseta o cronômetro
void chrono_reset(chronometer_t *chrono)
{
    chrono->xtotal_ns = 0;
    chrono->xn_events = 0;
}

// Inicia a contagem do tempo
void chrono_start(chronometer_t *chrono)
{
    clock_gettime(CLOCK_MONOTONIC_RAW, &(chrono->xadd_time1));
}

// Retorna o tempo total acumulado em nanosegundos
long long chrono_gettotal(chronometer_t *chrono)
{
    return chrono->xtotal_ns;
}

// Retorna o número total de eventos registrados
long long chrono_getcount(chronometer_t *chrono)
{
    return chrono->xn_events;
}

// Para a contagem de tempo e atualiza o tempo total acumulado
void chrono_stop(chronometer_t *chrono)
{
    clock_gettime(CLOCK_MONOTONIC_RAW, &(chrono->xadd_time2));

    long long ns1 = chrono->xadd_time1.tv_sec * 1000 * 1000 * 1000 + 
                    chrono->xadd_time1.tv_nsec;
    long long ns2 = chrono->xadd_time2.tv_sec * 1000 * 1000 * 1000 + 
                    chrono->xadd_time2.tv_nsec;
    long long deltat_ns = ns2 - ns1;

    chrono->xtotal_ns += deltat_ns;
    chrono->xn_events++;
}

// Gera relatório do tempo total e do tempo médio por operação
void chrono_reportTime(chronometer_t *chrono, char *s)
{
    printf("\n%s deltaT(ns): %lld ns for %ld ops \n"
           "        ==> each op takes %lld ns\n",
           s, chrono->xtotal_ns, chrono->xn_events,
           chrono->xtotal_ns / chrono->xn_events);
}

// Gera relatório do tempo médio considerando um loop de operações
void chrono_report_TimeInLoop(chronometer_t *chrono, char *s, int loop_count)
{
    printf("\n%s deltaT(ns): %lld ns for %ld ops \n"
           "        ==> each op takes %lld ns\n",
           s, chrono->xtotal_ns, chrono->xn_events * loop_count,
           chrono->xtotal_ns / (chrono->xn_events * loop_count));
}