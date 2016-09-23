#include <stdio.h>
#include <string.h>
#include "setup.h"
#include "status.h"

status_t validar_argc(short argc, short args)
{
  if (argc != args)
  {
    puts(ERR_ARGC_MSJ);
    puts(MSJ_USO_CORRECTO);
    return ERR_ARGC;
  } else return OK;
}

status_t validar_argv(char *argv[], short narg, char *argumento)
{
  if (strcmp(argv[narg], argumento))
    return ERR_ARGV;
  else return OK;
}
