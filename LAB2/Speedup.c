#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESSES 4
#define VECTOR_SIZE 200000000

// Função que roda sequencialmente o vetor:
void sequencial(double* v, int startseq, int endseq){
    for(int t = startseq; t < endseq; t++){
        v[t] = sin(v[t]) * cos(v[t]) + sqrt(v[t]);
    }
}

// Função que roda paralelamente o vetor:
void paralelismo(double* v, int start, int end){
    for(int t = start; t < end; t++){
        v[t] = sin(v[t]) * cos(v[t]) + sqrt(v[t]);
    }
}

int main(){
    double* vetor = (double*)malloc(VECTOR_SIZE * sizeof(double));
    double vector_piece = VECTOR_SIZE / NUM_PROCESSES;
    for(int y = 0; y < VECTOR_SIZE; y++){
        vetor[y] = (double)y;
    }

    struct timespec _paral_start, paral_end, seq_start, seq_end;
    clock_gettime(CLOCK_MONOTONIC , &_paral_start);
    for(int x = 0; x < NUM_PROCESSES - 1; x++){
        pid_t pid = fork();

        if(pid < 0){
            fprintf(stderr, "Fork falhou\n");
            return 1;

        } else if(pid == 0){
            int comeco_ind = x * vector_piece;
            int end_ind = (x == NUM_PROCESSES - 1) ? VECTOR_SIZE : (x + 1) * vector_piece;
            paralelismo(vetor, comeco_ind, end_ind);
            exit(0);
        }
    }
    printf("\n Pai rodando\n");
    for(int i = 0; i < NUM_PROCESSES; i++){
        wait(NULL); 
    }
    clock_gettime(CLOCK_MONOTONIC, &paral_end); // Acaba a medição de tempo do metodo paralelo

    clock_gettime(CLOCK_MONOTONIC, &seq_start);

    sequencial(vetor, 0, VECTOR_SIZE);

    clock_gettime(CLOCK_MONOTONIC, &seq_end); // Acaba a medição de tempo do metodo sequencial

    double tempo_exec_paralelo = (paral_end.tv_sec - _paral_start.tv_sec) + (paral_end.tv_nsec - _paral_start.tv_nsec) / 1e9;
    double tempo_exec_seq = (seq_end.tv_sec - seq_start.tv_sec) + (seq_end.tv_nsec - seq_start.tv_nsec) / 1e9;
    float speedup = tempo_exec_seq / tempo_exec_paralelo;

    printf("\nO speedup foi de: %f .", speedup);
    free(vetor);
    return 0;
}
