#include <stdio.h>

const char p[3] = {225, 226, 227};
const char *s[3] = {"puto", "puta", "putas"};

typedef enum{FALSE, TRUE} boolean;

void convertir(const char [], const char *[]);

int main(void)
{
  convertir(p, s);
  return 0;
}

void convertir(const char arrCharset1[], const char *parrCharset2[])
{
  boolean Traducido;
  short i, c;
  for (i=0; i<3; i++) printf("|%c", arrCharset1[i]);
putchar('\n');
  while ((c = getchar())!=EOF)
  {
    Traducido = FALSE;
    fprintf(stderr,"c = %c|%d\n",c,c);
    for (i = 0; i < 3; i++)
    {
      if (c == (char)arrCharset1[i])
      {
        Traducido = TRUE;
        printf("%s", parrCharset2[i]);
        #ifdef DEBUG
	  fprintf(stderr, "traducido c = %c | %d----->%s\n", c, c, parrCharset2[i]);
	#endif
        break;
      }
      if (arrCharset1[i] == 225) printf("pase por 225, arr[i] = %c\n", arrCharset1[i]);
    }
    if (Traducido == FALSE) putchar(c);
  }
}
