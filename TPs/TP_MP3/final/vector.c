#include "vector.h"

/* variable global al modulo */
status_t status;
/**/


/* 
status_t ADT_Array_Export2CSV (ADT_Array_t *vector, string file_name)
Se elimino esta primitiva.
A los efectos de agregar nuevas funciones de exportacion para la aplicacion hay que recompilar todo el TDA.
La funcion de exportacion debe ser ajena al TDA y utilizar ADT_Array_Print() seteada con el correspondiente printer.
*/
/* Print genérico */
status_t ADT_Array_Print(ADT_Array_t *vector, FILE *fo)
{
   size_t i;

   if (vector == NULL || fo == NULL) return ERR_NULL_POINTER;

   for(i=0; i<vector->size; i++)
      if((status = vector->printer(vector->data[i], fo))!=OK) return status;
   return OK;
}

/** Setters **/

status_t ADT_Array_Set_printer(ADT_Array_t *vector, Array_printer_t pf)
{
   if (vector == NULL || pf == NULL) return ERR_NULL_POINTER;
   vector->printer = pf;
   return OK;
}

status_t ADT_Array_Set_destructor(ADT_Array_t *pArr, destructor_t pf)
{
   if (pf == NULL || pArr == NULL) return ERR_NULL_POINTER;
   pArr->destructor = pf;
   return OK;
}

/** Getters **/

status_t ADT_Array_Get_element_at(ADT_Array_t *pArr, size_t pos, void **target)
{
   if(pArr == NULL || target == NULL) return ERR_NULL_POINTER;
   if(pos>pArr->size) {*target = NULL; return ERROR;}
   *target = pArr->data[pos];
   return OK;
}

size_t ADT_Array_Get_size(ADT_Array_t *pArr)
{
   return pArr->size;
}


void ADT_Array_Destroy(ADT_Array_t **pArr)
{
   size_t i;
   if (pArr == NULL) return ;
   /* primero destruyo globitos */
   for(i=0; i<(*pArr)->size; i++)
   {
      (*pArr)->destructor((*pArr)->data[i]); 
      (*pArr)->data[i] = NULL;
   }
   /* luego arreglo */
   free((*pArr)->data);
   (*pArr)->data = NULL;
   /* luego TDA */
   free(*pArr);
   *pArr = NULL;
}

status_t ADT_Array_Create(ADT_Array_t **pArr)
{
   if (pArr == NULL) return ERR_NULL_POINTER;

   /* pido memoria para el TDA */
   if((*pArr = (ADT_Array_t *)malloc(sizeof(ADT_Array_t)))==NULL)
      return ERR_MEMORY;
   /* pido memoria para el arreglo de punteros a globito (data) */
   if(((*pArr)->data = (void **)malloc(INIT_CHOP*sizeof(void *)))==NULL)
   {
      free(*pArr);
      *pArr = NULL;
      return ERR_MEMORY;
   }
   (*pArr)->alloc_size = INIT_CHOP;
   (*pArr)->size = 0;
   return OK;
}

status_t ADT_Array_Append(ADT_Array_t *pArr, void *new_data)
{
   void **aux;
   if (pArr == NULL) return ERR_NULL_POINTER;

   if(pArr->size == pArr->alloc_size)
   {
      if((aux = (void **)realloc(pArr->data, (pArr->alloc_size+CHOP)*sizeof(void*)))==NULL)
         return ERR_MEMORY;
      pArr->alloc_size += CHOP;
      pArr->data = aux;
   }
   pArr->data[(pArr->size)++] = new_data;
   return OK;
}
