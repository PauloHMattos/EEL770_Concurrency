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

    int threadIds[SEARCHER_COUNT + INSERTER_COUNT + REMOVER_COUNT];
    
    for (int i = 0; i < SEARCHER_COUNT; i++)
    {
        threadIds[i] = i + 1;
        pthread_create(&searcherThreads[i], NULL, &searcher, &threadIds[i]);
    }
    for (int i = 0; i < INSERTER_COUNT; i++)
    {
        threadIds[i + SEARCHER_COUNT] = i + 1;
        pthread_create(&inserterThreads[i], NULL, &inserter, &threadIds[i + SEARCHER_COUNT]);
    }
    for (int i = 0; i < REMOVER_COUNT; i++)
    {
        threadIds[i + SEARCHER_COUNT + INSERTER_COUNT] = i + 1;
        pthread_create(&removerThreads[i], NULL, &remover, &threadIds[i + SEARCHER_COUNT + INSERTER_COUNT]);
    }

    pthread_join(removerThreads[0], NULL);
    return 0;
}

void searchList(int searcherId)
{
    pthread_rwlock_rdlock(&readWriteLock);
    printf("[Searcher %i] Searching item\n", searcherId);
    pthread_rwlock_unlock(&readWriteLock);
}

void insertList(int inserterId)
{
    pthread_rwlock_wrlock(&readWriteLock);
    printf("[Inserter %i] Inserting item\n", inserterId);
    pthread_rwlock_unlock(&readWriteLock);
}

void removeList(int removerId)
{
    pthread_rwlock_wrlock(&readWriteLock);
    printf("[Remover %i] Removing item\n", removerId);
    pthread_rwlock_unlock(&readWriteLock);
}

void searcher(void* searcherIdPtr)
{
    int searcherId = *(int*)searcherIdPtr;
    while (1)
    {
        searchList(searcherId);
        sleep(1);
    }
}

void inserter(void* inserterIdPtr)
{
    int inserterId = *(int*)inserterIdPtr;
    while (1)
    {
        insertList(inserterId);
        sleep(1);
    }
}

void remover(void* removerIdPtr)
{
    int removerId = *(int*)removerIdPtr;
    while (1)
    {
        removeList(removerId);
        sleep(1);
    }
}