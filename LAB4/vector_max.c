#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define TAM 10000000
#define NUM_T 4

long long vector[TAM];
long piece = TAM / NUM_T;
short int total = 10;

void insert_nums(){
    for(int piper = 0; piper < TAM; piper++){
        long random_num = rand();
        vector[piper] = random_num;
    }
}

void* max_finder(void* arg){
    long id_thread = (long)arg;

    long comeco = piece * id_thread;
    long end = (id_thread == NUM_T - 1) ? TAM: (id_thread + 1) * piece;

    long maior_num = vector[comeco];

    for(long idx = comeco; idx <= end; idx++){
        if(vector[idx] > maior_num){
            maior_num = vector[idx];
        }
    }

    return (void*)maior_num;

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

int main(){
    insert_nums();
    pthread_t thread[NUM_T];
    void* return_value_ptr = NULL;
    long maior_global = vector[0];

    

    for(int x = 0; x < NUM_T; x++){
        if(pthread_create(&thread[x], NULL, max_finder, (void*)x) != 0){
            perror("ERROR DETECTED\n");
            exit(EXIT_FAILURE);
        }

    }

    for(int y = 0; y < NUM_T; y++){
        // Conversão do num encontrado:
        pthread_join(thread[y], &return_value_ptr);
        long resultado = (long)return_value_ptr;
        if(resultado > maior_global){
            maior_global = resultado;
        }
    }
    for(int x = 0; x <= total; x++){
        loading_bar(x, total);
        usleep(100000);
    }
    
   
   printf("\n Maior número encontrado: %ld", maior_global);
}


