/* ////////////////// main.c ///////////////////*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setup.h"
#include "base64.h"
#include "types.h"

typedef enum {ENCODE, DECODE} mode_t;

/***************************PROTOTIPOS***************************/
status_t Set_Mode (int , char *[]);
/****************************************************************/

mode_t mode;
status_t status=OK;

int main(int argc, char *argv[])
{
   short i, j, chars_wrote = 0;
   char c, buffer_ascii[BUFFER_ASCII_BYTES_LENGTH], buffer_b64[BUFFER_B64_BYTES_LENGTH];

   if (Set_Mode(argc, argv) != OK) return ERR_ARGUMENTS;

   if (mode == ENCODE)
   {
      while(1)
      {
         for (i=0; i<BUFFER_ASCII_BYTES_LENGTH; i++)
         {
            if ((c=getchar())==EOF) break;
            buffer_ascii[i] = c;
         }
         if (i==0) break;

         if (i == BUFFER_ASCII_BYTES_LENGTH) /* Modo normal */
         {
            encode_normal(buffer_ascii, buffer_b64);
            for(j=0; j<BUFFER_B64_BYTES_LENGTH; j++)
               putchar(dictionary_b64[(int)buffer_b64[j]]);
            /* cada linea no debe contener mas de 76 caracteres */
            chars_wrote += BUFFER_B64_BYTES_LENGTH;
            if (chars_wrote == B64_LINE_LENGTH) 
            {
               putchar(NEW_LINE_CHAR);
               chars_wrote = 0;
            }
         }

         if (i == BUFFER_ASCII_BYTES_LENGTH-2) /*EXCEPTION1*/
         {
            encode_exception1(buffer_ascii, buffer_b64);
            for(j=0; j<BUFFER_B64_BYTES_LENGTH-2; j++)
               putchar(dictionary_b64[(int)buffer_b64[j]]);
            putchar(B64_EXCEPTION_CHAR);
            putchar(B64_EXCEPTION_CHAR);
         }

         if (i == BUFFER_ASCII_BYTES_LENGTH-1) /*EXCEPTION2*/
         {
            encode_exception2(buffer_ascii, buffer_b64);
            for(j=0; j<BUFFER_B64_BYTES_LENGTH-1; j++)
               putchar(dictionary_b64[(int)buffer_b64[j]]);
            putchar(B64_EXCEPTION_CHAR);
         }
      }
   }
	
   if (mode == DECODE)
   {
      while(1)
      {
         for (i=0; i<BUFFER_B64_BYTES_LENGTH; i++)
         {
            if ((c=getchar())==EOF) break;
            if (c == NEW_LINE_CHAR) 
               {status = NEW_LINE_B64_STATUS; break;}
            else status = OK;
            buffer_b64[i] = c;
         }
         if (status == NEW_LINE_B64_STATUS) continue;
         if (i == 0) break;
         if (i != BUFFER_B64_BYTES_LENGTH) return ERR_INPUT;
         if ((status = decode(buffer_b64, buffer_ascii)) != OK) return status;

         for (j=0; j<BUFFER_B64_BYTES_LENGTH; j++)
         {
            if (buffer_ascii[j] == 0) break;
            putchar(buffer_ascii[j]);
         }
      }
   }

   return EXIT_SUCCESS;
}

status_t Set_Mode (int argc, char *argv[])
{
   short i;

   if (argc != NUMBER_OF_ARGUMENTS) return ERROR;

   for (i=0; i<NUMBER_OF_ARGUMENTS; i++)
      if (!strcmp(argv[i], ARGV_MODIFIER_FROM_STRING)) break;

   if (i == NUMBER_OF_ARGUMENTS || argv[i+1]==NULL) return ERROR;

   if (!strcmp(argv[i+1], ARGV_ASCII_STRING)) mode = ENCODE;
   else if (!strcmp(argv[i+1], ARGV_B64_STRING)) mode = DECODE;
   else return ERROR;

   
   for (i=0; i<NUMBER_OF_ARGUMENTS; i++)
      if (!strcmp(argv[i], ARGV_MODIFIER_TO_STRING)) break;

   if (i == NUMBER_OF_ARGUMENTS || argv[i+1]==NULL) return ERROR;

   if (mode == ENCODE && !strcmp(argv[i+1], ARGV_ASCII_STRING)) return ERROR;
   if (mode == DECODE && !strcmp(argv[i+1], ARGV_B64_STRING)) return ERROR;
   if (strcmp(argv[i+1], ARGV_B64_STRING) && strcmp(argv[i+1], ARGV_ASCII_STRING)) return ERROR;

   
   return OK;
}
