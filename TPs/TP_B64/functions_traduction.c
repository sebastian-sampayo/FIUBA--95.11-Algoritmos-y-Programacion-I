/* Funciones codificadoras/decodificadoras */
#include <stdio.h>
#include "setup.h"

extern const char dictionary_b64[];

/******************PROTOTIPOS**************
void link_ascii_b64 (const char [], char [], char []);
void decode(const char [], char []);
void encode_normal(const char [], char []);
void encode_exception1(const char [], char []);
void encode_exception2(const char [], char []);
*/

/* DECODIFICACION base64 --> ascii */
/* Esta funcion linkea los caracteres que nosotros leemos en ascii con su correspondiente expresión en base 64 */
void link_ascii_b64 (const char dictionary_b64[], char characters_ascii[], char buffer_b64[])
{
    short i;
    register short j;

    for(i=0; i<4; i++)
    {
        for(j=0; characters_ascii[i]!=dictionary_b64[j] && j<MAX_B64_ITEMS; j++);
        if(j<MAX_B64_ITEMS)
            buffer_b64[i]=j;
        else buffer_b64[i]=0;
    }
}

/* Decodificador b64 --> ascii
   void decode(char array_in[], char array_out[]) */
/* en setup.h 
#define BUFFER_ASCII_BYTES_LENGHT 3
#define BUFFER_B64_BYTES_LENGHT 4
#define SHIFT_BYTE_ASCII 8
#define SHIFT_BYTE_B64 6
#define MASK_BYTE_ASCII 0xFF */

void decode(const char array_in[], char array_out[])
{
  short i, j;
  unsigned int buffer=0;
  #ifdef DEBUG
    fprintf(stderr,"Entro a decode\n");
  #endif

  for(i=0, j=BUFFER_B64_BYTES_LENGHT-1; i<BUFFER_B64_BYTES_LENGHT; i++, j--)
  {
    buffer |= array_in[i]<<(j*SHIFT_BYTE_B64);
    #ifdef DEBUG
      fprintf(stderr,"buffer = %X | j = %d | i = %d | j*6 = %d\n", buffer, j, i, j*6);
      fprintf(stderr,"array_in[i] = %X\n", array_in[i]);
    #endif
  }

  #ifdef DEBUG
    fprintf(stderr,"buffer = %X\nj = %d\n", buffer, j);
  #endif
  for(j=0, i=BUFFER_ASCII_BYTES_LENGHT-1; j<BUFFER_ASCII_BYTES_LENGHT; j++, i--)
  {
    array_out[i] = ((buffer>>(j*SHIFT_BYTE_ASCII))&MASK_BYTE_ASCII);
    #ifdef DEBUG
      fprintf(stderr,"buffer = %X\nj = %d | array_out[i] = %X\n",buffer, j, array_out[i]);
    #endif
  }
  #ifdef DEBUG
    fprintf(stderr,"Salgo de decode\n");
  #endif
}

/* CODIFICACION ascii --> base64 */
/* codifica ascii a b64 en modo NORMAL
   void encode_normal(char array_in[], char array_out[]) */
/* en setup.h 
#define BUFFER_ASCII_BYTES_LENGHT 3
#define BUFFER_B64_BYTES_LENGHT 4
#define SHIFT_BYTE_ASCII 8
#define SHIFT_BYTE_B64 6
#define MASK_BYTE_B64 0x3F */

void encode_normal(const char array_in[], char array_out[])
{
  short i, j;
  unsigned int buffer=0;
  #ifdef DEBUG
    fprintf(stderr,"Entro a encode_normal\n");
  #endif

  for(i=0, j=BUFFER_ASCII_BYTES_LENGHT-1; i<BUFFER_ASCII_BYTES_LENGHT; i++, j--)
  {
    buffer |= (unsigned char)array_in[i]<<(j*SHIFT_BYTE_ASCII); /*casteo en caso de encontrar caracter extendido */
    #ifdef DEBUG
      fprintf(stderr,"i = %d | j = %d\narray_in[i] = %X %c| buffer = %X\n",i,j,array_in[i], array_in[i],buffer);
    #endif
  }

  #ifdef DEBUG
    fprintf(stderr,"buffer = %X\n", buffer);
  #endif

  for(i=BUFFER_B64_BYTES_LENGHT-1, j=0; j<BUFFER_B64_BYTES_LENGHT; i--, j++)
  {
    array_out[i] = (buffer>>(j*SHIFT_BYTE_B64)) & MASK_BYTE_B64;
    #ifdef DEBUG
      fprintf(stderr,"array_out[i = %d] = %X\n", i, array_out[i]);
    #endif
  }
  #ifdef DEBUG
    fprintf(stderr,"Salgo de encode_normal\n");
  #endif
}

/* codifica ascii a b64 en modo EXCEPCION1 */
void encode_exception1(const char array_in[], char array_out[])
{
  unsigned int buffer=0;

  #ifdef DEBUG
    short i;
    fprintf(stderr,"Entro a encode_exception1: array_in[0] = %X\n", array_in[0]);
  #endif
  array_out[3] = B64_EXCEPTION_CHAR;
  array_out[2] = B64_EXCEPTION_CHAR;
  buffer = (unsigned char)array_in[0] << 4; /* Relleno con 0s *//*casteo en caso de encontrar caracter extendido */

  #ifdef DEBUG
    fprintf(stderr,"buffer = %X\n", buffer);
  #endif

  array_out[1]= buffer&MASK_BYTE_B64;
  array_out[0]= (buffer>>6)&MASK_BYTE_B64;
 
  #ifdef DEBUG 
    for (i=0; i<4; i++)
      fprintf(stderr,"array_out[i = %d] = %X\n", i, array_out[i]);
    fprintf(stderr,"Salgo de encode_exception1\n");
  #endif
}

/* codifica ascii a b64 en modo EXCEPCION2 */
void encode_exception2(const char array_in[], char array_out[])
{
  unsigned int buffer=0;

  #ifdef DEBUG
    short i;
    fprintf(stderr, "Entro a encode_exception2:\narray_in[0] = %X\narray_in[1] = %X\n", array_in[0], array_in[1]);
  #endif
  array_out[3] = B64_EXCEPTION_CHAR;
  buffer = (unsigned char)array_in[0] << 10; /* Relleno con 0s */ /*casteo en caso de encontrar caracter extendido */
  buffer |= (unsigned char)array_in[1] << 2;

  #ifdef DEBUG
    fprintf(stderr,"buffer = %X\n", buffer);
  #endif

  array_out[2]= buffer&MASK_BYTE_B64;
  array_out[1]= (buffer>>6)&MASK_BYTE_B64;
  array_out[0]= (buffer>>12)&MASK_BYTE_B64;
  
  #ifdef DEBUG  
    for (i=0; i<4; i++)
      fprintf(stderr,"array_out[i = %d] = %X\n", i, array_out[i]);
    fprintf(stderr,"Salgo de encode_exception2\n");
  #endif
}
