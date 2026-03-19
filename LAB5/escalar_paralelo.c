#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define N 15
#define NUM_T 5

// Inicializando variáveis e semáforos: 
pthread_mutex_t locker;
int vector1[N];
int vector2[N];
int piece = N / NUM_T;
double global_dot_product = 0;

void preenche_v(){
    for(int idx = 0; idx < N; idx++){
        int random1 = rand();
        int random2 = rand();
        vector1[idx] = random1;
        vector2[idx] = random2;
    }
}

void* produto(void* arg){
    int soma_local = 0;
    int id_thread = (long)arg;

    for(int x = 0; x < N; x++){
        soma_local += (vector1[x] * vector2[x]);
    }
    pthread_mutex_lock(&locker);
    global_dot_product += soma_local;
    pthread_mutex_unlock(&locker);


    return NULL;
}

int main(){
    pthread_mutex_init(&locker, NULL);
    pthread_t threads[NUM_T];
    preenche_v();

    for(int a = 0; a < NUM_T; a++){
        pthread_create(&threads, NULL, produto ,NULL);
    }


}



