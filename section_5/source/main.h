#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void *cookerThread();
void *savageThread(void* savageIdPtr);

void eat(int savageId);
void getServingFromPot(int savageId);

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