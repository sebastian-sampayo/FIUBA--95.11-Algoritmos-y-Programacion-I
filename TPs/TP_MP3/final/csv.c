#include "csv.h"

/* variable gobal al modulo */
status_t status;

/* el main llama a un puntero a funcion para exportar. Este apunta a Export2CSV(), que llama a ADT_Array_Print(),
que llama a su printer, que apunta a ADT_MP3_Print() (a traves de un enmascarador), que llama a su printer,
que apunta a Print_CSV().*/

/* Esta funcion recive un TDA vector y un nombre de archivo CSV a crear
   Imprime la cabecera y llama a la primitiva del TDA vector para imprimir los elementos */
status_t Export2CSV (ADT_Array_t *vector, string file_name)
{
   FILE *file;

   if (vector == NULL || file_name == NULL) return ERR_NULL_POINTER;

   if ((file = fopen(file_name,"wt"))==NULL) return ERR_OPENING_FILE;

   /* Imprimo cabecera */
   fprintf(file, "%s%c%s%c%s\n",
      language_string[TITLE],DELIMITER_CHAR, language_string[ARTIST],DELIMITER_CHAR, language_string[GENRE]);

   /* Imprimo elementos */
   if ((status = ADT_Array_Print (vector, file)) != OK) return status;
   
   if (fclose(file)==EOF) return ERR_MEMORY;
   return OK;
}

/* este sera el printer del TDA mp3, que será a su vez, el printer del TDA vector */

/* Esta funcion recive un TDA mp3 y un stream abierto,
   Obtiene los atributos del TDA mp3 a traves de las primitivas "getters"
   Los imprime en el stream en forma de CSV                               */
status_t Print_CSV (ADT_MP3_t *track, FILE *file)
{
   string buffer;
   if (track == NULL || file == NULL) return ERR_NULL_POINTER;

   if ((status = ADT_MP3_Get_Title(track, &buffer)) != OK) return status;
   fprintf(file, "%s%c", buffer, DELIMITER_CHAR);
   free(buffer);

   if ((status = ADT_MP3_Get_Artist(track, &buffer)) != OK) return status;
   fprintf(file, "%s%c", buffer, DELIMITER_CHAR);
   free(buffer);

   if ((status = ADT_MP3_Get_Genre(track, &buffer)) != OK) return status;
   fprintf(file, "%s\n", buffer);
   free(buffer);

   return OK;
}
