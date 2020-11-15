#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void *searcherThread(void* searcherIdPtr);
void *inserterThread(void* inserterIdPtr);
void *deleterThread(void* deleterIdPtr);

void searchList(int searcherId);
void insertList(int inserterId);
void removeList(int removerId);

int getRandom(int seed, int max)
{
    srand(time(NULL) + seed);
    return rand() % max;
}

void waitFor(int timeInSeconds)
{
    for (int i = 0; i < timeInSeconds; i++)
    {
        sleep(1);
    }
}

/// Create a random sleep time using the thread id as a seed
/// This is used to add more variaty in the threads execution order
void randomSleep(int seed, int max)
{
    int sleepTime = getRandom(seed, max);
    waitFor(sleepTime);
}