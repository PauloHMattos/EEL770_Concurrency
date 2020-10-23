#include "main.h"
#include <pthread.h>

pthread_rwlock_t readWriteLock = PTHREAD_RWLOCK_INITIALIZER;

int main()
{
    pthread_t searcherThreads[2];
    pthread_t inserterThreads[2];
    pthread_t removerThreads[2];
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&searcherThreads[i], NULL, searcher, NULL);
        pthread_create(&inserterThreads[i], NULL, inserter, NULL);
        pthread_create(&removerThreads[i], NULL, remover, NULL);
    }
    pthread_join(removerThreads[0], NULL);
    return 0;
}

void searchList()
{
    pthread_rwlock_tryrdlock(&readWriteLock);
    printf("Searching item\n");
    pthread_rwlock_unlock(&readWriteLock);
}

void insertList()
{
    pthread_rwlock_trywrlock(&readWriteLock);
    printf("Inserting item\n");
    pthread_rwlock_unlock(&readWriteLock);
}

void removeList()
{
    pthread_rwlock_trywrlock(&readWriteLock);
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
