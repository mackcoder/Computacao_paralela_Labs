#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NUM_SONS 4
int main(){
    pid_t pid;

    printf("Processo Pai/Father: %d\n", getpid());

    for(int t = 0; t < NUM_SONS; t++){
        pid =fork();

        if(pid < 0){
            fprintf(stderr, "ERROR DETECTED\n");
            return 1;

        } else if(pid == 0){
            // Son 1
            printf("Filho criado: PID -> %d. Meu pai = T%d\n", getpid(), getppid());
            exit(0);

        }
    }
    printf("==========================================================\n");
    printf("PAI/FATHER esperando a finalização dos processos filhos...\n");
    for(int p = 0; p < NUM_SONS; p++){
        wait(NULL);
    }
    printf("ALL PROCESSES FINALIZED WITH SUCCESS");
    return 0;
}