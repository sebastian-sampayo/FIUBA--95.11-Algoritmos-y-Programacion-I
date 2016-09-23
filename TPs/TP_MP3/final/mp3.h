#ifndef MP3__H
#define MP3__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "genres.h"
#include "utilities.h"

typedef status_t (*MP3_printer_t)(const /*ADT_MP3_t*/void * , FILE* );

typedef struct{
   string title, artist, album,
          tag, comment, year, genre;
   MP3_printer_t printer;
} ADT_MP3_t;

/****************** PROTOTIPOS TDA MP3 ************************/
status_t ADT_MP3_Create (ADT_MP3_t **);
status_t ADT_MP3_Set_Title (ADT_MP3_t *, string);
status_t ADT_MP3_Set_Artist (ADT_MP3_t *, string);
status_t ADT_MP3_Set_Genre (ADT_MP3_t *, string);
status_t ADT_MP3_Get_Title (ADT_MP3_t *, string *);
status_t ADT_MP3_Get_Artist (ADT_MP3_t *, string *);
status_t ADT_MP3_Get_Genre (ADT_MP3_t *, string *);
/*status_t ADT_MP3_Print_CSV (ADT_MP3_t *, FILE *);*/
status_t ADT_MP3_Print (ADT_MP3_t *, FILE *);
status_t ADT_MP3_Set_printer (ADT_MP3_t *, MP3_printer_t );
void ADT_MP3_Destroy (ADT_MP3_t **);
void ADT_MP3_Destroy_Title (ADT_MP3_t *);
void ADT_MP3_Destroy_Artist (ADT_MP3_t *);
void ADT_MP3_Destroy_Genre (ADT_MP3_t *);
/*************************************************************/

#endif
