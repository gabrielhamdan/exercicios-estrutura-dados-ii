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

void counting_sort(int *array, int size)
{
    int i, min, max;
    int j=0; 
    min = max = array[0];

    clock_t t1 = clock();

    printf("iniciando count_sort\n");
    for(i = 1; i < size;  i++) 
    {
        if (array[i] < min)
        min = array[i];
        else if (array[i] > max)
        max = array[i];
    }

    int range = max - min + 1;
    int *count = (int *) malloc(range * sizeof(int));

    for(i = 0; i < range; i++)
        count[i] = 0;
    
    for(i = 0; i < size; i++)
        count[array[i] - min]++;
    
    int indice;
    indice=0; 
    
    for(i = min; i <= max; i++)
        for(j = 0; j < count[ i - min ]; j++)
        {
            array[indice] = i;
            indice++;
        }

    free(count);

    clock_t t2 = clock();
    double time_spent = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("tempo final de execução: %f\n", time_spent);
}

int main ()
{
    load_data();
    int i, j = 0,  aux;
    counting_sort(v,n);

    return 0;
}