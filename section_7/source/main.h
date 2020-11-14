#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int getRandom(int seed, int max)
{
    srand(time(NULL) + seed);
    return rand() % max;
}

void waitFor(int tempo)
{
    for (int i = 0; i < tempo; i++)
    {
        usleep(100000);
    }
}