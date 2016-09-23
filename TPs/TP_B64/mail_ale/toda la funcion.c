/* TODO EL PROGRAMA */
#include <stdio.h>
#include <string.h>


void adaptar_la_cadena_para_que_sea_multiplo_de_3_bytes(char[]);
void traducion (char[]);
char[] lector_de_caracteres(*char);
void encoder(char[]);
void decoder(char[]);

int main (void) {





}




/*me baso fuertemente en el hecho de que cada caracter ascii ocupa un byte de 8bits*/
void adaptar_la_cadena_para_que_sea_multiplo_de_3_bytes(char character[]) {
    int x=0, y=0; /*x: modo; y: longitud de la cadena ingresada*/
    char *characterptr;
    characterptr =& character[0] /*este puntero esta al pedo, se puede usar character directamente*/
    y=strlen(*characterptr) /*usar sizeof*/
    x=y%3;
    /*aca hay un punto debil que es que estoy considerando que la posicion y, la posicion y+1, la posision y+2 son posiciones que pertenecen al mismo arreglo*/

    if(x==2) {
        *(characterptr+y)='NUL'; /*usar notacion de arreglos, y cambiar nuul por 'NUL'*/
        *(characterptr+y+1)='\0';
    }
    if (x==1) {
        *(characterptr+y)=nul;
        *(characterptr+y+1)=nul;
        *(characterptr+y+2)='\0';
    }
}


void traducion(char[]) {
    int i, c, k, j;
    /* va en archivo aparte*/
    char diccionario[64]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','+','/'};
    char base64[64];
    char **todiccionario_frombase64ptr, *tobase64ptr;

/*no hace falta usar c, no hace falta nada*/
    for(i=0; i<64; i++){
    c=0x00;
    base64[i]=c;
    c+=0x01;
    }
    /*corregir*/
    todiccionario_frombase64ptr =& base64&diccionario; /* no se si esta bien inicializado pero es un puntero doble a base64 y desde ahi a diccionario*/
    tobase64ptr=& base64;

    for(k=0; k<3, k++) {
        for(j=0; (encode[k])!=(*(tobase64ptr+j)) && j<64, j++);

        printf("%c", **(todiccionario_frombase64+j-1))
    }
return 0;
}



/*status_t*/
char[] lector_de_caracteres(*char, /*  *sentence*/) {
    int   j;
    char c, sentence[3]={0}; /*buffer*/

/* '\0' */
    for(j=0, c;(c=getchar())!= '\n' && j<3; j++, c)
        sentence[j]=c;

return sentence;
    }




/* encoder/decoder */
/*falta poner unsigned int, para que al desplazar pueda asegurar que se coloquen ceros en los lugares (no se donde se pone) */

#define CANTIDAD_DE_BYTES_DE_8BITS 3
#define SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA 8
#define SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA 8
#define CANTIDAD_DE_BYTES_DE_6BITS 4
#define SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA 6
#define SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA 6
#define MASK_READ_6_BITS 0x3F

/*character hay que declararlo adnetoro o tomarlo de alguna lado*/
void encoder(char[]) {
    char encode[4]; /*buffer*/
    /*i, j : short;;; bytethree: uchar*/
    int i, j, bytethree=0;/*otro buffer*/

    for(i=0, j=CANTIDAD_DE_BYTES_DE_8BITS-1; i<=CANTIDAD_DE_BYTES_DE_8BITS-1, j>=0; i++, j--)
        bytethree+= character[i]<<(j*SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA); /*aca no se si lo que esta dentro de character se sumara como hexadecimal, o si hay que hacer algo primero para expresarlo en hexadecimal*/

    for(i=CANTIDAD_DE_BYTES_DE_6BITS-1, j=0; i>=0, j<=CANTIDAD_DE_BYTES_DE_6BITS-1; i--, j++) {
        encode[i]=((bytethree>>(j*SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA))&MASK_READ_6_BITS);
 /*---esto no---*/
        if(encode[i]==nul) /* esto lo agrego para decir que si llega a aparecer un 0 de hexa, que lo reemplace por un '=' */
            encode[i]='=';
 /*-------------*/
    }
}

void decoder(char[]) {
    char decode[3]
    int i, j, bytethree=0;

    for(i=0, j=CANTIDAD_DE_BYTES_DE_6BITS-1; i<=CANTIDAD_DE_BYTES_DE_6BITS-1, j>=0; i++, j--)
        bytethree+= character[i]<<(j*SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA); /*aca no se si lo que esta dentro de character se sumara como hexadecimal, o si hay que hacer algo primero para expresarlo en hexadecimal*/

    for(i=CANTIDAD_DE_BYTES_DE_6BITS-1, j=0; i>=0, j<=CANTIDAD_DE_BYTES_DE_8BITS-1; i--, j++) {
        decode[i]=((bytethree>>(j*SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA))&MASK_READ_6_BITS);
        if(decode[i]=='=')
        decode[i]=nul;
    }
}
