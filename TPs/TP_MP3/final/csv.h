#ifndef CSV__H
#define CSV__H
#include "types.h"
#include "mp3.h"
#include "vector.h"
#include "lang.h"

#define DELIMITER_CHAR '|'

/**************** PROTOTIPOS CSV ****************/
status_t Export2CSV (ADT_Array_t *, string );
status_t Print_CSV (ADT_MP3_t *, FILE *);
/***********************************************/

#endif
