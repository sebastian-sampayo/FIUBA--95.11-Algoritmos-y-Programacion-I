/*setup*/
#define THD
#define MONOTONO
/*Tension de entrada*/ /*UNIDADES V y mA*/
#define FRECUENCIA1 1000.0
#define AMPLITUD1 0.05
#ifdef BITONO
  #define FRECUENCIA2 1200.0
  #define AMPLITUD2 0.04
#else
  #define FRECUENCIA2 0
  #define AMPLITUD2 0
#endif
#define VBE_POL 0.7
#define VGS_POL -0.6
/*CONSTANTES*/
/*TBJ*/
#define IS 1e-11
#define VT 0.026
/*JFET*/
#define IDSS 2.0
#define VP -2.0
/*FORMATO DE SALIDA*/
#define RESOLUCION 400.0
#define NPERIODOS 4.0
#define INCREMENTO 1.0/(RESOLUCION*fabs(FRECUENCIA1-FRECUENCIA2))
#define NMUESTRAS ((float)NPERIODOS/((float)fabs(FRECUENCIA1-FRECUENCIA2)))
