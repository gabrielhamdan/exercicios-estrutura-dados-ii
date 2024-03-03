#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHUNK_SIZE 1024
#define MAX_STR_LEN 100

int a_qt = 0;
int direito_qt = 0;
int direitos_qt = 0;
int deveres_qt = 0;
char longest_wrd[MAX_STR_LEN] = "";

void count_Aa(char *buff) {
    for(int i = 0; i < strlen(buff); i++)
        if(tolower(buff[i]) == 'a')
            a_qt++;
}

void clean_str(char *str) {
    int last_char = strlen(str) - 1;
    if(!isalpha(str[last_char]))
        str[last_char] = '\0';
}

char * str_to_lower(char * str) {
    for(int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
    
    clean_str(str);

    return str;
}

void update_longest_wrd(char *str) {
    if(strlen(longest_wrd) < strlen(str))
        strncpy(longest_wrd, str, MAX_STR_LEN);
    
    clean_str(longest_wrd);
}

void print_reversed_file(char * fcontent) {
    for(int i = strlen(fcontent) - 1; i >= 0; i--)
        printf("%c", fcontent[i]);
}

void print_output() {
    printf("\n\n");
    printf("A/a: %d\n", a_qt);
    printf("Direito: %d\n", direito_qt);
    printf("Direitos: %d\n", direitos_qt);
    printf("Deveres: %d\n", deveres_qt);
    printf("Palavra mais longa: %s\n", longest_wrd);
}

void process_file_input(FILE *f, char * fcontent) {
    rewind(f);
    char buff[CHUNK_SIZE];
    while(!feof(f)) {
        fgets(buff, CHUNK_SIZE, f);
        count_Aa(buff);
        strncat(fcontent, buff, strlen(buff));
    }

    rewind(f);
    while(!feof(f)) {
        char word_buff[CHUNK_SIZE];
        fscanf(f, "%s", word_buff);
        update_longest_wrd(word_buff);

        if(strcmp(str_to_lower(word_buff), "direito") == 0)
            direito_qt++;
        else if(strcmp(str_to_lower(word_buff), "direitos") == 0)
            direitos_qt++;
        else if(strcmp(str_to_lower(word_buff), "deveres") == 0)
            deveres_qt++;
    }
}

long get_file_size(FILE *f) {
    fseek(f, 0L, SEEK_END);
    return ftell(f);
}

int main(int argc, char **argv) {
    FILE *f = fopen("arquivo_texto.txt", "r");

    if(f == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    long fsize = get_file_size(f);
    char *fcontent = (char *)malloc((fsize + 1) * sizeof(char));
    if(fcontent == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    process_file_input(f, fcontent);

    print_reversed_file(fcontent);

    print_output();

    free(fcontent);
    fclose(f);

    return 0;
}