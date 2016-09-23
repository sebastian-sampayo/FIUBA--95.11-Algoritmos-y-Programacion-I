/* ////////////////// base64.h ///////////////////*/
#ifndef BASE64__H
#define BASE64__H
#include "types.h"

#define DEBUG

#define NEW_LINE_CHAR '\n'

/* Diccionario base64. Maxíma cantidad de elementos en el diccionario */
#define MAX_B64_ITEMS 64
/* Impresion en base64. Cantidad máxima de caracteres por línea */
#define B64_LINE_LENGTH 76
/* Caracter utilizado para casos excepcionales */
#define B64_EXCEPTION_CHAR '='
/* Setup para funciones encode/decode */
#define BUFFER_ASCII_BYTES_LENGTH 3
#define BUFFER_B64_BYTES_LENGTH 4
#define SHIFT_BYTE_ASCII 8
#define SHIFT_BYTE_B64 6
#define MASK_BYTE_ASCII 0xFF
#define MASK_BYTE_B64 0x3F

extern const char dictionary_b64[];

/******************PROTOTIPOS****************/
status_t decode(char [], char []);
void encode_normal(const char [], char []);
void encode_exception1(const char [], char []);
void encode_exception2(const char [], char []);
/*******************************************/

#endif
