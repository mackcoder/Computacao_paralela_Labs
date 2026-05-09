#include<stdio.h>
#include<omp.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

#define K 1024
#define SIZE 4

static double diff_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main(){
    

    static double matrizA[K][K], matrizB[K][K], matrizC[K][K];
    struct timespec start_static, end_static, start_dynamic, end_dynamic;
    struct timespec start_guided, end_guided, start_auto, end_auto;
    double tempo_static, tempo_dynamic, tempo_guided, tempo_auto;

    printf("--- PROCESSING MULTIPLICACAO STATIC ---\n");

    // Preenchendo as matrizes:
    for(int x = 0; x < K; x++){
        for(int y = 0; y < K; y++){
            matrizA[x][y] = 1.0;
            matrizB[x][y] = 2.0;
            matrizC[x][y] = 0.0;  
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &start_static);
    #pragma omp parallel for schedule(static, SIZE)

    for(int i = 0; i < K; i++){
        for(int k = 0; k < K; k++){
            for(int j = 0; j < SIZE; j++){
                matrizC[i][k] += matrizA[i][j] * matrizB[j][k];
            }
        }    
    }
    clock_gettime(CLOCK_MONOTONIC, &end_static);
    tempo_static = diff_time(start_static, end_static);

    memset(matrizC, 0, sizeof(matrizC)); // reseta / zera a matriz C
    printf("--- PROCESSING SCHEDULE (dynamic, %d) ---\n", SIZE);

    clock_gettime(CLOCK_MONOTONIC, &start_dynamic);
    #pragma omp parallel for schedule(dynamic, SIZE)

    for(int i = 0; i < K; i++){
        for(int k = 0; k < K; k++){
            for(int j = 0; j < K; j++){
                matrizC[i][k] += matrizA[i][j] * matrizB[j][k];
            }
        }    
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end_dynamic);

    tempo_dynamic = diff_time(start_dynamic, end_dynamic);

    memset(matrizC, 0, sizeof(matrizC));
    printf("--- PROCESSING SCHEDULE (guided) ---\n");
    clock_gettime(CLOCK_MONOTONIC, &start_guided);
    #pragma omp parallel for schedule(guided)
    
    for(int i = 0; i < K; i++){
        for(int k = 0; k < K; k++){
            for(int j = 0; j < K; j++){
                matrizC[i][k] += matrizA[i][j] * matrizB[j][k];
            }
        }    
    }
    clock_gettime(CLOCK_MONOTONIC, &end_guided);
    tempo_guided = diff_time(start_guided, end_guided);

    memset(matrizC, 0, sizeof(matrizC));
    printf("--- PROCESSING SCHEDULE (auto) ---\n");
    clock_gettime(CLOCK_MONOTONIC, &start_auto);
    #pragma omp parallel for schedule(auto)
    
    for(int i = 0; i < K; i++){
        for(int k = 0; k < K; k++){
            for(int j = 0; j < K; j++){
                matrizC[i][k] += matrizA[i][j] * matrizB[j][k];
            }
        }    
    }
    clock_gettime(CLOCK_MONOTONIC, &end_auto);
    tempo_auto = diff_time(start_auto, end_auto);

    printf("\nTempo static : %.6f segundos\n", tempo_static);
    printf("Tempo dynamic: %.6f segundos\n", tempo_dynamic);
    printf("Tempo guided : %.6f segundos\n", tempo_guided);
    printf("Tempo auto   : %.6f segundos\n", tempo_auto);
    return 0;
}