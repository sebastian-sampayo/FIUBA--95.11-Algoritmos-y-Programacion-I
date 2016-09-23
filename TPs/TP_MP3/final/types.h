#ifndef TYPES__H
#define TYPES__H

/* Documentacion de posibles estados que devuelve la aplicacion
Estados genericos:
0:   OK
1:   ERROR, 
Errores de bajo nivel: 10-19
10:   ERR_MEMORY, 
11:   ERR_NULL_POINTER, 
Errores de archivos y directorios: 20-29
20:   ERR_PATH_INVALID, 
21:   ERR_OPENING_FILE,
Errores de argumentos: >30
30:   ERR_AMOUNT_OF_ARGUMENTS,
31:   ERR_ARGV_FORMAT,
32:   ERR_FORMAT_OPTION,
33:   ERR_ARGV_SORT,
34:   ERR_SORT_OPTION,
35:   ERR_ARGV_PATH,
36:   ERR_PATH_OPTION
*/

typedef enum{
   OK = 0,
   ERROR = 1, 
   ERR_MEMORY = 10, 
   ERR_NULL_POINTER, 
   ERR_PATH_INVALID = 20, 
   ERR_OPENING_FILE,
   ERR_AMOUNT_OF_ARGUMENTS = 30,
   ERR_ARGV_FORMAT,
   ERR_FORMAT_OPTION,
   ERR_ARGV_SORT,
   ERR_SORT_OPTION,
   ERR_ARGV_PATH,
   ERR_PATH_OPTION
} status_t;

typedef char* string;

/* Formatos de exportacion disponibles */
typedef enum{
   CSV,
   HTML,
   XML
} export_t;

#endif
