#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define THREADS 8
#define INCREMENT 1000000

int total = 10;
long long cont = 0;

void loading_bar(int passo, int total){
    int width = 20;
    int preenche = (passo * width) / total;
    
    printf("\r[");
    for(int a = 0; a < preenche; a++) printf("█");
    for(int b = preenche; b < width; b++) printf(" ");
    printf("] %d%%", (passo * 100)/total);
    fflush(stdout);
}

void* thread_func(void* arg){
    long id_thread = (long)arg;
    printf("\nThread %ld iniciando o trabalho\n");

    for(int y = 0; y < INCREMENT; y++){
        cont++;
    }
    return NULL;
}


int main(){
    pthread_t threads[THREADS];

    for(long x = 0; x < THREADS; x++){
        if(pthread_create(&threads[x], NULL, thread_func, (void*)x) != 0){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    for(int x = 0; x <= total; x++){
        loading_bar(x, total);
        usleep(200000);
    }

    for(int t = 0; t < THREADS; t++){
        pthread_join(threads[t], NULL); // wait para todos terminarem
    }

    long long esperado = (long long)THREADS * INCREMENT;
    printf("\nRESULTADOS\n");
    printf("Valor final do contador: %lld\n", cont);
    printf("Valor esperado: %lld\n", esperado);

    if(cont != esperado){
        printf("Diferença: %lld. CONDIÇÃO DE CORRIDA DETECTED\n", esperado - cont);

    } else {
        printf("Resultado está correto.\n");

    }
    return 0;
}


