#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "spend_time.h"
#include "trio.h"

int main(int argc, char *argv[])
{
    pthread_t threads[999];
    int args[999][4];
    int num_threads = 0;

    init_trio(&trio);

    while (scanf("%d %d %d %d", &args[num_threads][0], &args[num_threads][1], &args[num_threads][2], &args[num_threads][3]) != EOF)
    {
        pthread_create(&threads[num_threads], NULL, thread_start, (void *)args[num_threads]);
        num_threads++;
    }
    // Aguarda o término das threads
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
