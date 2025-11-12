
/*****************************************************/
/* implémentation des fonctions offertes dans op_bits.h */
/* toutes sont simples et basées sur les bitwise operators du C */
/*****************************************************/

#include "m_opbits_int.h"


/*****************************************************/
/*		DEFINITIONS DES FONCTIONS				*/
/*****************************************************/
/*****************************************************/
/* STRATÉGIE
    tester si ordre est valide
	PUIS tester si le (bitwise and) entre nombre
	et un train de bits tout à 0 sauf un 1 à ordre voulu, 
	(1 << ordre), est différent de 0	
*/
 int get_bit_int(uint nombre, uint ordre){
	 return (!(ordre < BITS_INT)) ? 0 : (nombre & (1 << ordre)) != 0;
}

/*****************************************************/
/* STRATÉGIE 
    tester si ordre est valide
	PUIS un (bitwise or)  entre la valeur recue et un train de bits 
	tout à 0 sauf un 1 à ordre voulu,donne la valeur
*/
 uint set_bit_int(uint nombre, uint ordre){
	 return (!(ordre < BITS_INT)) ? nombre : (nombre | (1 << ordre));
}

/*****************************************************/
/* STRATÉGIE 
    tester si ordre est valide
	PUIS un (bitwise and)  entre la valeur recue et un train de bits 
	tout à 1 sauf un 0 à ordre voulu, usage de l'opérateur ~
*/
 uint clear_bit_int(uint nombre, uint ordre){
	return (!(ordre < BITS_INT)) ? nombre : (nombre & (~(1<<ordre)));
}

/*****************************************************/
/* STRATÉGIE , réutilisation des trois précédentes
    tester si ordre est valide
	Puis on obtient l'état du bit ordre voulu 
	si 1, appel de clear	
	sinon appel de set
*/
 uint flip_bit_int(uint  nombre, uint ordre){	
	 return (!(ordre < BITS_INT)) ? nombre :
		 get_bit_int(nombre, ordre) ? clear_bit_int(nombre, ordre) :
		 set_bit_int(nombre, ordre);
}
 
/*****************************************************/
/* STRATÉGIE  réutilisation
	on affiche BITS_INT fois le résultat obtenu
	du get_bit pour chaque position.
*/
 void voir_bits_int( uint nombre){
	int i;
	for(i = BITS_INT - 1; i > -1; i-=1)
		printf("%d", get_bit_int(nombre,i));
}

/*****************************************************/
/*****************************************************/

