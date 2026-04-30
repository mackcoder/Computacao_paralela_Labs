#include<stdio.h>
#include<omp.h>
#include<unistd.h>

#define NUM 16
#define SIZE 2    //testar com 1

int main(){
    printf("--- Testando SCHEDULE (static, %d) ---\n", SIZE);

    #pragma omp parallel for schedule(static, SIZE)

    for(int y = 0; y < NUM; y++){
        usleep((y % 4) * 10000);
        printf("Thread %d processing iteration %d\n", omp_get_thread_num(), y);
    }

    printf("--- Testando SCHEDULE (dynamic, %d) ---\n", SIZE);

    #pragma omp parallel for schedule(dynamic, SIZE)

    for(int x = 0; x < NUM; x++){
        usleep((x % 4) * 10000);
        printf("Thread %d processing iteration %d\n", omp_get_thread_num(), x);
    }
    return 0;
}
