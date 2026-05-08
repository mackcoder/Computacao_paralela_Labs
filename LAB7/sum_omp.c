#include <stdio.h>
#include <omp.h>
#include <time.h>

#define SIZE 100000

int main(){
    long vetorA[SIZE];
    long vetorB[SIZE];
    long vetorC[SIZE];

    struct timespec start_par, end_par, start_seq, end_seq;
    double tempo_par;
    double tempo_seq;
    // ----------------------------------------------------------------//
    // Parte paralelizável:
    clock_gettime(CLOCK_MONOTONIC, &start_par);
    #pragma omp parallel for
    for (int t = 0; t < SIZE; t++){
        vetorA[t] += t;
        vetorB[t] += t * 2;
    }

    #pragma omp parallel for
    for(int idx = 0; idx < SIZE; idx++){
        vetorC[idx] = vetorA[idx] + vetorB[idx];
    }

    long soma_total_par = 0.0;
    #pragma omp parallel for reduction(+:soma_total_par)
    for(int b = 0; b < SIZE; b++){
        soma_total_par += vetorC[b];
    }
    clock_gettime(CLOCK_MONOTONIC, &end_par);
    // ----------------------------------------------------------------//
    // Parte sequencial:
    clock_gettime(CLOCK_MONOTONIC, &start_seq);
    long soma_total_seq = 0.0;
    for(int a = 0; a < SIZE; a++){
        soma_total_seq += vetorA[a] + vetorB[a];
    }
    clock_gettime(CLOCK_MONOTONIC, &end_seq);
    // ----------------------------------------------------------------//
    // CALCULATE TIME EXEC
    tempo_par = (end_par.tv_sec - start_par.tv_sec) + (end_par.tv_nsec - start_par.tv_nsec) / 1e9;
    tempo_seq = (end_seq.tv_sec - start_seq.tv_sec) + (end_seq.tv_nsec - start_seq.tv_nsec) / 1e9;
    // ----------------------------------------------------------------//
    printf("\n--- RESPOSTA RECEBIDA DAS THREADS -> PARARELA ---\n");
    printf("Soma total: %ld\n", soma_total_par);
    printf("Tempo gasto: %.6f segundos\n", tempo_par);

    // ----------------------------------------------------------------//

    printf("\n--- RESPOSTA RECEBIDA DAS THREADS -> SEQUENCIAL ---\n");
    printf("Soma total: %ld\n", soma_total_seq);
    printf("Tempo gasto: %.6f segundos\n", tempo_seq);
    return 0;
}