#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MSJ_OPCIONES_INGRESO "Para operar una sola onda ingrese 1, para dos ingrese 0"
#define MSJ_INGRESE_FRECUENCIA1 "Ingrese frecuencia1:"
#define MSJ_INGRESE_AMPLITUD1 "Ingrese amplitud de la onda1:"
#define MSJ_INGRESE_FRECUENCIA2 "Ingrese frecuencia2:"
#define MSJ_INGRESE_AMPLITUD2 "Ingrese amplitud de la onda2:"
#define MSJ_INGRESE_RESOLUCION "Ingrese resolución (cantidad de puntos por período):"
#define MSJ_INGRESE_NPERIODOS "Ingrese cantidad de períodos a procesar:"
#define ERR_MSJ_
#ifndef M_PI
#define M_PI 3.14159
#endif

int main(void)
{
  float frecuencia1, frecuencia2, amplitud1, amplitud2, t, v, incremento;
  int resolucion, n_periodos;
 
  fprintf(stderr,MSJ_INGRESE_FRECUENCIA1);
  scanf("%f", &frecuencia1);
  fprintf(stderr,MSJ_INGRESE_AMPLITUD1);
  scanf("%f", &amplitud1);
  fprintf(stderr,MSJ_INGRESE_FRECUENCIA2);
  scanf("%f", &frecuencia2);
  fprintf(stderr,MSJ_INGRESE_AMPLITUD2);
  scanf("%f", &amplitud2);
  fprintf(stderr,MSJ_INGRESE_RESOLUCION);
  scanf("%d", &resolucion);
  fprintf(stderr,MSJ_INGRESE_NPERIODOS);
  scanf("%d", &n_periodos);
  fflush(stdout);
  puts("t       \tv");

  incremento = 1/(resolucion*fabs(frecuencia1-frecuencia2));
  for (t = 0; t <= (n_periodos/fabs(frecuencia1-frecuencia2)); t += incremento)
  {
    v = amplitud1*sin(2*M_PI*frecuencia1*t) + amplitud2*sin(2*M_PI*frecuencia2*t);
    printf("% -6f\t% -6f\n", t, v);
  }

  return EXIT_SUCCESS;
}
