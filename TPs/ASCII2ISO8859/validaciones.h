/**********PROTOTIPOS*************/
status_t validar_nitems(short [], const char *[], short *); /*valida y almacena la cantidad de items por puntero*/
status_t validar_argc(short , short);
status_t validar_argv(char *[], short, char *);

status_t validar_nitems(short arrCharset1[], const char *parrCharset2[], short *pitems)
{
  short i;
  
  for (i=0; arrCharset1[i]!=NUL && parrCharset2[i]!=NULL; i++);
  if (arrCharset1[i]==NUL && parrCharset2[i]==NULL)
  {
    *pitems = i;
    return OK;
  }
  else
    return ERR_NITEMS;
}

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
