#include <stdio.h>
#include "setup.h"

extern const char dictionary_b64[];

/******************PROTOTIPOS******************
void printXascii(const char [], size_t );
void printXbase64(const char [], size_t , const char []);
void show_usage(void);
*/

/* Imprime de a x caracteres ascii. Si encuentra el caracter NUL corta.
   void printXascii(const char buffer[], size_t x) */
void printXascii(const char buffer[], size_t x)
{
  short i;

  for (i=0; i<x; i++)
  {
    if (buffer[i]== 0) break;
    putchar(buffer[i]);
  }
}

/* Imprime de a x caracteres en base64. */
void printXbase64(const char buffer[], size_t x, const char dictionary_b64[])
{
  size_t i;
  
  for(i=0; i<x; i++)
    putchar(dictionary_b64[(int)buffer[i]]);
}

/*    Muestra modo correcto de funcionamiento:
************** b64.exe	base64/ascii	encoder/decoder **************

In order to run this program correctly you must type:
>/$ b64 <modifier1> <charset1> <modifier2> <charset2>

Modifiers must be "-from" and "-to", or "-to" and "-from".
Charsets must be: "ascii" and "base64", or "base64" and "ascii".

Use piping for best results.

*********************************************************************
ver setup.h */
void show_usage(void)
{
	printf("%s %s  %s  %s %s\n\n","**************", PROGRAM_NAME, CHARSETS, MODES, "***************");
	puts(MSG_CORRECT_USAGE);
	puts(MSG_CLA_CORRECT_USAGE);
	putchar('\n');
	puts(MSG_MODIFIERS);
	puts(MSG_CHARSETS);
	putchar('\n');
	puts(MSG_PIPING_USAGE);
	puts("\n*********************************************************************\n");
}
