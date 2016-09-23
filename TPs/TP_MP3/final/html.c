#include "html.h"



status_t Export2HTML (ADT_Array_t *vector, string file_name)
{
   FILE *file;

   if (vector == NULL || file_name == NULL) return ERR_NULL_POINTER;

   if ((file = fopen(file_name,"wt"))==NULL) return ERR_OPENING_FILE;

   fprintf(file, "HTML Export not available.\n");

   if (fclose(file)==EOF) return ERR_MEMORY;
   return OK;
}

status_t Print_HTML (ADT_MP3_t *track, FILE *file)
{
   fprintf(file, "HTML Print not available.\n");
   return OK;
}
