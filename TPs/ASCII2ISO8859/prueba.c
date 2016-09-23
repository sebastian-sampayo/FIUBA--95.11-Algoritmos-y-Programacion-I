#include <stdio.h>
#include <stdlib.h>
#define NUL '\0'
#include "diccionarios.h"

int main(void)
{
  int i;
  for(i=0; a[i]!=NUL && b[i]!=NULL; i++) fprintf(stderr,"i = %d\ta[i] = %c\tb[i] = %s\n", i, a[i], b[i]);
  fprintf(stderr,"i = %d\n", i);
  if ((a[i] == NUL) && (b[i] == NULL))
    puts("todo piola");
  else 
    puts("Err Nitems");
  return 0;
}
