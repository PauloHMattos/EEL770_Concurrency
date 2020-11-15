#include "main.h"

int eating = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexFull = PTHREAD_MUTEX_INITIALIZER;

void enter_bar(void *clientIdPtr)
{
    int clientId = *((int *)clientIdPtr);
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

    int threadId = pthread_self();

    // Cria um tempo de atendimento "aleatório" usando o id da thread como seed
    int eatingTime = getRandom(threadId, 100);

    // Simula o tempo que o cliente leva para comer
    waitFor(eatingTime);

    // Sai do bar
    exit_bar(clientId);
}

void exit_bar(int clientId)
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

#define CLIENTS 18

int main()
{
    pthread_t threads[CLIENTS];
    int clientIds[CLIENTS];

    for (int i = 0; i < CLIENTS; i++)
    {
        clientIds[i] = i + 1;
        pthread_create(&threads[i], NULL, &enter_bar, &clientIds[i]);
    }

    for (int i = 0; i < CLIENTS; i++)
    {
        pthread_t th = threads[i];
        pthread_join(th, NULL);
    }

    printf("Fim\n");
    return 0;
}