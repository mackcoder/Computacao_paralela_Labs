#include<stdio.h>
#include<omp.h>
#include<unistd.h>

#define NUM 16
#define SIZE 2

int main(){
    printf("--- Testando SCHEDULE (guided) ---\n");

    #pragma omp parallel for schedule(guided)

    for(int y = 0; y < NUM; y++){
        usleep((y % 4) * 10000);
        printf("Thread %d processing iteration %d\n", omp_get_thread_num(), y);
    }

    printf("--- Testando SCHEDULE (auto) ---\n");

    #pragma omp parallel for schedule(auto)

    for(int x = 0; x < NUM; x++){
        usleep((x % 4) * 10000);
        printf("Thread %d processing iteration %d\n", omp_get_thread_num(), x);
    }
    return 0;
}
