#include "main.h"
#include <pthread.h>

#define SEARCHER_COUNT 5
#define INSERTER_COUNT 2
#define REMOVER_COUNT 2

pthread_rwlock_t readWriteLock = PTHREAD_RWLOCK_INITIALIZER;

int main()
{
    pthread_t searcherThreads[SEARCHER_COUNT];
    pthread_t inserterThreads[INSERTER_COUNT];
    pthread_t removerThreads[REMOVER_COUNT];
    
    for (int i = 0; i < SEARCHER_COUNT; i++)
    {
        pthread_create(&searcherThreads[i], NULL, searcher, NULL);
    }
    for (int i = 0; i < INSERTER_COUNT; i++)
    {
        pthread_create(&inserterThreads[i], NULL, inserter, NULL);
    }
    for (int i = 0; i < REMOVER_COUNT; i++)
    {
        pthread_create(&removerThreads[i], NULL, remover, NULL);
    }

    pthread_join(removerThreads[0], NULL);
    return 0;
}

void searchList()
{
    pthread_rwlock_rdlock(&readWriteLock);
    printf("Searching item\n");
    pthread_rwlock_unlock(&readWriteLock);
}

void insertList()
{
    pthread_rwlock_wrlock(&readWriteLock);
    printf("Inserting item\n");
    pthread_rwlock_unlock(&readWriteLock);
}

void removeList()
{
    pthread_rwlock_wrlock(&readWriteLock);
    printf("Removing item\n");
    pthread_rwlock_unlock(&readWriteLock);
}

void *searcher()
{
    while (1)
    {
        searchList();
        sleep(1);
    }
}

void *inserter()
{
    while (1)
    {
        insertList();
        sleep(1);
    }
}

void *remover()
{
    while (1)
    {
        removeList();
        sleep(1);
    }
}
