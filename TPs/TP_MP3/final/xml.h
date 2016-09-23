#ifndef XML__H
#define XML__H

#include "types.h"
#include "mp3.h"
#include "vector.h"

/**************** PROTOTIPOS XML ****************/
status_t Export2XML (ADT_Array_t *, string );
status_t Print_XML (ADT_MP3_t *, FILE *);
/***********************************************/

#endif
