#ifndef VECTOR__H
#define VECTOR__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define INIT_CHOP 20
#define CHOP 20

typedef void (*destructor_t)(void *);
typedef status_t (*Array_printer_t)(const void * , FILE* );

typedef struct{
   void **data;
   size_t size, alloc_size;
   destructor_t destructor;
   Array_printer_t printer;
} ADT_Array_t;

/******************* PROTOTIPOS TDA VECTOR ******************/
status_t ADT_Array_Create(ADT_Array_t **);
    void ADT_Array_Destroy(ADT_Array_t **);
status_t ADT_Array_Set_destructor(ADT_Array_t *, destructor_t );
status_t ADT_Array_Append(ADT_Array_t *, void *);
  size_t ADT_Array_Get_size(ADT_Array_t *);
status_t ADT_Array_Get_element_at(ADT_Array_t *, size_t , void **);
/*status_t ADT_Array_Export2CSV (ADT_Array_t *, string );*/
status_t ADT_Array_Print (ADT_Array_t *, FILE *);
status_t ADT_Array_Set_printer (ADT_Array_t *, Array_printer_t );
/***********************************************************/

#endif

