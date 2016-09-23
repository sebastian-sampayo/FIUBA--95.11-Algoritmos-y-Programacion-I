#include <stdio.h>
#include "diccionarios.h"

int main(void)
{
  char str[100], asd;
  short i,j,k;
  asd = ('á' % 128);
  fgets(str, 100, stdin);
  for(k=0; str[k]!='\0'; k++);
  printf("asd %c\n%c\n%c\n", asd, str[0], 'á');

  for(i=0; i < k; i++)
  {
    printf("\nstr = %c\n\n", str[i]);
    for (j=0; j<ITEMS; j++)
    {
      ASCIIcharset[j] = (ASCIIcharset[j] % 128) + 128;
      if (str[i] == ASCIIcharset[j])
      {
        printf("COMELA, %c = %c\n", str[i], ASCIIcharset[j]);
        break;
      }
      if (str[i]== 'á')
        puts("forro");
    }
  }
  return 0;
}
