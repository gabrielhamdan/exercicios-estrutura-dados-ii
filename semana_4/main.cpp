#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "dados.txt"

int * read_file(FILE *);

int main(int argc, char *argv) {
    FILE *f = fopen(FILE_NAME, "r");

    int *f_content = read_file(f);

    return 0;
}

int * read_file(FILE * f) {
    int *f_content;

    return f_content;
}