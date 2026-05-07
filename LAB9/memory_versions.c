#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N_DEFAULT 1000
#define BLOCK_SIZE 32

// Vars Globais
double **A,**B,**C;

// Funções de alocação:
double** allocate_matrix(Int N){
    double** matriz = (double**)malloc(N * sizeof(double*));

    for(int t = 0; t < N; t++){
        matriz[t] = (double)malloc(N * sizeof(double));
    }
    return matriz;
}

void init_m(int N){
    A = allocate_matrix(N);
    B = allocate_matrix(N);
    C = allocate_matrix(N);

    // Preencher com nums randomizados:
    srand(time(NULL));
    for(int x = 0; x < N x++){
        for(y = 0; y < N; y++){
            A[x][y] = (double)rand() / RAND_MAX;
            B[x][y] = (double)rand() / RAND_MAX;
            C[x][y] = 0.0;
        }
    }
}

// Versao IJK (Péssimo)
void mm_ijk_serial(int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j]; 
            }
        }
    }
}
// Versao IKJ (BOA)
void mm_ikj_serial(int N){
    for(int i = 0; i < N; i++){
        for(int k = 0; k < N; k++){
            for(int j = 0; j < N; j++){
                C[i][j] += A[i][k] * B[k][j]; 
            }
        }
    }
}
// Versao IKJ Paralela:
void mm_ikj_parallel(int N){
    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j]; 
            }
        }
    }
}

// Versao bloqueada
void mm_ijk_serial(int N){
    int i, j, k, i_block, j_block, k_block;

    #pragma omp parallel for private(j, k, i_block, j_block, k_block)
    for(int i = 0; i < N; i+= BLOCK_SIZE){
        for(int k = 0; k < N; k+= BLOCK_SIZE){
            for(int j = 0; j < N; j+= BLOCK_SIZE){
                
                for(i_block = i; i_block < i + BLOCK_SIZE && i_block < N; i_block++){
                    for(k_block = k; k_block < k + BLOCK_SIZE && k_block < N; k_block++){
                        for(j_block = j; j_block < j + BLOCK_SIZE && j_block < N; j_blovk++){
                            C[i_block][j_block] += A[i_block][k_block] * B[k_block][j_block];
                        }
                    }
                }
            }
        }
    }
}

// Main:

int main(int argc, char** argv){
    int N = (argc > 1) ? atoi(argv[1]: N_DEFAULT);

    init_m(N);

    double start_time = omp_get_wtime();

    #if defined(SERAIL_IJK)
        printf("Executando SERIAL IJK (N = %d)\n", N);
        mm_ijk_serial(N);
    #elif defined(SERIAL_IKJ)
        printf("Executando SERIAL IKJ (N = %d)\n", N);
    #elif defined(PARALLEL_IKJ)
        printf("Executando Paralelo IKJ (N = %d, Threads = %d)\n", N, omp_get_max_threads());
    #elif defined(PARALLEL_BLOCKED)
        printf("Executando Paralelo Blocado (N = %d, BS = %d, Threads = %d)\n", N, BLOCK_SIZE, omp_get_max_threads());
        mm_blocked_parallel(N);
    #else
        #error "Nenhuma versão de multiplicação definida na Compilation"
    #endif

    double end_time = omp_get_wtime();
    printf("Tempo total: %f segundos\n", end_time - start_time);

    free(A);
    free(B);
    free(C);

    return 0;
}
