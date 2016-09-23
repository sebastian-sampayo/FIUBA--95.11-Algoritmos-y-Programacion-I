#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char s[10] = "hola", t[10] = "asdaasd";
  int i = strcmp(s,t);
  printf("i = %d\n", i);
  if (i >0)
    puts("mayor a 0");
  else if (i<0)
    puts("menor a 0");
  else if (i == 0)
    printf("igual a 0, i = %d\n", i);
  for (i=0; i<10; i++) printf("%c", 7);
  return 0;
}
