#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MSJ_INGRESE_FRECUENCIA "Ingrese frecuencia:"
#define MSJ_INGRESE_AMPLITUD "Ingrese amplitud de la onda:"
#define MSJ_INGRESE_RESOLUCION "Ingrese resolución (cantidad de puntos por período):"
#define MSJ_INGRESE_NPERIODOS "Ingrese cantidad de períodos a procesar:"
#define ERR_MSJ_
#ifndef M_PI
#define M_PI 3.14159
#endif

int main(void)
{
  float frecuencia, amplitud, t, v, incremento;
  float resolucion, n_periodos;

  fprintf(stderr,MSJ_INGRESE_FRECUENCIA);
  scanf("%f", &frecuencia);
  fprintf(stderr,MSJ_INGRESE_AMPLITUD);
  scanf("%f", &amplitud);
  fprintf(stderr,MSJ_INGRESE_RESOLUCION);
  scanf("%f", &resolucion);
  fprintf(stderr,MSJ_INGRESE_NPERIODOS);
  scanf("%f", &n_periodos);
  fflush(stdout);
  puts("t       \tv");

  incremento = 1/(resolucion*frecuencia);
  for (t = 0; t <= (n_periodos/frecuencia); t += incremento)
  {
    v = amplitud*sin(2*M_PI*frecuencia*t);
    printf("% -6f\t% -6f\n", t, v);
  }

  return EXIT_SUCCESS;
}
