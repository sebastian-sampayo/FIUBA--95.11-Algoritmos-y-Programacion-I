#include "main.h"

/************ PROTOTIPOS DE FUNCIONES DE DATOS ************/
status_t Load_Vector (string , ADT_Array_t *);
status_t Load_Track (ADT_Array_t *, FILE *);
void destroy_atributes (void *);
status_t Validate_and_SetOptions(int , char *[], string *);
status_t array_printer (const void *, FILE *);
status_t track_printer (const void *, FILE *);
/**********************************************************/

int main (int argc, char *argv[])
{
   ADT_Array_t *vector;
   string path;
   logmsg("Nuevo Test\n");

   if ((status = Validate_and_SetOptions(argc, argv, &path))!=OK) return status;
   logmsg("valide, voy a crear vector");

   if ((status = ADT_Array_Create(&vector))!=OK) return status;
   logmsg("cree vector, voy a setear printer del vector");

   if ((status = ADT_Array_Set_printer(vector, array_printer))!=OK) return status;
   logmsg("setie, voy a cargar vector");

   if ((status = Load_Vector(path, vector))!=OK) return status;
   logmsg("cargue vector, voy a exportar");
/* Sort() */

   if ((status = pExport[export_id](vector, FILE_OUT_NAME))!=OK) return status;
   logmsg("exporte, seteo destructor");

   if ((status = ADT_Array_Set_destructor(vector, destroy_atributes))!=OK) return status;
   logmsg("setie, destruyo vector");

   ADT_Array_Destroy(&vector);
   logmsg("destrui vector, libero path");

   free(path);

   return EXIT_SUCCESS;
}

status_t Load_Vector (string path, ADT_Array_t *vector)
{
   DIR  *dfd;
   struct dirent *dp;
   FILE *file;
   string aux;

   if (vector == NULL) return ERR_NULL_POINTER;

   if ((dfd = opendir(path) ) == NULL) return ERR_PATH_INVALID;

   while ((dp = readdir(dfd)) != NULL) 
   {
      if (!strcmp(dp->d_name,".") || !strcmp(dp->d_name,"..")) continue;
      logstr("dp->d_name = ", dp->d_name);

      if(strdup(&aux, path)!=OK) return ERR_MEMORY;
      if(my_strcat(&aux, dp->d_name)!=OK) return ERR_MEMORY;
      logmsg("se copio bien con my_strcat");
      logstr("aux = ", aux);

      if((file = fopen(aux,"rb"))==NULL) return ERR_OPENING_FILE;
      if((status = Load_Track (vector, file)) != OK) return status;
      fclose(file);
      free(aux);      
   }

    closedir(dfd);
    return OK;
}

/* Obtiene el header del archivo .mp3
   Crea un track TDA MP3
   Setea sus atributos incluyedo el printer
   Aniade dicho track al vector que se le paso como argumento  */
status_t Load_Track (ADT_Array_t *vector, FILE *file)
{
   char header[MP3_HEADER_SIZE];
   char buf[MP3_ATTRIBUTE_MAX_SIZE+1];
   ADT_MP3_t *track;

   fseek(file, -MP3_HEADER_SIZE, SEEK_END);
   fread(header,sizeof(char),MP3_HEADER_SIZE,file);

   if((status = ADT_MP3_Create(&track))!= OK) return status;

/*
    memcpy(buf,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    buf[LEXEM_SPAN_TAG] = '\0';
    printf("%s%s\n","tag:",buf);
*/
    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    if((status = ADT_MP3_Set_Title(track, buf))!=OK) return status;
   logstr("title = ", buf);

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    if((status = ADT_MP3_Set_Artist(track, buf))!=OK) return status;
   logstr("artist = ", buf);
/*
    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    printf("%s%s\n","album:",buf);

    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    printf("%s%s\n","year:",buf);

    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    printf("%s%s\n","comment:",buf);
*/
    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    buf[LEXEM_SPAN_GENRE] = '\0';
    if((status = ADT_MP3_Set_Genre(track, buf))!=OK) return status;

   /* track_printer enmascara el printer global que sabe como imprimir */
   if ((status = ADT_MP3_Set_printer(track, track_printer))!=OK) return status;

   if((status = ADT_Array_Append(vector, track))!=OK) return status;

   return OK;
}

void destroy_atributes (void *dato)
{
   if (dato == NULL) return ;

   ADT_MP3_Destroy_Title(dato);
   ADT_MP3_Destroy_Artist(dato);
   ADT_MP3_Destroy_Genre(dato);
}

/* Valida argumentos en el orden que sea que esten,
   setea el tipo de exportacion,
   y almacena la ruta.                              */
status_t Validate_and_SetOptions(int argc, char *argv[], string *path)
{
   short i;

   if (argc != MAX_AMOUNT_OF_ARGUMENTS) return ERR_AMOUNT_OF_ARGUMENTS;

   /* Valido y selecciono formato */
   for (i=0; i<argc; i++)
      if (!strcmp(argv[i], ARGV_MODIFIER_FORMAT_STRING)) break;
   if (i == argc) return ERR_ARGV_FORMAT;
   
   if (!strcmp(argv[i+1], ARGV_FORMAT_CSV_STRING)) export_id = CSV;
   else if (!strcmp(argv[i+1], ARGV_FORMAT_HTML_STRING)) export_id = HTML;
   else if (!strcmp(argv[i+1], ARGV_FORMAT_XML_STRING)) export_id = XML;
   else return ERR_FORMAT_OPTION;

   /* Valido criterio de ordenamiento */
   for (i=0; i<argc; i++)
      if (!strcmp(argv[i], ARGV_MODIFIER_SORT_STRING)) break;
   if (i == argc) return ERR_ARGV_SORT;
   if (argv[i+1] == NULL) return ERR_SORT_OPTION;

   /* Valido ruta y la almaceno en heap */
   for (i=0; i<argc; i++)
      if (!strcmp(argv[i], ARGV_MODIFIER_PATH_STRING)) break;
   if (i == argc) return ERR_ARGV_PATH;
   if (argv[i+1] == NULL) return ERR_PATH_OPTION;

   if (strdup(path, argv[i+1]) != OK) return ERR_MEMORY;

   return OK;
}

/**/
/* Enmascarador que recive void* para coincidir con el printer del TDA vector,
   Llama a ADT_MP3_Print que recive ADT_MP3_t *, 
   Dicho en otras palabras, logro que el printer del TDA vector sea la primitiva de impresion del TDA MP3 
*/
status_t array_printer (const void *data, FILE *f)
{
   if( data==NULL || f==NULL) return ERR_NULL_POINTER;
   /* casteo data a ADT_MP3_t */
   if((status = ADT_MP3_Print((ADT_MP3_t *)data, f)) != OK) return status;
   return OK;
}

/* Enmascarador que recive void* para coincidir con el printer del TDA MP3,
   Llama a la funcion que sabe como imprimir recibiendo un ADT_MP3_t
*/
status_t track_printer (const void *data, FILE *f)
{
   if( data==NULL || f==NULL) return ERR_NULL_POINTER;
   /* casteo data a ADT_MP3_t */
   if((status = MP3_printer[export_id]((ADT_MP3_t *)data, f)) != OK) return status;
   return OK;
}
