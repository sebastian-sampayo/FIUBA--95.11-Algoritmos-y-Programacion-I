/* Funciones de lectura de caracteres */
#include <stdio.h>
#include "setup.h"
#include "typedefs.h"

extern const char dictionary_b64[];
extern status_t status;

/*************PROTOTIPOS***********
size_t readXchars(char [], size_t );
status_t check_reading (const char [], const char [], short );
*/

/* size_t readXchars(char buffer[], size_t x)  
   Lee x caracteres por stdin y devuelve por nombre la cantidad que efectivamente guardo en el buffer*/
size_t readXchars(char buffer[], size_t x)
{
  int c, b;
  size_t i;
  #ifdef DEBUG
    fprintf(stderr,"Entro a readXchars\n");
  #endif

  for (i=0; i<x; i++)
  {
    if ((c = getchar())==EOF) break;
    /*Esta parte del código lee un caracter más y lo guarda en b y lo compara con EOF.
      De ser cierto, indica que c era un \n inmediato anterior al EOF, pero que no 
      es parte del texto. Por lo tanto se lo devuelve a stdin y sale del ciclo*/
    if ((b = getchar())==EOF && c=='\n')
    {
      ungetc(b, stdin);
      break;
    }
    ungetc(b, stdin); /* En el caso de que el siguiente caracter (b) no fuera EOF,
                         se lo devuelve a stdin para ser leido por getchar posteriormente*/
    buffer[i] = c;
    #ifdef DEBUG
      fprintf(stderr, "i = %d | c = %c (char)\t %d (int)\n", i, c, c);
    #endif
  }
  #ifdef DEBUG
    fprintf(stderr,"i = %d\nSalgo de readXchars\n", i);
  #endif
  return i;
}

/* Verifica que el texto guardado en el buffer sea efectivamente base64 */
status_t check_reading (const char dictionary_b64[], const char buffer[], short buffer_lenght) {
    short i;
    register short j;
    static status_t centinela = VALID;

    if (buffer_lenght == 0)
        status = END;
    else if (buffer_lenght == 4)
        status = NORMAL_WORKING;
    else
				return ERROR; /* Si se leyeron entre 1 y 3 caracteres la cantidad total de caracteres en stdin
                         no es múltiplo de 4 */

    if(centinela==END) 
		{
        if(status==END)
            return END;
        else return ERROR;
    }else if (status==END)
            return END; /* Si no se leyeron caracteres se acabo el texto */
    else{
  			for(i=0; i<4; i++){
        		for(j=0; buffer[i]!=dictionary_b64[j]; j++){
        		    if(j==(MAX_B64_ITEMS-1)) { /*si el caracter no está en el diccionario... */
        		        if(i==0)
                    {
                      if (buffer[i] != '\n')
                        return ERROR;
                      else 
                      {
                        for (i=3; i>0; i--) ungetc(buffer[i], stdin);
                        /*Si hay un \n en el primer elemento, devuelve todo lo demás para ser leido nuevamente*/
                        return NEW_LINE;
                      }
                    }
                    else if (i==1)
        		            return ERROR; /* aunque fuera un B64_EXCEPTION_CHAR ('='), si está en seguna posicion
                                         del buffer => ERROR */
        		        else if(i==2){
        		            if(buffer[i]==B64_EXCEPTION_CHAR && buffer[i+1]==B64_EXCEPTION_CHAR){
        		                centinela=END; /* si los últimos dos caracteres del buffer son un B64_EXCEPTION_CHAR
                                              se prende el centinela que debe confirmar que en la próxima lectura
                                              se haya acabado el texto a leer */
        		                return VALID;
        		            }else return ERROR;
        		        }else if(i==3){
        		            if(buffer[i]==B64_EXCEPTION_CHAR){
        		                centinela=END; /* ídem con un solo B64_EXCEPTION_CHAR*/
        		                return VALID;
        		            }else return ERROR;
        		        }
        		    }
        		}
    		}
    }
		return VALID;
}

