#include <pthread.h>

typedef struct
{
    pthread_mutex_t lock;
    int types[3]; // tipos das threads no trio atual
    int count;    // quantidade de threads no trio atual
    pthread_cond_t cond;
} trio_t;
trio_t trio;

void init_trio(trio_t *t);
void trio_enter(trio_t *t, int my_type);
void trio_leave(trio_t *t, int my_type);
void *thread_start(void *arg);