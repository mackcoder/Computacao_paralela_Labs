#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <linux/time.h>

#define TAM_VECTOR 200000000

void sequencial(double* v, int start, int end){
    for(int t = 0; t < TAM_VECTOR; t++){
        v[t] = sin(v[t]) * cos(v[t]) + sqrt(v[t]);
    }
}

int main(){
    double* vetor = (double*)malloc(TAM_VECTOR * sizeof(double));
    for(int y = 0; y < TAM_VECTOR; y++){
        vetor[y] = (double)y;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    sequencial(vetor, 0, TAM_VECTOR);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double tempo_exec = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Tempo de Execução do Sequencial foi de: %f segundos.", tempo_exec);

    return 0;
}
