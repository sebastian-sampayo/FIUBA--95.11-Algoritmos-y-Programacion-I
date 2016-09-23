/* 
    Algoritmos y Programación I - 75.02 - Curso Ing. Cardozo
    Material de clase
    Archivo:    ejemplo43.c
    Descripcion: Conversion de caracteres ASCII a ISO8859-1

    !!!!!!!!!!!!!!!!!! Debe usarse una funcion para validar los argumentos en linea de ordenes, por ejemplo:
                status_t validate_arguments(int, char * []);

*/
#include <stdio.h>

#define MAX_ITEM 100

typedef enum{FALSE,TRUE} boolean;

char    NormalCharSet[MAX_ITEM]={' ','‚','¡','¢','£',''};
char    *HTMLCharSet[]={"&aacute;","&eacute;","&iacute;","&oacute;","&uacute;","&ntilde;"};


int main(int argc,char *argv[])
{
    size_t     Items=6;
    size_t     i,j;
    boolean Traducido;

    
    if(argc>2){
       fprintf(stderr,"%s\n","Demasiados argumentos.");
       fprintf(stderr,"%s\n","Uso: %s <texto original>",argv[0]);
       return 1;
    }
    if(argc<1){
       fprintf(stderr,"%s\n","Argumentos insuficientes.");
       fprintf(stderr,"%s\n","Uso: %s <texto original>",argv[0]);
       return 0;
    }

    /* en argv[1] tengo la cadena a traducir */
    printf("%s%s\n","Cadena original: ",argv[1]);

    printf("%s","Cadena traducida: ");
    for(i=0;argv[1][i]!='\0';i++){
        Traducido = FALSE;
        for(j=0;j<Items;j++){
            if(argv[1][i]==NormalCharSet[j]){
               Traducido = TRUE;
	       printf("%s",HTMLCharSet[j]);
	       break;
            }
        }
        if(Traducido == FALSE) 
            putchar(argv[1][i]);

    }
    return 0;
}











