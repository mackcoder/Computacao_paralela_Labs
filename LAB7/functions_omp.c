#include <stdio.h>
#include <omp.h>

int main(){
    printf(" --- Fora da regiao paralela - - -\n");
    printf("Numero de processadores disponiveis: %d\n", omp_get_num_procs());
    printf("Número de threads(antes de definir): %d \n", omp_get_num_threads());

    omp_set_num_threads(4);

    #pragma omp parallel
    {

        #pragma omp_master
        {
            printf("\n --- Inner Parallel Region ---\n");
            printf("Número de threads na equipe: %d \n", omp_get_num_threads());
        }
        // Garante que todas as threads esperem a master imprimir antes de continuar
        #pragma omp_barrier
        // Cada thread imprime seu proprio ID
        // Usamos ’critical ’ para evitar que as saidas se misturem no console

        #pragma omp_critical
        {
            printf("THREAD DETECTED -> NUM: %d of %d threads.\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }

    printf ("\n- - - Fora da regiao paralela de novo - - -\n");
    printf (" Numero de threads : %d\n", omp_get_num_threads());

    return 0;
}