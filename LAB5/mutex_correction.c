#include<stdio.h>
#include<pthread.h>

#define NUM_T 8
#define INCREMENTS_PER_THREAD 1000000

long long count = 0;
pthread_mutex_t mutex;

void* thread_func(void* args){
    for(int a = 0; a  < INCREMENTS_PER_THREAD; a++){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[NUM_T];

    for(int t = 0; t < NUM_T; t++){
        pthread_create(&threads[t], NULL, thread_func, NULL);
    }

    for(int x = 0; x < NUM_T; x++){
        pthread_join(threads[x], NULL);
    }
    pthread_mutex_destroy(&mutex);

    long long result_expected = (long long)NUM_T * INCREMENTS_PER_THREAD;
    printf("Valor final do count: %lld\n", count);
    printf("Expected: %lld\n", result_expected);

    if(count == result_expected){
        printf("Correct!\n");
    }

    return 0;
}




