#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

int v[SIZE], n=SIZE;

void load_data() {
    FILE *f = fopen("lista_semi_ordenada", "r");
    
    fread(v, sizeof(int), SIZE, f);
    
    printf("finalizou execução de load_data\n");
    fclose(f);
}

int main ()  {
    load_data();

    clock_t t1 = clock();

    int i, j, chave;
    int c = 0; 

    printf("iniciando insertion_sort\n");
    for(j=1; j<n; j++) 
    {
        chave = v[j];
        i = j-1;
        while(i >= 0 && v[i] > chave) {
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = chave;
    }

    clock_t t2 = clock();
    double time_spent = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("tempo final de execução: %f\n", time_spent);

    return 0;
}