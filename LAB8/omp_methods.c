#include<stdio.h>
#include<omp.h>
#include<unistd.h>
#include<time.h>

#define NUM 16

int main(){
    struct timespec start_guide, end_guide, start_auto, end_auto;
    double tempo_guide, tempo_auto;
    printf("--- Testando SCHEDULE (guided) ---\n");
    
    clock_gettime(CLOCK_MONOTONIC, &start_guide);
    #pragma omp parallel for schedule(guided)

    for(int y = 0; y < NUM; y++){
        usleep((y % 4) * 10000);
        printf("Thread %d processing iteration %d\n", omp_get_thread_num(), y);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_guide);

    printf("--- Testando SCHEDULE (auto) ---\n");
    clock_gettime(CLOCK_MONOTONIC, &start_auto);
    #pragma omp parallel for schedule(auto)

    for(int x = 0; x < NUM; x++){
        usleep((x % 4) * 10000);
        printf("Thread %d processing iteration %d\n", omp_get_thread_num(), x);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_auto); 
    tempo_auto = (end_auto.tv_sec - start_auto.tv_sec) + (end_auto.tv_nsec - start_auto.tv_nsec) / 1e9;
    tempo_guide = (end_guide.tv_sec - start_guide.tv_sec) + (end_guide.tv_nsec - start_guide.tv_nsec) / 1e9;

    printf("\n Tempo do guided: %.6f segundos", tempo_guide);
    printf("\n Tempo do auto: %.6f segundos", tempo_auto);
    
    return 0;
}
