/*=========================================================*/
/*		par husiro du SEG  1996 */
/*=========================================================*/

/*  implémentation du module offrant ces chronomètres 
    de temps d'exécution
*/
/*=========================================================*/
#include "m_chronos.h"
/*=========================================================*/

/*=========================================================*/
/*		DEFINITION DE LA STRUCTURE PRIVÉE			*/
/*      REPRÉSENTANTE DE L'ÉTAT D'UN CHRONOMÈTRE    */

struct chrono{

    /* GARDERA LE TEMPS CUMULÉ JUSQU'À DATE EN TICK */
	double tick_cumul;

	/* GARDERA LA MARQUE TEMPORELLE DE LA DERNIÈRE */
	/* ACTION init,start,stop, reset , get  EN TICK */
	double tick_action; 

	/* LE CHRONO FONCTIONNE OU NON */
	int on_off_ ;
};

/*---------------------------------------------------*/
/* STRATÉGIE
	on assure un suivi au malloc : 
	champs  tick_action, cumul et marche à 0
*/
struct chrono* init_chrono(void){
	
	struct chrono* lui = malloc( sizeof(struct chrono));

	/* si on a obtenu de la mémoire */
	if (lui != NULL){
	
		lui-> tick_cumul = 0;	
		lui->tick_cumul = 0;
		lui-> on_off_ = 0;
	}
	return lui ;	
}
/*-----------------------------------------------------*/
/* STRATÉGIE
	  on libère le struc obtenu en  allocation programmée 
*/
void free_chrono (struct chrono* lui){ 
	if(lui) free(lui); 
}
/*-----------------------------------------------------*/
/* STRATÉGIE  
    le champs on_off_ vaudra  1
	s il fonctionne déjà, on ajoute le temps
*/
void start_chrono (struct chrono* lui){ 
	/*s'il marche déjà, on cumule le temps */
	if (lui->on_off_ ){
		lui->tick_cumul += (clock() - lui->tick_action);
	}
	/*   on conserve le nouveau départ */
	lui->tick_action = clock();
	/* il est en marche */
	lui->on_off_ =  1;
}
/*---------------------------------------------------*/
/* STRATÉGIE  
    le champs on_off_ vaudra  0
	s il marche, on ajoute le temps, 
	on garde ce temps d'action  pour toc
*/

/*on l'arrête, les commentaires sont identiques à la précédente  */
void stop_chrono (struct chrono* lui){ 
	if (lui->on_off_ ){
		lui->tick_cumul += (clock() - lui->tick_action);
	}
	lui->tick_action = 0;
	lui->on_off_ = 0;
}
/*---------------------------------------------------*/
/* STRATÉGIE 
      le temps cumulé est mis à 0
	  on garde le temps d'action pour toc 
*/
void reset_chrono(struct chrono* lui){
	lui->tick_cumul = 0;
	if (lui->on_off_) {
		lui->tick_action = clock(); 
	}
}
/*---------------------------------------------------*/
/* STRATÉGIE  	
	s il marche, on ajoute le temps, on garde ce temps d'action  
	on retourne le temps cumulé en secondes 
*/
double get_chrono(struct chrono* lui){ 
	if (lui->on_off_ ){
		double t = clock();
		lui->tick_cumul += (t - lui->tick_action);
		lui->tick_action = t;
	}
	
	/* on retourne le temps cumulé    */
	return (lui->tick_cumul /CLOCKS_PER_SEC);
}
/*---------------------------------------------------*/

/*---------------------------------------------------*/
/* STRATÉGIE
	retourne le champ on_off_
*/
int get_etat( struct chrono* lui){ 
	return lui->on_off_  ;
}
/*---------------------------------------------------*/
/* fin de l'implémentation*/
/*---------------------------------------------------*/