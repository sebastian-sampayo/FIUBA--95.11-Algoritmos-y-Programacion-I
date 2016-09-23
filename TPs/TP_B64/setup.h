/************* setup **************/
/* Modo DEBUG */
/*
#define DEBUG
*/

/* Command-Line Arguments */
#define ARGV_MODIFIER1 1
#define ARGV_MODIFIER1_STR "-from"
#define ARGV_MODIFIER2 3
#define ARGV_MODIFIER2_STR "-to"
#define ARGV_CHARSET1 2
#define ARGV_CHARSET1_STR "ascii"
#define ARGV_CHARSET2 4
#define ARGV_CHARSET2_STR "base64"

/* Diccionario base64. Maxíma cantidad de elementos en el diccionario */
#define MAX_B64_ITEMS 64
/* Impresion en base64. Cantidad máxima de caracteres por línea */
#define B64_LINE_LENGHT 76
/* Caracter utilizado para casos excepcionales */
#define B64_EXCEPTION_CHAR '='

/* Mensajes de error */
#define ERR_MSG_INVALID_COMMAND "Invalid arguments. See output for details."
#define ERR_MSG_CORRUPT_FILE "The input text is corrupt. Imposible to keep decoding."
/* Otros mensajes */
#define MSG_CORRECT_OPERATION "The input was translated successfuly!"

/* Setup para funciones encode/decode */
#define BUFFER_ASCII_BYTES_LENGHT 3
#define BUFFER_B64_BYTES_LENGHT 4
#define SHIFT_BYTE_ASCII 8
#define SHIFT_BYTE_B64 6
#define MASK_BYTE_ASCII 0xFF
#define MASK_BYTE_B64 0x3F

/* Funcion show_usage() */
#define PROGRAM_NAME "b64.exe"
#define CHARSETS     "ascii/base64"
#define MODES        "encoder/decoder"
#define MSG_CORRECT_USAGE       "In order to run this program correctly you must type:"
#define MSG_CLA_CORRECT_USAGE   ">/$ b64 <modifier1> <charset1> <modifier2> <charset2>"
#define MSG_MODIFIERS           "Modifiers must be '-from' and '-to', or '-to' and '-from'."
#define MSG_CHARSETS            "Charsets must be: 'ascii' and 'base64', or 'base64' and 'ascii'."
#define MSG_PIPING_USAGE        "Use piping for best results."
