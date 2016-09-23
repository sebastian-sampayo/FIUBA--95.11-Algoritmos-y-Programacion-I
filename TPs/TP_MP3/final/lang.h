#ifndef LANG__H
#define LANG__H
#include "types.h"

extern const string language_string[];

/* Este es el orden a respetar por los paquetes de idiomas */
typedef enum {
   TITLE, 
   ARTIST, 
   GENRE
} language_string_t;

#endif
