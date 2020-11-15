#include "main.h"
#include <pthread.h>

#define CAPACITY 10
#define SAVAGES 5

volatile int servings = CAPACITY;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t emptyCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t fullCond = PTHREAD_COND_INITIALIZER;


int main()
{                    
    pthread_t cookThread;
    pthread_create(&cookThread, NULL, cooker, NULL);
    
    pthread_t savageThreads[SAVAGES];
    for (int i = 0; i < SAVAGES; i++)
    {
        pthread_create(&savageThreads[i], NULL, savage, NULL);
    }

    // Join the cook thread so that the execution won't finish until the thread does
    pthread_join(cookThread, NULL);
    return 0;
}

void *cooker()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while (servings != 0)
        {
            pthread_cond_wait(&emptyCond, &mutex);
        }
        
        servings = CAPACITY;
        printf("Cozinheiro encheu o pote\n");
        pthread_cond_signal(&fullCond);
        pthread_mutex_unlock(&mutex);
    }
}

void *savage()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while (servings == 0)
        {
            pthread_cond_signal(&emptyCond);
            pthread_cond_wait(&fullCond, &mutex);
        }

        servings--;
        printf("Selvagem pegou uma porção\n");
        pthread_mutex_unlock(&mutex);
        usleep(100000);
    }
}