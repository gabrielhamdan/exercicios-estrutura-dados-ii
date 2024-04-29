#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>

#define SIZE 100000

int v[SIZE], n=SIZE;

void load_data() {
    FILE *f = fopen("lista_semi_ordenada", "r");
    
    fread(v, sizeof(int), SIZE, f);
    
    printf("finalizou execução de load_data\n");
    fclose(f);
}

int main() {
    load_data();

    clock_t t1 = clock();

    int i, j = 0,  aux;

    bool swapped = false;
    printf("iniciando bubble_sort com flag\n");
    while (j < n)
    {
        swapped = false;
        for(i = 0; i < n-1; i++)
            if(v[i] > v[i + 1])
            {
                aux=v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                swapped = true;
            }

        if(!swapped) break;
        j++;
    }

    clock_t t2 = clock();
    double time_spent = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("tempo final de execução: %f\n", time_spent);
}