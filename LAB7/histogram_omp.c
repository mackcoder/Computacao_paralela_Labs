#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 256
#define PIXELS 1000000

double tempo_exec;
struct timespec start, end;
// Lendo pixels:
int main(){
    int *px = malloc(PIXELS * sizeof(int));
    int hist[SIZE] = {0};
    srand(time(NULL));
    for(int x = 0; x < PIXELS; x++){
        px[x] = rand() % 256;
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    // Calculando histograma:
    for(int y = 0; y < PIXELS; y++){
        hist[px[y]]++; 
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Verifica saida:
    int total_sum = 0;
    for(int a = 0; a < SIZE; a++){
        total_sum += hist[a];
    }
    

    tempo_exec = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("=== HISTOGRAMA CONCLUIDO ===\n");
    printf("Total pixels processados: %d\n", total_sum);
    printf("Tempo total: %.6f segundos", tempo_exec);

    free(px);
    return 0;
}
