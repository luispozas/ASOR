#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    pid_t pid = getpid();
    int scheduler = sched_getscheduler(pid);

    
     /* Consultar "man sched" para determinar el valor de retorno. */
    printf("* La politica de planificacion (pid = %i):\n  ", pid);
    switch(scheduler){
        case SCHED_RR: 
            printf("Round-robin | SCHED_RR = %i\n", SCHED_RR); break;
        case SCHED_OTHER: 
            printf("Default Linux time-sharing | SCHED_OTHER = %i\n", SCHED_OTHER); break;
        case SCHED_FIFO: 
            printf("FIFO  | SCHED_FIFO = %i\n", SCHED_FIFO); break;
        default: 
            printf("Error (No se ha encontrado)\n"); break;
    }

    /* Prioridad */
    struct sched_param p;
    sched_getparam(pid, &p);
    printf("\n* La prioridad es: %i\n\n", p.sched_priority);

    /* Valores máximo y mínimo de la prioridad para la política de planificación */
    int min = sched_get_priority_min(scheduler);
    int max = sched_get_priority_max(scheduler);
    printf("* El valor MINIMO de la prioridad es: %i\n", min);
    printf("* El valor MAXIMO de la prioridad es: %i\n", max);

    return 0;
}
