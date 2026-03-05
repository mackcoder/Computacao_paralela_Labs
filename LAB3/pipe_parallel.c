#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

// Main:
int main(){
    // Criando as pipes(com os descritores)
    int pipefd[2];
    char buffer[100];

    if(pipe(pipefd) == -1){
        perror("Pipe");
        exit(EXIT_FAILURE);
    }

    // Criando filho:
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        close(pipefd[0]); // Não irá ler(read)

        const char* mensagem = "Message from SON";
        printf("\nFILHO SENDING MESSAGE...\n");

        write(pipefd[1], mensagem, strlen(mensagem + 1));
        close(pipefd[1]); // Fecha ponta de escrita
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]); // Não irá escrever
        printf("\nPAI: Awaiting message");
        read(pipefd[0], buffer, sizeof(buffer));
        printf("\nPAI -> Vox Message received --> %s", buffer);
        close(pipefd[0]);
        wait(NULL);
    }
    return 0;
}