/* SE PUEDE DEFINIR THD EN SETUP PARA GRAFICAR SOLO LA DISTORSION*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "setup.h"

#ifndef M_PI
#define M_PI 3.14159
#endif

int main(void)
{
  float v, ic, id, t;
  /*Imprimo datos y cabecera*/
  printf("TBJ_JFET  ");
  #ifdef THD
    puts("-THD");
  #else
    puts("");
  #endif
  printf("Vin = %.2f*sen(2*PI*%.1f*t)", AMPLITUD1, FRECUENCIA1);
  #ifdef BITONO
    printf(" + %.2f*sen(2*PI*%.1f*t)\n", AMPLITUD2, FRECUENCIA2);
  #else 
    puts("");
  #endif
  printf("Is = %-10.2eIdss = %.2f\n", IS, IDSS);
  printf("Vt = %-10.3fVp   = %.2f\n", VT, VP);
  puts("Tensiones de polarización");
  printf("Vbe = %.3f\nVgs = %.3f\n", VBE_POL, VGS_POL);
  printf("Resolución de ploteo = %.1f puntos por período\n\n", RESOLUCION);
  printf("%-8s\t%-8s\t%-8s\t%-8s\t\n", "t [s]", "Vin [V]", "Ic [mA]", "Id [mA]");
  
  /*Computo y salida*/
  for (t=0; t<=NMUESTRAS; t+=INCREMENTO)
  {
    v = AMPLITUD1*sin(2*M_PI*FRECUENCIA1*t) + AMPLITUD2*sin(2*M_PI*FRECUENCIA2*t);
    printf("% -5.6f\t% -5.6f\t", t, v);
    ic = IS*exp((v+VBE_POL)/VT);
    id = IDSS*(1-(v+VGS_POL)/VP)*(1-(v+VGS_POL)/VP);
    #ifdef THD
    {
      ic -= (v + VBE_POL);
      id -= (v + VGS_POL);
    }
    #endif
    printf("% -5.6f\t% -5.6f\n", ic, id);
  }
  fprintf(stderr,"Calculo de señal procesada por TBJ y JFET realizado con éxito\n");
  return EXIT_SUCCESS;
}
