//
// Created by Méo Charlet and Martin Coudret on 2025-11-09. Inspired by Hugues Saulnier
//

#include "m_opbits_char.h"

char get_bit_char( uchar nombre, uchar ordre) {
    return (!(ordre < BITS_CHAR)) ? 0 : (nombre & (1 << ordre)) != 0;
}

uchar set_bit_char( uchar nombre, uchar ordre) {
    return (!(ordre < BITS_CHAR)) ? nombre : (nombre | (1 << ordre));
}

uchar clear_bit_char( uchar nombre, uchar ordre) {
    return (!(ordre < BITS_CHAR)) ? nombre : (nombre & (~(1<<ordre)));

}

uchar flip_bit_char( uchar nombre, uchar ordre) {
    return (!(ordre < BITS_CHAR)) ? nombre :
         get_bit_char(nombre, ordre) ? clear_bit_char(nombre, ordre) :
         set_bit_char(nombre, ordre);

}

void voir_bits_char(uchar nombre) {
    char i;
    for(i = BITS_CHAR - 1; i > -1; i-=1)
        printf("%d", get_bit_char(nombre,i));

}
