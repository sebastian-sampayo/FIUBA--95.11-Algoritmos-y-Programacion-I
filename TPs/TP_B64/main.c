/* 
*/
#include <stdio.h>
#include <stdlib.h>
#include "setup.h"
#include "dictionaryB64.h"
#include "typedefs.h"

/***************************PROTOTIPOS***************************/
status_t validate_cla(int, char *[]);
mode_t select_mode(char *[]);
size_t readXchars(char [], size_t );
status_t check_reading (const char [], const char [], short );
void link_ascii_b64 (const char [], char [], char []);
void decode(const char [], char []);
void encode_normal(const char [], char []);
void encode_exception1(const char [], char []);
void encode_exception2(const char [], char []);
void printXascii(const char [], size_t );
void printXbase64(const char [], size_t , const char []);
void show_usage(void);
/****************************************************************/

status_t status;

int main(int argc, char *argv[])
{
	short number_of_chars_read, chars_wrote = 0;
	char buffer_ascii[3];
	char buffer_b64[4];
  mode_t mode;

	if (validate_cla(argc, argv) != OK)
	{
    fprintf(stderr,"%s\n", ERR_MSG_INVALID_COMMAND);
		show_usage();
		return EXIT_SUCCESS;
	}
	mode = select_mode(argv);
	if (mode == ENCODE)
	{
		while(1)
		{
			number_of_chars_read = readXchars(buffer_ascii, 3);

			if (number_of_chars_read==0) /*END OF FILE*/
			{
				status = END;
				break;
			}
			if (number_of_chars_read==3) /*NORMAL_WORKING*/
      {
				encode_normal(buffer_ascii, buffer_b64);
        printXbase64(buffer_b64, 4, dictionary_b64);
  			chars_wrote++;
  			if (chars_wrote == B64_LINE_LENGHT/4) 
  			{
  				putchar('\n');
  				chars_wrote = 0;
  			}
      }

			if (number_of_chars_read==1) /*EXCEPTION1*/
      {
				encode_exception1(buffer_ascii, buffer_b64);
        printXbase64(buffer_b64, 2, dictionary_b64);
        putchar(B64_EXCEPTION_CHAR);
        putchar(B64_EXCEPTION_CHAR);
      }

			if (number_of_chars_read==2) /*EXCEPTION2*/
      {
				encode_exception2(buffer_ascii, buffer_b64);
        printXbase64(buffer_b64, 3, dictionary_b64);
        putchar(B64_EXCEPTION_CHAR);
			}
		}		
	}
	
	if (mode == DECODE)
	{
		while(1)
		{
      #ifdef DEBUG
        if (status == NEW_LINE)
        {
          fprintf(stderr,"NEW_LINE\nbuffer_b64[1] = %c | buffer_b64[2] = %c | buffer_b64[3] = %c\n",
                                    buffer_b64[1],buffer_b64[2],buffer_b64[3]);
        }
      #endif
			number_of_chars_read = readXchars(buffer_b64, 4);
			status = check_reading(dictionary_b64, buffer_b64, number_of_chars_read);
      if (status == NEW_LINE) continue;
			if (status == ERROR) break;
			if (status == END) break;
      link_ascii_b64(dictionary_b64, buffer_b64, buffer_b64);
			decode(buffer_b64, buffer_ascii);
			printXascii(buffer_ascii, 3);
		}
	}
  if (status == ERROR) 
  {
    fprintf(stderr,"%s\n",ERR_MSG_CORRUPT_FILE);
    return EXIT_FAILURE;
  } else fprintf(stderr,"%s\n", MSG_CORRECT_OPERATION);
  
	return EXIT_SUCCESS;
}
