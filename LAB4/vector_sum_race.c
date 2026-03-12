#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define THREADS 4
#define TAM 100000000
long long vector[TAM];

int total = 10;
long long global_soma = 0;
long pedaco = TAM / THREADS;

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
    long long local_soma = 0;
    long id_thread = (long)arg;
    printf("\nThread %ld iniciando o trabalho\n", id_thread);

    long comeco = id_thread * THREADS;
    long end = (id_thread == THREADS - 1) ? TAM : (id_thread + 1) * pedaco;

    for(long n = comeco; n <= end; n++){
        local_soma += vector[n];
    }
    global_soma += local_soma;

    return NULL;
}


int main(){

    for(int i = 0; i < TAM; i++){
        vector[i] = 1;
    }

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
    // Operação de soma:

    for(int t = 0; t < THREADS; t++){        
        pthread_join(threads[t], NULL); // wait para todos terminarem
    }

    long long esperado = (long long)TAM;
    printf("\nRESULTADOS\n");
    printf("Valor final do contador: %lld\n", global_soma);
    printf("Valor esperado: %lld\n", esperado);

    if(global_soma != esperado){
        printf("Diferença: %lld. CONDIÇÃO DE CORRIDA DETECTED\n", esperado - global_soma);

    } else {
        printf("Resultado está correto.\n");

    }
    return 0;
}


