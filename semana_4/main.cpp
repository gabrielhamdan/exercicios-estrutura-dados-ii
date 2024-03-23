#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "dados.txt"
#define CHUNK_SIZE 16
#define SEARCH_VALUES_LEN 6
#define SEARCH_VALUES (int[SEARCH_VALUES_LEN]) {7341488, 85, 265654, 732765, 8313596, 45744}

int * read_file(FILE *, int *);
int do_bin_search(int *, int);
int do_linear_search(int *, int);

int main(int argc, char **argv) {
    FILE *f = fopen(FILE_NAME, "r");

    int f_content_len = 0;
    int *f_content = read_file(f, &f_content_len);

    int linear_search_ct = do_linear_search(f_content, f_content_len);
    int bin_search_ct = do_bin_search(f_content, f_content_len);
    
    printf("Total de acessos de busca sequencial: %d\n", linear_search_ct);
    printf("Total de acessos de busca binária: %d\n", bin_search_ct);
    printf("A busca binária é %dx mais rápida que a busca sequencial.\n", linear_search_ct / bin_search_ct);

    free(f_content);
    fclose(f);

    return 0;
}

int do_bin_search(int *search_list, int len) {
    int mem_access_ct = 1;
    int last_access;

    for(int i = 0; i < SEARCH_VALUES_LEN; i++) {
        int local_mem_access_ct = 1;
        int first_half = -1, second_half = len;
        while(first_half < second_half - 1) {
            int mid = (first_half + second_half) / 2;

            if(search_list[mid] == SEARCH_VALUES[i]) {
                last_access = mid;
                printf(" > (BUSCA BINÁRIA) Valor %d encontrado em %d acessos.\n", search_list[mid], local_mem_access_ct);
                break;
            } else if(search_list[mid] < SEARCH_VALUES[i])
                first_half = mid;
            else
                second_half = mid;
            
            local_mem_access_ct++;
            mem_access_ct++;
            last_access = mid;
        }

        if(search_list[last_access] != SEARCH_VALUES[i])
            printf(" >>> (BUSCA BINÁRIA) Valor %d NÃO encontrado após %d acessos.\n", SEARCH_VALUES[i], local_mem_access_ct);
    }

    return mem_access_ct;
}

int do_linear_search(int *search_list, int len) {
    int mem_access_ct = 1;
    int last_access;
    
    for(int i = 0; i < SEARCH_VALUES_LEN; i++) {
        int local_mem_access_ct = 1;
        for(int j = 0; j < len; j++) {
            if(SEARCH_VALUES[i] == search_list[j]) {
                last_access = j;
                printf(" > (BUSCA SEQUENCIAL) Valor %d encontrado em %d acessos.\n", search_list[j], local_mem_access_ct);
                break;
            }

            local_mem_access_ct++;
            mem_access_ct++;
            last_access = j;
        }

        if(search_list[last_access] != SEARCH_VALUES[i])
            printf(" >>> (BUSCA SEQUENCIAL) Valor %d NÃO encontrado após %d acessos.\n", SEARCH_VALUES[i], local_mem_access_ct);
    }

    return mem_access_ct;
}

int * read_file(FILE *f, int *f_content_len) {
    int max_len = 1024;
    int *f_content = (int *)malloc(sizeof(int) * max_len);

    char buff[CHUNK_SIZE];
    int item;

    while(!feof(f)) {
        fgets(buff, CHUNK_SIZE, f);
        item = atoi(buff);

        if((*f_content_len) == max_len) {
            max_len *= 2;
            f_content = (int *)realloc(f_content, max_len * sizeof(int));
        }

        f_content[(*f_content_len)++] = item;
    }

    return f_content;
}