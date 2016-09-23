/* ascii2iso8859.c 
Descripcion: Convierte caracteres de ASCII extendido (160-255) a ISO-8859-1
Uso: archivoASCII.txt | ascii2iso8859.exe -standard > salida.txt
Notas: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setup.h"
#include "status.h"
#include "diccionarios.h"
#define DEBUG

typedef enum{FALSE, TRUE} boolean;
/***************PROTOTIPOS******************/
void convertir(const char [], const char *[]);
status_t validar_argc(short , short);
status_t validar_argv(char *[], short, char *);

int main(int argc, char *argv[])
{
  status_t status;

  /********VALIDACIONES*******/  
  status = validar_argc(argc, ARGS);
  if (status != OK)
    return status;

  status = validar_argv(argv, ARGC1, ARGV1);
  if (status != OK)
    return status;
  /**************************/

  convertir(ASCIIcharset, ISOcharset);

  return EXIT_SUCCESS;
}

void convertir(const char arrCharset1[], const char *parrCharset2[])
{
  boolean Traducido;
  short i, c;
  while ((c = getchar())!=EOF)
  {
    Traducido = FALSE;
    for (i = 0; i < ITEMS; i++)
    {
      if (c == arrCharset1[i])
      {
        Traducido = TRUE;
        printf("%s", parrCharset2[i]);
        #ifdef DEBUG
	  fprintf(stderr, "traducido c = %c | %d----->%s\n", c, c, parrCharset2[i]);
	#endif
        break;
      }
    }
    if (Traducido == FALSE) putchar(c);
  }
}
