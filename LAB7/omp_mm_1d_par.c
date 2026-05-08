#include <stdio.h>
#include <omp.h>
#include <time.h>

#define SIZE 100

int matrizA[SIZE][SIZE];
int matrizB[SIZE][SIZE];
int matrizC[SIZE][SIZE];

struct timespec start_par, end_par;
double tempo_par;


int main(){

    // ----------------------------------------------------------------//
    // Preenchendo paralelamente
    for(int x = 0; x < SIZE; x++){
        for(int y = 0; y < SIZE; y++){
            matrizA[x][y] = y * 2;
            matrizB[x][y] = y * 3;
        }
    }

    for(int x = 0; x < SIZE; x++){
        for(int y = 0; y < SIZE; y++){
            matrizC[x][y] = 0; 
        }
    }

    // ----------------------------------------------------------------//
    // Cálculo Paralela 
    clock_gettime(CLOCK_MONOTONIC, &start_par);
    #pragma omp parallel for
    for(int i = 0; i < SIZE; i++){
        for(int k = 0; k < SIZE; k++){
            for(int j = 0; j < SIZE; j++){
                matrizC[i][k] += matrizA[i][j] * matrizB[j][k];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_par);
    // ----------------------------------------------------------------//
    // Main
    tempo_par = (end_par.tv_sec - start_par.tv_sec) + (end_par.tv_nsec - start_par.tv_nsec) / 1e9;
    printf("/n Tempo total: %.6f segundos", tempo_par);
    
    return 0;
}