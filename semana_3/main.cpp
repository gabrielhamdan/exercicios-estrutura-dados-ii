#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
    #define SYS_CLEAR "clear"
#elif defined(_WIN32) || defined(WIN32) 
    #define SYS_CLEAR "cls"
#endif

#define FILE_NAME "arquivo_binario"
#define UNKNOWN_OP "Opcao desconhecida. Tente novamente!\n"
#define MAX_PPL 100
#define MAX_NAME_LEN 50

typedef enum op_code { 
    INSERT = 1, 
    LIST, 
    QUIT
} Op_code;

typedef struct person {
    char name[MAX_NAME_LEN];
    int age;
} Person;

void add_person(Person *, int *);
void list_people(Person *, int);
void load_people(FILE *, Person *, int *);
void print_menu(bool *);
FILE * read_file(Person *, int *);
void save_people(Person *, int);
char * skip_new_line(char *);

int main(int argc, char **argv) {
    int ppl_ct = 0;
    Person people[MAX_PPL];
    FILE *f = read_file(people, &ppl_ct);

    int op;
    bool invalid_op = false;
    while(op != QUIT) {
        print_menu(&invalid_op);
        scanf("%d", &op);
        getchar(); // consome '\n'

        switch(op) {
            case INSERT:
                add_person(people, &ppl_ct);
                break;
            case LIST:
                list_people(people, ppl_ct);
                break;
            case QUIT:
                break;
            default:
                invalid_op = true;
        }
    }

    save_people(people, ppl_ct);

    return 0;
}

/**
 * Adiciona struct Person à lista people se houver espaço.
*/
void add_person(Person *people, int *ppl_ct) {
    if(*ppl_ct == MAX_PPL) {
        printf("Não é possível adicionar mais pessoas à lista.\n");
        getchar();
        return;
    }

    Person person;
    printf("Informe o nome: ");
    fgets(person.name, MAX_NAME_LEN, stdin);
    printf("Informe a idade: ");
    scanf("%d", &person.age);
    getchar(); // consome '\n'

    people[(*ppl_ct)++] = person;
}

/**
 * Itera lista people e imprime na tela nome e idade de pessoas cadastradas.
 * Aguarda input do usuário para retornar ao menu principal.
*/
void list_people(Person *people, int ppl_ct) {
    for(int i = 0; i < ppl_ct; i++)
        printf("-> %s\t\t\t%d\n", skip_new_line(people[i].name), people[i].age);

    getchar();
}

/**
 * Lê arquivo f até o fim e carrega structs Person na lista people.
*/
void load_people(FILE *f, Person *people, int *ppl_ct) {
    while(true) {
        if(fread(&people[(*ppl_ct)], sizeof(Person), 1, f) != 1)
            break;
        (*ppl_ct)++;
    }

    fclose(f);
}

/**
 * Imprime menu principal.
*/
void print_menu(bool *invalid_op) {
    system(SYS_CLEAR);
    printf("[1] - Inserir\n");
    printf("[2] - Listar\n");
    printf("[3] - Sair\n");
    if(*invalid_op) {
        printf(UNKNOWN_OP);
        *invalid_op = false;
    }
    printf("Digite a opcao: ");
}

/**
 * Lê arquivo FILE_NAME. Quando lido com sucesso, chama função load_people.
*/
FILE * read_file(Person *people, int *ppl_ct) {
    FILE *f = fopen(FILE_NAME, "rb");

    if(f)
        load_people(f, people, ppl_ct);

    return f;
}

/**
 * Chamada antes do fim da execução do programa, armazena em FILE_NAME todas as structs Person
 * guardadas na lista people.
*/
void save_people(Person *people, int ppl_ct) {
    FILE *f = fopen(FILE_NAME, "wb");

    if(!f) {
        printf("Não foi possível abrir %s!\n", FILE_NAME);
        exit(EXIT_FAILURE);
    }

    if(ppl_ct > 0)
        fwrite(people, sizeof(Person), ppl_ct, f);

    fclose(f);
}

/**
 * Utilitário para remover o caractere '\\n' da string name.
*/
char * skip_new_line(char *name) {
    for(int i = 0; i < strlen(name); i++)
        if(name[i] == '\n')
            name[i] = '\0';

    return name;
}