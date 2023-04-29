#include "trio.h"
#include <stdio.h>
#include <stdlib.h>

// Funções para manipular a estrutura de dados trio_t
void init_trio(trio_t *t)
{
    pthread_mutex_init(&t->lock, NULL);
    t->count = 0;
    pthread_cond_init(&t->cond, NULL);
}

void trio_enter(trio_t *t, int my_type)
{
    pthread_mutex_lock(&t->lock);

    // Garante que o trio só exista com threads de tipos diferentes e no máximo 3 threads.
    while (t->count == 3 || t->types[my_type - 1] > 0)
    {
        pthread_cond_wait(&t->cond, &t->lock);
    }
    t->types[my_type - 1] = 1;
    t->count++;

    // Inicia o trabalho em trio ou espera o trio ser formado
    if (t->count == 3)
    {
        pthread_cond_broadcast(&t->cond);
    }
    else
    {
        while (t->count < 3)
        {
            pthread_cond_wait(&t->cond, &t->lock);
        }
    }
    pthread_mutex_unlock(&t->lock);
}

void trio_leave(trio_t *t, int my_type)
{
    pthread_mutex_lock(&t->lock);
    t->types[my_type - 1] = 0;
    t->count--;

    // Garante que um novo trio só é formado quando a estrutura não estiver vazia de threads.
    if (t->count == 0)
    {
        pthread_cond_broadcast(&t->cond);
    }
    pthread_mutex_unlock(&t->lock);
}

void *thread_start(void *arg)
{
    int id = ((int *)arg)[0];
    int type = ((int *)arg)[1];
    int tsolo = ((int *)arg)[2];
    int ttrio = ((int *)arg)[3];

    spend_time(id, type, "S", tsolo);
    trio_enter(&trio, type);
    spend_time(id, type, "T", ttrio);
    trio_leave(&trio, type);
    pthread_exit(NULL);
}