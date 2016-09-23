#include "utilities.h"

status_t strdup(string *t, const string s)
{
   if((*t = malloc(strlen(s)+1))==NULL) return ERR_MEMORY;
   strcpy(*t, s);
   return OK;
}

status_t my_strcat(string *t, string s)
{
   char * aux;
   if((aux = malloc(strlen(s) + strlen(*t) + 1))==NULL) return ERR_MEMORY;
   strcpy(aux, *t);
   strcat(aux, s);
   free(*t); /*si se llama a esta funcion es porque t fue pedido con malloc */
   *t = aux;
   return OK;
}

void logmsg(string msg)
{
   FILE *f;
   #ifdef DEBUG
      fprintf(stderr, "-Debug-|%s|\n", msg);
   #endif
/* warning: ISO C90 forbids mixed declarations and code */
   time_t tiempo = time(NULL);
   if((f = fopen(LOG_FILE,"at"))==NULL) return;
   fprintf(f, "%s-Debug-|%s|\n",ctime(&tiempo), msg);

   if(fclose(f)==EOF)
      return ;
}

void logstr(string msg, string s)
{
   FILE *f;
   #ifdef DEBUG
      fprintf(stderr, "-Debug-|%s|%s|\n", msg, s);
   #endif
/* warning: ISO C90 forbids mixed declarations and code */
   time_t tiempo = time(NULL);
   if((f = fopen(LOG_FILE,"at"))==NULL) return;
   fprintf(f, "%s-Debug-|%s|%s|\n",ctime(&tiempo), msg, s);

   if(fclose(f)==EOF)
      return ;
}

void logint(string msg, int i)
{
   FILE *f;
   #ifdef DEBUG
      fprintf(stderr, "-Debug-|%s|%d|\n", msg, i);
   #endif
/* warning: ISO C90 forbids mixed declarations and code */
   time_t tiempo = time(NULL);
   if((f = fopen(LOG_FILE,"at"))==NULL) return;
   fprintf(f, "%s-Debug-|%s|%d|\n",ctime(&tiempo), msg, i);

   if(fclose(f)==EOF)
      return ;
}
