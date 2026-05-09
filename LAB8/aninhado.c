#include<stdio.h>
#include<time.h>
#include<omp.h>

#define N 100000

int main(){
    #pragma omp_set_nested(1)

    #pragma omp parallel for num_threads(2)
    for(int a = 0; a < N; a++){
        #pragma omp parallel for num_threads(4)
        for(int b = 0; b < N; b++){
            printf("\nID: %d -- LEVEL LOCATED: %d", omp_get_thread_num, omp_get_level());
        }
    }
}