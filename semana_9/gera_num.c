#include <stdlib.h>
#include <stdio.h>

#define SIZE 100000

int main() {
    FILE *f = fopen("lista_semi_ordenada", "wb");

    for(int i = 0; i < SIZE; i++)
        fwrite(&i, sizeof(int), 1, f);
    
    fclose(f);

    f = fopen("lista_ordenada_rev", "wb");

    for(int i = SIZE; i > 0; i--)
        fwrite(&i, sizeof(int), 1, f);
    
    fclose(f);

    return 0;
}