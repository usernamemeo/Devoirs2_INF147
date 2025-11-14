//=========================================================
/*****************************************************/
/* usage  des fonctions offertes dans le module m_alea00
   dans les problemes de dés, de pile/face ou d'urne
 */
/*****************************************************/

#include "m_alea00.h"
/*=========================================================*/


/*=========================================================*/
// Définitions des fonctions offertes
/*=========================================================*/

/*=========================================================*/
double randf00(void) {
	// STRATEGIE
	// calcul du rapport de la valeur issue de rand au 
	// maximum emissible + epsilon  
	return (1.0 * rand()) / (RAND_MAX + EPSILON);
}

/*=========================================================*/
Uint randi00(Uint n) {
	// STRATEGIE
	// n * randf()) donne un réel dans (0,n-1)
	// le typecast (Uint) va le tronquer dans [0,n[
	//  ajouter 1  assure être dans [1,n]
	return  (1 + (Uint)(n * randf00()));
}

/*=========================================================*/
int randi00_born(int b1, int b2) {
	// STRATEGIE
	// dans l'intervalle abs(b1-b2)+1  = K valeurs atteignables
	// donc on a une bijection avec randi(K) puis 
	// translation pour retrouver la valeur 
	return(b1 < b2) ? (b1-1) +randi00((b2-b1)+1) : (b2-1) + randi00((b1 - b2)+1 );
}

/*=========================================================*/
double randf00_born(double b1, double b2) {
	// STRATEGIE
	// passer de l'intervalle réel (0,1) à l'intervalle désigné 
	// par les paramètres
	// maths :  une dilatation de (0,1) par le facteur(b2 - b1)
	// suivie d'une translation de b1
	return b1 + ((b2 - b1) * randf00());
}

/*=========================================================*/

/*=========================================================*/
void srand00_explicit(Uint seed) {
	// init le generateur du C du parametre
	srand(seed);
	//  par tradition il est suivi d'un premier appel au generateur
	rand();
}

/*=========================================================*/
Uint srand00_system(void) {
	unsigned int secondes ;
	// obtenir le décalage secondes (Unix timestamp)
	secondes = (unsigned int)time(NULL);
	// init le generateur, suivi par tradition  d'un premier appel 
	srand(secondes) , rand();
	return secondes;
}
/*=========================================================*/

/*=========================================================*/



/*=========================================================*/