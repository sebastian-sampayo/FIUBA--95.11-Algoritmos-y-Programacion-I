#include <stdio.h>


#define MP3_HEADER_SIZE 128



#define LEXEM_START_TAG     0
#define LEXEM_SPAN_TAG      3

#define LEXEM_START_TITLE   3
#define LEXEM_SPAN_TITLE   30

#define LEXEM_START_ARTIST 33
#define LEXEM_SPAN_ARTIST  30

#define LEXEM_START_ALBUM  63
#define LEXEM_SPAN_ALBUM   30

#define LEXEM_START_YEAR   93
#define LEXEM_SPAN_YEAR     4

#define LEXEM_START_COMMENT 97
#define LEXEM_SPAN_COMMENT  30

#define LEXEM_START_GENRE  127
#define LEXEM_SPAN_GENRE     1




void show_header (char header[]);

int main (void)
{
    FILE *f;
    int i;
    char c;
    char *str1 = "mysong.mp3";
    char *str2 = "lieder.txt";
    int pos;
long cur_pos, length;
    char header[MP3_HEADER_SIZE];



    if ((f = fopen("paparulo.mp3","rb")) == NULL) {
        fprintf(stderr,"No se pudo abrir el archivo\n.");
        return 1;
    }
//    pos = fseek(f,0,SEEK_END);
//    fseek(f,-1,SEEK_CUR);
//        fread(&c,sizeof(char),1,f);
//        putchar(c);
/*
    for (i = 0; 1<127;i++) {
        fread(&c,sizeof(char),1,f);
        putchar(c);
    }
*/

    cur_pos = ftell(f);
    fseek(f, 0, SEEK_END); // set pointer to end of file
    length=ftell(f); // offset in bytes from file's beginning
    fseek(f, cur_pos, SEEK_SET); // restore original position
    printf("%s%li\n","longitud de archivo:", length);

    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);
    fread(header,sizeof(char),MP3_HEADER_SIZE,f);
    show_header(header);





    fclose(f);
    return 0;
}





void show_header (char header[])
{
    char buf[MP3_HEADER_SIZE];

    memcpy(buf,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    buf[LEXEM_SPAN_TAG] = '\0';
    printf("%s%s\n","tag:",buf);

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    printf("%s%s\n","title:",buf);

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    printf("%s%s\n","artist:",buf);

    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    printf("%s%s\n","album:",buf);

    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    printf("%s%s\n","year:",buf);

    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    printf("%s%s\n","comment:",buf);

    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    buf[LEXEM_SPAN_GENRE] = '\0';
    printf("%s%s\n","genre:",buf);

}






















