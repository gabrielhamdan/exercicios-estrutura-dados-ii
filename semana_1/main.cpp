#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 1024
#define MAX_WRD_LEN 100

void clean_str(char *);
void count_Aa(char *);
void count_wrds(char const *);
long get_file_size(FILE *);
void print_output();
void print_reversed_file(char *);
void process_file_input(FILE *, char *);
char * str_to_lower(char *);
void update_longest_wrd(char *);

int a_qt = 0;
int direito_qt = 0;
int direitos_qt = 0;
int deveres_qt = 0;
char longest_wrd[MAX_WRD_LEN] = "";

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

/**
 * Limpa caracteres não alfabéticos (e. g., ',', '.', '/', etc.).
*/
void clean_str(char *str) {
    int last_char = strlen(str) - 1;
    if(!isalpha(str[last_char]))
        str[last_char] = '\0';
}

/**
 * Itera buffer e incrementa a_qt se caractere for igual a 'A' ou 'a'.
*/
void count_Aa(char *buff) {
    for(int i = 0; i < strlen(buff); i++)
        if(tolower(buff[i]) == 'a')
            a_qt++;
}

/**
 * Itera cada palavra (i. e., cada string separada por ' ') e compara com "direito", "direitos", "deveres", 
 * incrementando, respectivamente, direito_qt, direitos_qt e deveres_qt quando a comparação retorna 0.
*/
void count_wrds(char const *str) {
    char buff[CHUNK_SIZE];
    strncpy(buff, str, CHUNK_SIZE);

    char word_buff[MAX_WRD_LEN];
    char splitc[] = " ";
    char *spt = strtok(buff, splitc);

    while (spt) {
        strncpy(word_buff, spt, MAX_WRD_LEN);
        update_longest_wrd(word_buff);

        if(strcmp(str_to_lower(word_buff), "direito") == 0)
            direito_qt++;
        else if(strcmp(str_to_lower(word_buff), "direitos") == 0)
            direitos_qt++;
        else if(strcmp(str_to_lower(word_buff), "deveres") == 0)
            deveres_qt++;

        spt = strtok(NULL, splitc);
    }
}

/**
 * Percorre arquivo até o fim e retorna sua posição a fim de determinar o tamanho do arquivo em questão.
*/
long get_file_size(FILE *f) {
    fseek(f, 0L, SEEK_END);
    return ftell(f);
}

/**
 * Imprime no console os elementos definidos no enunciado do exerício.
*/
void print_output() {
    printf("\n\n");
    printf("A/a: %d\n", a_qt);
    printf("Direito: %d\n", direito_qt);
    printf("Direitos: %d\n", direitos_qt);
    printf("Deveres: %d\n", deveres_qt);
    printf("Palavra mais longa: %s\n", longest_wrd);
}

/**
 * Imprime no console o conteúdo do arquivo de trás para frente.
*/
void print_reversed_file(char *fcontent) {
    for(int i = strlen(fcontent) - 1; i >= 0; i--)
        printf("%c", fcontent[i]);
}

/**
 * Percorre o arquivo e chama as funções de contagem de palavras/caracteres, guardando em fcontent
 * cada uma das linhas lidas do arquivo para, posteriormente, utilizar o conteúdo da variável em
 * print_reversed_file.
*/
void process_file_input(FILE *f, char *fcontent) {
    rewind(f);
    char buff[CHUNK_SIZE];
    while(!feof(f)) {
        fgets(buff, CHUNK_SIZE, f);
        count_Aa(buff);
        count_wrds(buff);
        strncat(fcontent, buff, strlen(buff));
    }
}

/**
 * Utilitário para converter caracteres de string para minúsculos a fim de
 * facilitar a comparação entre strings.
*/
char * str_to_lower(char * str) {
    for(int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);

    clean_str(str);

    return str;
}

/**
 * Atualiza a variável longest_wrd sempre que str for mais longa que a última ocorrência.
*/
void update_longest_wrd(char *str) {
    if(strlen(longest_wrd) < strlen(str))
        strncpy(longest_wrd, str, MAX_WRD_LEN);

    clean_str(longest_wrd);
}