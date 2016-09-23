/* ascii2iso8859.c 
Descripcion: Convierte caracteres de ASCII extendido (160-255) a ISO-8859-1
Uso: archivoASCII.txt | ascii2iso8859.exe -standard > salida.txt
Notas:
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUL '\0'
#include "setup.h"
#include "status.h"
#include "validaciones.h"
#include "diccionarios.h"
#define DEBUG

typedef enum{FALSE, TRUE} boolean;

void convertir(short , short [], const char *[]);
void inic_ASCIIcharset(short , short , short *);

int main(int argc, char *argv[])
{
  status_t status;
  short items;
 
  inic_ASCIIcharset(ASCII_DESDE, ASCII_HASTA, ASCIIcharset);

  /********VALIDACIONES*******/  
  status = validar_nitems(ASCIIcharset, ISOcharset, &items);
  if (status != OK)
    return status;

  status = validar_argc(argc, ARGS);
  if (status != OK)
    return status;

  status = validar_argv(argv, ARGC1, ARGV1);
  if (status != OK)
    return status;
  /**************************/

  convertir(items, ASCIIcharset, ISOcharset);

  return EXIT_SUCCESS;
}

void convertir(short items, short arrCharset1[], const char *parrCharset2[])
{
  boolean Traducido;
  short i, c;
  
  while ((c = getchar())!=EOF)
  {
    Traducido = FALSE;
    for (i = 0; i < items; i++)
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

void inic_ASCIIcharset(short inicio, short fin, short *p)
{
  short i;
  for (i = 0; inicio<=fin; i++, inicio++)
    p[i] = inicio;

  /*agrego caracteres que no están ordenados*/
  p[i++] = 36;
  p[i++] = 38;
  p[i++] = 60;
  p[i++] = 62;
}
