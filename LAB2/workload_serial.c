#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESSES 4
#define VECTOR_SIZE 200000000

void paralelismo(double* v, int start, int end){
    for(int t = 0; t < VECTOR_SIZE; t++){
        v[t] = sin(v[t]) * cos(v[t]) + sqrt(v[t]);
    }
}


int main(){
    double* vetor = (double*)malloc(VECTOR_SIZE * sizeof(double));
    int vector_piece = VECTOR_SIZE / NUM_PROCESSES;
    for(int y = 0; y < VECTOR_SIZE; y++){
        vetor[y] = (double)y;
    }
    for(int x = 0; x < NUM_PROCESSES - 1; x++){
        pid_t pid = fork();

        if(pid < 0){
            fprintf(stderr, "Fork falhou\n");
            return 1;
        } else if(pid == 0){
            int comeco_ind = x * vector_piece;
            int end_ind = (x + 1) * vector_piece;
        } else {
            
        }
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    paralelismo(vetor, 0, VECTOR_SIZE);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double tempo_exec = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Tempo de Execução do Sequencial foi de: %f segundos.", tempo_exec);
    free(vetor);
    return 0;
}
