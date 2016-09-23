#include <stdio.h>

const char p = 225;

int main(void)
{
  char c;
  c = getchar();
  printf("225 = %c\tc = %c\n", 225, c);
  if (c==(char)p)
  puts("asd");
  return 0;
}
