/* encoder/decoder */
/*falta poner unsigned int, para que al desplazar pueda asegurar que se coloquen ceros en los lugares (no se donde se pone) */

#define CANTIDAD_DE_BYTES_DE_8BITS 3
#define SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA 8
#define SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA 8
#define CANTIDAD_DE_BYTES_DE_6BITS 4
#define SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA 6
#define SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA 6
#define MASK_READ_8BITS 0xFF
#define MASK_READ_6BITS 0x3F

void encoder_exception (char encode[], int x) {
    char encode[4];
    int i, j, bytethree=0;

    if(x) {
        for(i=0, j=CANTIDAD_DE_BYTES_DE_8BITS-1; i<=CANTIDAD_DE_BYTES_DE_8BITS-1, j>=0; i++, j--)
            bytethree+= character[i]<<(j*SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA); /*aca no se si lo que esta dentro de character se sumara como hexadecimal, o si hay que hacer algo primero para expresarlo en hexadecimal*/

        for(i=CANTIDAD_DE_BYTES_DE_6BITS-1, j=0; i>=0, j<=CANTIDAD_DE_BYTES_DE_6BITS-1; i--, j++) {
            encode[i]=((bytethree>>(j*SHIFT_ENCODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA))&MASK_READ_6BITS);
        }
    }

    if(x==1) {
        encode[3]='=';
        encode[2]='=';

        bytethree= character[0]<<4); /*aca no se si lo que esta dentro de character se sumara como hexadecimal, o si hay que hacer algo primero para expresarlo en hexadecimal*/

        encode[1]= bytethree&MASK_READ_6BITS;
        encode[0]= (bytethree>>6)&MASK_READ_6BITS;
    }

    if(x==2) {
        encode[3]= '=';
        bytethree= character[0]<<10;
        bytethree+= character[1]<<2

        encode[2]= bytethree&MASK_READ_6BITS;
        encode[1]= (bytethree>>6)&MASK_READ_6_BITS;
        encode[0]= (bytethree>>12)&MASK_READ_6BITS;
    }
}


void decoder(char[]) {
    char decode[3]
    int i, j, bytethree=0;

    for(i=0, j=CANTIDAD_DE_BYTES_DE_6BITS-1; i<=CANTIDAD_DE_BYTES_DE_6BITS-1, j>=0; i++, j--)
        bytethree+= character[i]<<(j*SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_IZQUIERDA); /*aca no se si lo que esta dentro de character se sumara como hexadecimal, o si hay que hacer algo primero para expresarlo en hexadecimal*/

    for(i=CANTIDAD_DE_BYTES_DE_6BITS-1, j=0; i>=0, j<=CANTIDAD_DE_BYTES_DE_8BITS-1; i--, j++) {
        decode[i]=((bytethree>>(j*SHIFT_DECODER_CANTIDAD_DE_BITS_A_DESPLAZAR_A_DERECHA))&MASK_READ_8BITS);
        if(decode[i]=='=')
        decode[i]=nul;
    }
}
