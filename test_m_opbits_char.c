#include <stdio.h>
#include <assert.h>
#include "m_opbits_char.h"

int main(void) {
    char rep, rep1, rep2, rep3;
    char nombre = 10;

    rep = get_bit_char(nombre, 0);
    assert(rep == 0);

    rep1 = set_bit_char(nombre, 0);
    assert(rep1 == 11);

    rep2 = clear_bit_char(nombre, 1);
    assert(rep2 == 8);

    rep3 = flip_bit_char(nombre, 2);
    assert(rep3 == 14);

    voir_bits_char(rep3);




    return 0;
}