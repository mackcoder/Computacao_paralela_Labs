#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

#define PROCESSES 4
#define TAM_VETOR 1000

int somador(int *v, int start, int end){
    int partioned_sum=0;
    for(int i = start; i < end; i++){
        partioned_sum += v[i];
    }
    return partioned_sum;
}

void loading_bar(int passo, int total){
    int width = 20;
    int preenche = (passo * width) / total;
    
    printf("\r[");
    for(int a = 0; a < preenche; a++) printf("█");
    for(int b = preenche; b < width; b++) printf(" ");
    printf("] %d%%", (passo * 100)/total);
    fflush(stdout);
}

// Main:
int main(){
    // Criando as pipes(com os descritores)
    int pipers[PROCESSES][2];
    int vector[TAM_VETOR];
    double soma_total;
    int vector_piece = TAM_VETOR / PROCESSES;
    int total = 10;

    for(int b = 0; b < TAM_VETOR; b++){
        vector[b] = 1;
    }

    // Criando filho:
    for(int y = 0; y < PROCESSES; y++){
        if(pipe(pipers[y]) == -1){
            perror("Pipe");
            exit(EXIT_FAILURE);
        }
        pid_t pid = fork();

        if(pid < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            close(pipers[y][0]); // Não irá ler(read)

            int comeco_ind = y * vector_piece;
            int end_ind = (y == PROCESSES - 1) ? TAM_VETOR : (y + 1) * vector_piece;
            printf("\nFILHO CALCULALTING SUM...\n");
            double soma_local = somador(vector, comeco_ind, end_ind); // chama funcao
            write(pipers[y][1], &soma_local, sizeof(double));
            close(pipers[y][1]); // Fecha ponta de escrita
            exit(EXIT_FAILURE);
        }
        for(int t = 0; t < PROCESSES; t++){
            close(pipers[t][1]); // Não irá escrever
            // Laço pai:
            double soma_local;
            printf("\nPAI: Awaiting sum...");
            /*
            for(int x = 0; x <= total; x++){
                loading_bar(x, total);
                usleep(10000);
            }
            */
            read(pipers[t][0], &soma_local, sizeof(double));
            soma_total += soma_local;
            close(pipers[t][0]);
            wait(NULL);
        }    
    }
    for(int x = 0; x <= total; x++){
        loading_bar(x, total);
        usleep(300000);
    }
    printf("\nPAI -> Vox Sum received --> %.2f", soma_total);
    
    return 0;
}