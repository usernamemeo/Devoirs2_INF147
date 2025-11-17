/*=========================================================*/
/*		par husiro du SEG  1996 */
/*=========================================================*/
/*	

	Module qui offre l'usage de chronomètres capables de
	mesurer différents temps d'exécution dans un programme.

	ils donnent un critere important pour le choix d'une parmi plusieurs 
 	versions algorithmiques en compétition

*/

/*
	Le client possède la panoplie de fonctions nécessaires à un 
	maniement simple de tels objets
	tout ou presque de l'interface est naturelle avec les fonctions
	init_ , start_ , stop_ , reset_ , get_ , free_

	qui assurent informations et modifications de l'état d'un tel chronomètre 
*/

/*  
	Ces chronomètres ont  une précision  estimée minimalement
	au quarantième de seconde sur des plateformes comtemporaines
	Ne pensez pas les utiliser pour controler du temps réel machine 
	à moins que les contraintes de réponse  du programme ne soient 
	suffisamment larges.
*/

/*
	interressant peut-être, mais loin d'être essentiel
	vous pouvez négliger cette partie et sa fonction  toc

	Une vraie particularité de ces chronomètres, c'est de pouvoir
	donner des temps relatifs à certaines actions sur un chronometre

	la fonction toc_ retourne le temps passé depuis la dernière
	intervention significative sur ce chronomètre après  un init_,
	un start_, un reset_, un stop_ , un get_
	Mais les méthodes toc_ et get_etat ne sont pas prises en compte
*/
/*=========================================================*/
/*=========================================================*/

#ifndef  __MODUL_CHRONOS_1780325__
#define  __MODUL_CHRONOS_1780325__

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<time.h>

/*=========================================================*/



/*---------------------------------------------------*/
/* LA RÈGLE DE BASE D'USAGE DES CHRONOMÈTRES */
/* Voici le type du lien (dire handle) d'une variable du client pour 
   conserver l'objet donné  par le constructeur init_chrono */

/* la valeur d'un t_chrono doit être conservée intacte par le client puisqu'elle 
   est nécessaire à toute action ultérieure voulue sur le chronometre 
   jusqu'à  sa libération explicite avec la fonction free_chrono
*/

typedef  struct chrono*  t_chrono ;

/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/* constructeur , retourne le handle d'un nouveau chronometre  

	PARAMETRES  :  rien
	SORTIE  : : le handle  d'un nouveau chrono
	SPÉCIFICATIONS :
	   construit un chronomètre  neuf arrêté
	   retourne la constante symbolique NULL si échec (reste peu probable)
*/
t_chrono init_chrono(void);
/*-----------------------------------------------------*/

/*---------------------------------------------------*/
/* démarre le chronomètre,  le temps cumulé à date est conservé

	PARAMETRES  :   un  handle valide sur un chrono
	SORTIE  : : rien
	SPÉCIFICATIONS :
	   le comportement est imprévisible si le paramètre
	   effectif n'est pas un handle correct obtenu d'init_chrono
*/
void start_chrono(t_chrono);

/*-----------------------------------------------------*/
/*---------------------------------------------------*/
/* arrête le chronomètre  et le temps cumulé à date est conservé 

	PARAMETRES  :   un  handle valide sur un chrono
	SORTIE  : : rien
	SPÉCIFICATIONS :
	   le comportement est imprévisible si le paramètre
	   effectif n'est pas un handle correct obtenu d'init_chrono
*/
void stop_chrono(t_chrono);

/*-----------------------------------------------------*/
/*---------------------------------------------------*/
/* le temps cumulé est remis à 0 */
/* elle n'influence pas la marche du chronomètre */
/*
	PARAMETRES  :   un  handle  valide sur un chrono
	SORTIE  : : rien
	SPÉCIFICATIONS :
	   le comportement est imprévisible si le paramètre
	   effectif n'est pas un handle correct obtenu d'init_chrono
*/
void reset_chrono(t_chrono);

/*-----------------------------------------------------*/
/*---------------------------------------------------*/
/* retourne le temps cumulé à date */
/* elle n'influence pas la marche du chronomètre */
/*
	PARAMETRES  :   un  handle valide sur un chrono
	SORTIE  : : un réel qui donne le temps en secondes
	SPÉCIFICATIONS :
	   le comportement est imprévisible si le paramètre
	   effectif n'est pas un handle correct obtenu d'init_chrono
*/
double get_chrono(t_chrono); 

/*-----------------------------------------------------*/

/*---------------------------------------------------*/
/* retourne 1 s'il fonctionne et 0 sinon   */
/*
	PARAMETRES  :   un  handle valide sur un chrono
	SORTIE  : : 1 s'il fonctionne et 0 sinon
	SPÉCIFICATIONS :
       elle ne  fait PAS partie du groupe considéré par toc_chrono
	   le comportement est imprévisible si le paramètre
	   effectif n'est pas un handle correct obtenu d'init_chrono
*/
int get_etat(t_chrono);

/*---------------------------------------------------*/

/*-----------------------------------------------------*/
/* destructeur,  libère le système du chronomètre */
/* cette valeur du handle ne DOIT PLUS  être utilisée */
/*
PARAMETRES  :   un  handle valide sur un chrono
SORTIE  : : rien
SPÉCIFICATIONS :
son comportement est imprévisible si le paramètre
effectif n'est pas un handle correct obtenu d'init_chrono
*/
void free_chrono(t_chrono);

/*---------------------------------------------------*/

#endif
/*---------------------------------------------------*/
