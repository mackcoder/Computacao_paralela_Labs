#include<stdio.h>
#include<omp.h>
#include<unistd.h>

#define K 1024
#define SIZE 4

int main(){
    double matrizA[K][K], matrizB[K][K], matrizC[K][K];
    printf("--- MATRIZ MULTIPLICACAO ---\n");

    printf("Modo Static:\n");
    #pragma omp parallel for schedule(static, SIZE)

    for(int x = 0; x < SIZE; x++){
        for(int y = 0; y < SIZE; y++){
            matrizA[x][y] = 1.0;
            matrizB[x][y] = 2.0;
            matrizC[x][y] = 0.0;  
        }
            for(int z = 0; z < SIZE; z++){
                
            }
    }

    printf("--- Testando SCHEDULE (dynamic, %d) ---\n", SIZE);

    #pragma omp parallel for schedule(dynamic, SIZE)

    for(int x = 0; x < SIZE; x++){
        usleep((x % 4) * 10000);
        printf("Thread %d processing iteration %d\n", omp_get_thread_num(), x);
    }
    return 0;
}