/* ////////////////// base64.c ///////////////////*/
#include <stdio.h>
#include <stdlib.h>
#include "base64.h"
#include "types.h"

const char dictionary_b64[MAX_B64_ITEMS] = {
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'0','1','2','3','4','5','6','7','8','9','+','/'
};


status_t decode(char array_in[], char array_out[])
{
  short i, j;
  static bool_t exception_char_read = FALSE;
  unsigned int buffer=0;

  /** linkeo caracteres ascii con diccionario b64 **/
  for(i=0; i<BUFFER_B64_BYTES_LENGTH; i++)
  {
    for(j=0; array_in[i]!=dictionary_b64[j] && j<MAX_B64_ITEMS; j++);
    if(j<MAX_B64_ITEMS)
      array_in[i]=j;
    else if (array_in[i] == B64_EXCEPTION_CHAR && i>1)
    {
      if (exception_char_read == TRUE) return ERR_INPUT;
      array_in[i]=0;
      exception_char_read = TRUE;
    }
    else return ERR_INPUT;
  }

  /** lleno un buffer de 4 bytes de 6 bits **/
  for(i=0, j=BUFFER_B64_BYTES_LENGTH-1; i<BUFFER_B64_BYTES_LENGTH; i++, j--)
    buffer |= array_in[i]<<(j*SHIFT_BYTE_B64);

  /** saco del buffer 3 bytes de 8 bits **/
  for(j=0, i=BUFFER_ASCII_BYTES_LENGTH-1; j<BUFFER_ASCII_BYTES_LENGTH; j++, i--)
    array_out[i] = ((buffer>>(j*SHIFT_BYTE_ASCII))&MASK_BYTE_ASCII);

  return OK;
}

void encode_normal(const char array_in[], char array_out[])
{
  short i, j;
  unsigned int buffer=0;

  for(i=0, j=BUFFER_ASCII_BYTES_LENGTH-1; i<BUFFER_ASCII_BYTES_LENGTH; i++, j--)
    buffer |= (unsigned char)array_in[i]<<(j*SHIFT_BYTE_ASCII); /*casteo en caso de encontrar caracter extendido */

  for(i=BUFFER_B64_BYTES_LENGTH-1, j=0; j<BUFFER_B64_BYTES_LENGTH; i--, j++)
    array_out[i] = (buffer>>(j*SHIFT_BYTE_B64)) & MASK_BYTE_B64;
}

/* codifica ascii a b64 en modo EXCEPCION1 */
void encode_exception1(const char array_in[], char array_out[])
{
  unsigned int buffer=0;

  array_out[3] = B64_EXCEPTION_CHAR;
  array_out[2] = B64_EXCEPTION_CHAR;
  buffer = (unsigned char)array_in[0] << 4; /* Relleno con 0s *//*casteo en caso de encontrar caracter extendido */

  array_out[1]= buffer&MASK_BYTE_B64;
  array_out[0]= (buffer>>6)&MASK_BYTE_B64;
}

/* codifica ascii a b64 en modo EXCEPCION2 */
void encode_exception2(const char array_in[], char array_out[])
{
  unsigned int buffer=0;

  array_out[3] = B64_EXCEPTION_CHAR;
  buffer = (unsigned char)array_in[0] << 10; /* Relleno con 0s */ /*casteo en caso de encontrar caracter extendido */
  buffer |= (unsigned char)array_in[1] << 2;

  array_out[2]= buffer&MASK_BYTE_B64;
  array_out[1]= (buffer>>6)&MASK_BYTE_B64;
  array_out[0]= (buffer>>12)&MASK_BYTE_B64;
  
}
