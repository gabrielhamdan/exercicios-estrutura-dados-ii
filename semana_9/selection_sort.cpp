#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>

#define SIZE 100000

int num[SIZE], tam=SIZE;

void load_data() {
    FILE *f = fopen("lista_semi_ordenada", "r");
    
    fread(num, sizeof(int), SIZE, f);
    
    printf("finalizou execução de load_data\n");
    fclose(f);
}

int main () {
    load_data();

    clock_t t1 = clock();

    int i, j, min;
    printf("iniciando selection_sort\n");
    for (i = 0; i < (tam-1); i++) {
        min = i;
    
        for (j = (i+1); j < tam; j++) {
            if(num[j] < num[min]) {
                min = j;
            }
        }
        if (i != min) {
            int swap = num[i];
            num[i] = num[min];
            num[min] = swap;
        }
    }

    clock_t t2 = clock();
    double time_spent = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("tempo final de execução: %f\n", time_spent);

    return 0;
}