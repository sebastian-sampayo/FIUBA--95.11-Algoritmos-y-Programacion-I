/* Funciones referidas a CLA */
#include <stdio.h>
#include <string.h>
#include "typedefs.h"
#include "setup.h"

/***PROTOTIPOS***
status_t validate_cla(const int, const char *[]);
mode_t select_mode(const char *[]);
*/

status_t strings_pair_cmp(string, string, string, string);

status_t validate_cla(int argc, char *argv[])
{
  if (argc!=5) return ERROR;
  
  if (strings_pair_cmp(argv[ARGV_MODIFIER1], argv[ARGV_MODIFIER2], ARGV_MODIFIER1_STR, ARGV_MODIFIER2_STR)==ERROR)
    return ERROR; /* Error en los modificadores */
  
  if (strings_pair_cmp(argv[ARGV_CHARSET1], argv[ARGV_CHARSET2], ARGV_CHARSET1_STR, ARGV_CHARSET2_STR)==ERROR)
    return ERROR; /* Error en los juegos de caracteres*/

  return OK;
}

/* status_t string_pair_cmp(const string s1, const string s2, const string t1, const string t2)
   Recibe 1 par de cadenas s1 y s2 y las compara con el par t1, t2.
   Devuelve OK si: s1 = t1 ^ s2 = t2
           o bien: s1 = t2 ^ s2 = t1
   Sino devuelve ERROR. */
status_t strings_pair_cmp(string s1, string s2, string t1, string t2)
{
  if (strcmp(s1, t1))
  {
    if (strcmp(s1, t2))
			return ERROR;
		if (strcmp(s2, t1))
			return ERROR;
	} else if (strcmp(s2, t2))
			return ERROR;
	
	return OK; /* Si llega hasta acá es válido */
}

mode_t select_mode(char *argv[])
{
	if (!strcmp(argv[ARGV_MODIFIER1], ARGV_MODIFIER1_STR))
	{
		if (!strcmp(argv[ARGV_CHARSET1], ARGV_CHARSET1_STR))
			return ENCODE;
		else return DECODE;
	}else
		{
			if (!strcmp(argv[ARGV_CHARSET1], ARGV_CHARSET1_STR))
				return DECODE;
			else return ENCODE;
		}
}
