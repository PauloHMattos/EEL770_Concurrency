#include "main.h"

int eating = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexFull = PTHREAD_MUTEX_INITIALIZER;


#define CLIENTS 18

int main()
{
    pthread_t threads[CLIENTS];
    int clientIds[CLIENTS];

    for (int i = 0; i < CLIENTS; i++)
    {
        clientIds[i] = i + 1;
        pthread_create(&threads[i], NULL, clientThread, &clientIds[i]);
    }

    for (int i = 0; i < CLIENTS; i++)
    {
        pthread_t th = threads[i];
        pthread_join(th, NULL);
    }

    printf("XXXXXXXXXX: Restaurante fechado\n");
    return 0;
}

void *clientThread(void *clientIdPtr)
{
    int clientId = *((int *)clientIdPtr);
    enterBar(clientId);
    
    // Creates a random time that the client takes to eat
    // Uses the client id as seed
    int eatingTime = getRandom(clientId, 100);
    waitFor(eatingTime);

    // Client finish eating and leaves the bar
    exitBar(clientId);
}

void enterBar(int clientId)
{
    pthread_mutex_lock(&mutexFull);
    pthread_mutex_lock(&mtx);
    printf("<<<<<<<<<<: Cliente %i sentou\n", clientId);
    eating++;

    if (eating < 5)
    {
        pthread_mutex_unlock(&mutexFull);
    }
    else
    {
        printf("##########: Todas as mesas estão cheias \n");
    }
    pthread_mutex_unlock(&mtx);
}

void exitBar(int clientId)
{
    pthread_mutex_lock(&mtx);
    printf(">>>>>>>>>>: Cliente %i saiu\n", clientId);
    eating--;
    if (eating == 0)
    {
        printf("##########: Mesa liberada \n");
        pthread_mutex_unlock(&mtx);
        pthread_mutex_unlock(&mutexFull);
    }
    else
    {
        pthread_mutex_unlock(&mtx);
    }
}