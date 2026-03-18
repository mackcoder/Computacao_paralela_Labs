#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define TAM 10000000

long long vector[TAM];

void* max_finder(void* arg){
    for(int piper = 0; piper < TAM; piper++){
        long random_num = rand();
        vector[piper] = random_num;
    }
    
}


