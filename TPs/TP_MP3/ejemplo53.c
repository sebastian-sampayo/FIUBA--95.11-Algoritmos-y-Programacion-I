/* //////////////////////////////////////////////////////////////////////////////////////
   Algoritmos y Programación I - 75.02 - Curso Ing. Martín Cardozo
   Archivo: ejemplo53.c
   Descripcion: Estructura de directorios
   Obs: Estas funciones son Windows/UNIX/DOS compatibles, NO SON ANSI-C, pero sí son POSIX
   ////////////////////////////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>    /* DIR etc */
#include <string.h>

#define MAX_STRING  200

#define FILES_CHOP  10

typedef char * string;

/* ///////////////////// Prototipos ////////////////////////// */
string  my_strdup           (string);
string *get_dir_files    (string, size_t *);
void    str_free         (string [], size_t);
/* //////////////////////////////////////////////////////////  */

int main (void)
{
    char *dir_name = "C:\\dut\\dir";
    size_t  L, i;
    string *files;

    files = get_dir_files(dir_name, &L);
    for (i=0; i<L; i++) printf("%s\n",files[i]);
    str_free(files,L);

    return 0;
}


string *get_dir_files (string dir_name, size_t *L)
{
    DIR  *dfd;
    struct dirent *dp;
    size_t alloc_size;
    size_t used_size = 0;
    string *files;
    string *aux;


    if ((dfd = opendir(dir_name) ) == NULL) {
        fprintf(stderr,"no puede abrir el directorio\n");
        *L = 0;
        return NULL;
    }
    if ((files = (string *) malloc(sizeof(string) * FILES_CHOP)) == NULL) {
        fprintf(stderr,"Memoria insuficiente.");
        *L = 0;
        closedir(dfd);
        return NULL;
    }
    alloc_size = FILES_CHOP;

    while ((dp = readdir(dfd)) != NULL) {
        if (!strcmp(dp->d_name,".") || !strcmp(dp->d_name,"..")) continue;
        if (alloc_size == used_size) {
            if ((aux = (string *) realloc(files, (alloc_size + FILES_CHOP) * sizeof(string))) == NULL) {
                str_free(files,used_size);
                *L = 0;
                closedir(dfd);
                return NULL;  /* Memoria insuficiente */
            }
            files = aux;
            alloc_size += FILES_CHOP;
        }
        files[used_size++] = my_strdup(dp->d_name);

    }
    closedir(dfd);
    *L = used_size;
    return files;
}

string my_strdup (string s)
{
    string t;

    if ((t = (string) malloc((strlen(s)+1) * sizeof(char))) == NULL) return NULL;
    strcpy(t,s);
    return t;
}

void str_free (string arr[], size_t len)
{
    size_t i;
    for (i = 0; i<len; i++)  free(arr[i]);
    free(arr);
}


