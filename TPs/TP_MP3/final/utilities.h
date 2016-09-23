#ifndef UTILITIES__H
#define UTILITIES__H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include <string.h>

#define DEBUG
#define LOG_FILE "log.log"

/********* PROTOTIPOS UTILIDADES *********/
status_t strdup(string *, const string );
status_t my_strcat(string *, string );
void logmsg(string );
void logstr(string , string);
void logint(string , int );
/*****************************************/

#endif
