//
// Created by Méo Charlet on 2025-11-09.
//



#ifndef DEVOIR2_M_OPBITS_CHAR_H
#define DEVOIR2_M_OPBITS_CHAR_H

#include <stdio.h>
#define BITS_CHAR  (sizeof(char) * 8)

typedef unsigned char uchar ;

char get_bit_char( uchar nombre, uchar ordre);

uchar set_bit_char( uchar nombre, uchar ordre);

uchar clear_bit_char( uchar nombre, uchar ordre);

uchar flip_bit_char( uchar nombre, uchar ordre);

void voir_bits_char(uchar nombre);


#endif //DEVOIR2_M_OPBITS_CHAR_H