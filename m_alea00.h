//=========================================================
// 	hs pour nos étudiants en C
// 
//   le module offre la génération  de nombres aléatoires dans 
//   deux distributions  uniformes principales
// 
// /**********************************************************/
//=========================================================

#ifndef  __M_ALEA0058713__
#define  __M_ALEA0058713__
/*=========================================================*/
/* la constante qui permet de désactiver certains 
	warnings achalants de Visual
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>
/*=========================================================*/

// symbole   usuel pour le type de base unsigned int
typedef unsigned int Uint;

/*=========================================================*/
/*=========================================================*/
/* LES CONSTANTES */
/*=========================================================*/
// uniquement ce petit bonhomme bien connu en maths 
// c'est même un ami de  Shrek, alors respect
// je m'en sers pour assurer les distributions
#define EPSILON (0.0000000001)

/*=========================================================*/

/*=========================================================*/
/*
	six fonctions offertes pour réaliser certains 
	exercices ou devoirs qui ont besoin d'un générateur 
	de nombres  pseudo-aléatoires

	Avant de savoir utiliser un  generateur plus élaboré 
	je vous offre ces quelques fonctions qui interfacent le générateur du C 
	connu pour sa pauvre interface et ses deux fonctions rand et srand 
	pauvreté qui cause  parfois  des usages stupides par des inconsients
	par exemple l'horrible usage du modulo tel ce (rand()% 2) pour obtenir 
	un entier dans [0,1], je vous expliquerai...
		
    
	d'abord DEUX fonctions d'initialisation
	chacune donne une valeur à la racine de la suite pseudo-aleatoire
	srand00_system  rend transparent l'usage de l'horloge interne  
	avec en plus le retour de la valeur initiale (pour une possible reproduction)
	srand00_explicit recoit en parametre la racine qui sera donnée au générateur

	UNE REMARQUE ESSENTIELLE : peu importe le générateur pseudo-aléatoire, 
	il est initialisé une SEULE fois dans une simulation numérique
	SINON VOUS TUEZ VOTRE GÉNÉRATEUR --dit simplement mais c'est la vérité--

	Quatre fonctions d'émissions
	randf00, randi00 , randf00_born, randi00_born qui vont civiliser
	le simple rand du C pour émette dans une distribution uniforme spécifiée

*/
/*=========================================================*/
// LES DECLARTIONS DE FONCTIONS 
//   ( on dit malheureusement encore prototypes)
/*=========================================================*/
/* les deux d'initialisation  ne doivent jamais être appellées en boucle 
   elles n'auront PAS de macro associée, ce serait inutile.
*/
/*=========================================================*/
/*  srand00_explicit initialise le générateur de la valeur 
    donnée en paramètre
	PARAMETRES :  la valeur initiale de la suite
	RETOUR : Rien

	SPECS : DANS UNE SIMULATION NUMÉRIQUE, ON NE DOIT JAMAIS
		INITIALISER PLUS D'UNE FOIS LE GÉNÉRATEUR
*/
void srand00_explicit(Uint seed);
/*=========================================================*/
/*=========================================================*/
/*  srand00_system initialise le générateur de la valeur de
	l'horloge interne de la machine
	PARAMETRES :  Rien
	RETOUR : la valeur de l'horloge utilisée

	SPECS : DANS UNE SIMULATION NUMÉRIQUE, ON NE DOIT JAMAIS
		INITIALISER PLUS D'UNE FOIS LE GÉNÉRATEUR
*/
Uint srand00_system(void);
/*=========================================================*/

/* les quatre suivantes sont normalement appellées des millions
   ou des milliards de fois
   leur développement en macro-fonctions est souhaitable
   l'économie en temps d'exécution devient souvent très importante
*/

/*=========================================================*/
/*  randi00 simule un dé à N faces pour donner
	un entier positif entre 1 et le parametre recu

	PARAMETRE :  nombre, un entier positif
	RETOUR : une valeur entre 1 et le parametre

	SPECS : attention, si vous donnez un négatif en paramètre, 
	     il sera considéré positif donc > 2147483648 OUPS.... 
*/
Uint randi00(Uint n);

#define RANDI00(n) (1 + (Uint)((n) * RANDF00()))

/*=========================================================*/

/*=========================================================*/
/*  randi00_born donne un nombre entier dans l'intervalle fermé spécifié
	PARAMETRES :  deux entiers quelconques
	RETOUR : une valeur entiere dans l'intervalle fermé défini par les
			 deux paramètres

	SPECS : l'ordre des paramètres est sans importance
*/
int randi00_born(int b1, int b2);

#define RANDI00_BORN(b1,b2) (((b1) < (b2)) ? ((b1) - 1) + RANDI00((b2 - b1) + 1) : ((b2) - 1) + RANDI00((b1 - b2) + 1))

/*=========================================================*/

/*=========================================================*/
 /*  randf00 donne un nombre réel dans l'intervalle ouvert(0,1)

	PARAMETRES :  aucun
	RETOUR : une valeur réelle dans l'intervalle (0,1)

	SPECS : aucune
*/
double randf00(void);

#define RANDF00() ((1.0 * rand()) / (RAND_MAX + EPSILON))

/*=========================================================*/

/*=========================================================*/
/*  rand0f_born donne un nombre réel dans l'intervalle spécifié
	PARAMETRES :  deux réels quelconques
	RETOUR : une valeur réelle dans l'intervalle défini par ses
			 deux paramètres 

	SPECS : l'ordre des paramètres est sans importance
*/
double randf00_born(double b1, double b2);

#define RANDF00_BORN(b1,b2) ((b1) + (((b2) - (b1)) * RANDF00()))

/*=========================================================*/
#endif
/*=========================================================*/
//c'est fini
/*=========================================================*/