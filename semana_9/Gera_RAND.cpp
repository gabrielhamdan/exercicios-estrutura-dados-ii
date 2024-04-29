#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>

#define SIZE 1000000

main(){
long i;
unsigned int ex;

FILE *txt;

if((txt = fopen("rand.txt", "w")) == NULL)    {
        printf("Erro ao abrir arquivo");
    }
 else {
       
	  	//Definindo a Semente Inicial do Gerador Aleat�rio
		ex = ((unsigned) time(NULL)) ; 
		
		srand(ex) ; 
		
	     i = 0;
         while(i < SIZE)
         {
               int c = rand() % RAND_MAX;
               fprintf(txt, "%d\n",c);
               ++i;
          }
		fclose(txt);
      }
}

