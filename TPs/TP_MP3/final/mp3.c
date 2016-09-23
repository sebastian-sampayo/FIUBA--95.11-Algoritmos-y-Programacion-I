#include "mp3.h"

status_t status;

/* 
status_t ADT_MP3_Print_CSV (ADT_MP3_t *mp3, FILE *file)
Esta primitiva fue eliminada.
A los efectos de agregar nuevas funciones de exportacion hay que recompilar todo el TDA
Está función debe ser ajena al TDA y utilizar ADT_MP3_Print() seteada con el correspondiente printer 
*/
/* Print genérico */
status_t ADT_MP3_Print (ADT_MP3_t *mp3, FILE *file)
{
   if (mp3 == NULL || file == NULL) return ERR_NULL_POINTER;
   if ((status = mp3->printer(mp3, file)) != OK) return status;
   return OK;
}

/** Setters **/

status_t ADT_MP3_Set_printer (ADT_MP3_t *mp3, MP3_printer_t pf)
{
   if (mp3 == NULL || pf == NULL) return ERR_NULL_POINTER;
   mp3->printer = pf;
   return OK;
}

status_t ADT_MP3_Set_Title (ADT_MP3_t *mp3, string new_title)
{
   if (mp3 == NULL || new_title == NULL) return ERR_NULL_POINTER;
   if (strdup(&(mp3->title), new_title) != OK) return ERR_MEMORY;
   return OK;
}

status_t ADT_MP3_Set_Artist (ADT_MP3_t *mp3, string new_artist)
{
   if (mp3 == NULL || new_artist == NULL) return ERR_NULL_POINTER;
   if (strdup(&(mp3->artist), new_artist) != OK) return ERR_MEMORY;
   return OK;
}

status_t ADT_MP3_Set_Genre (ADT_MP3_t *mp3, string new_genre)
{
   if (mp3 == NULL || new_genre == NULL) return ERR_NULL_POINTER;
   if (strdup(&(mp3->genre), new_genre) != OK) return ERR_MEMORY;
   return OK;
}

/** Getters **/

status_t ADT_MP3_Get_Title (ADT_MP3_t *mp3, string *s)
{
   if (mp3 == NULL || mp3->title == NULL) return ERR_NULL_POINTER;
   if (strdup(s, mp3->title) != OK) return ERR_MEMORY;
   return OK;
}

status_t ADT_MP3_Get_Artist (ADT_MP3_t *mp3, string *s)
{
   if (mp3 == NULL || mp3->artist == NULL) return ERR_NULL_POINTER;
   if (strdup(s, mp3->artist) != OK) return ERR_MEMORY;
   return OK;
}

status_t ADT_MP3_Get_Genre (ADT_MP3_t *mp3, string *s)
{
   int aux = strtod(mp3->genre, NULL);
   if (mp3 == NULL || mp3->genre == NULL) return ERR_NULL_POINTER;
   if (strdup(s, (string)genres[aux]) != OK) return ERR_MEMORY;
   return OK;
}


status_t ADT_MP3_Create(ADT_MP3_t **mp3)
{
   if(mp3 == NULL) return ERR_NULL_POINTER;
   if((*mp3 = (ADT_MP3_t *)malloc(sizeof(ADT_MP3_t)))==NULL) return ERR_MEMORY;
   /* pongo a null cada miembro por seguridad */
   (*mp3)->title = NULL;
   (*mp3)->artist = NULL;
   (*mp3)->album = NULL;
   (*mp3)->year = NULL;
   (*mp3)->tag = NULL;
   (*mp3)->comment = NULL;
   (*mp3)->genre = NULL;
   return OK;
}

/* Esta funcion no es compatible con el programa porque será llamada por el destructor del TDA vector
   Sucede que luego de detruir cada atributo destruye la estructura del track,
   pero en la aplicacion, de eso se encargara el destructor del TDA vector                           */
void ADT_MP3_Destroy(ADT_MP3_t **mp3)
{
   if(mp3 == NULL) return ;
   /* primero libero globitos */
   if (((*mp3)->tag)!=NULL) {free((*mp3)->tag); (*mp3)->tag=NULL;}
   if (((*mp3)->title)!=NULL) {free((*mp3)->title); (*mp3)->title=NULL;}
   if (((*mp3)->artist)!=NULL) {free((*mp3)->artist); (*mp3)->artist=NULL;}
   if (((*mp3)->album)!=NULL) {free((*mp3)->album); (*mp3)->album=NULL;}
   if (((*mp3)->comment)!=NULL) {free((*mp3)->comment); (*mp3)->comment=NULL;}
   if (((*mp3)->year)!=NULL) {free((*mp3)->year); (*mp3)->year=NULL;}
   if (((*mp3)->genre)!=NULL) {free((*mp3)->genre); (*mp3)->genre=NULL;}
   /* luego estructura */
   free(*mp3);
   *mp3 = NULL;
}

/* Por eso la divido en funciones destructoras de atributos
   que serán usadas en una funcion destructor compatible para el TDA vector */
void ADT_MP3_Destroy_Title(ADT_MP3_t *mp3)
{
   if (mp3 == NULL) return ;

   if ((mp3->title)!=NULL) {free(mp3->title); mp3->title=NULL;}
}

void ADT_MP3_Destroy_Artist(ADT_MP3_t *mp3)
{
   if (mp3 == NULL) return ;

   if ((mp3->artist)!=NULL) {free(mp3->artist); mp3->artist=NULL;}
}

void ADT_MP3_Destroy_Genre(ADT_MP3_t *mp3)
{
   if (mp3 == NULL) return ;

   if ((mp3->genre)!=NULL) {free(mp3->genre); mp3->genre=NULL;}
}
