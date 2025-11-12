/**********************************************************/
/* Ce module offre les  actions les plus standard */
/* sur les bits d'un entier positif */

/* on peut : 

	obtenir la valeur d'un bit spécifique (get)
	mettre un bit à 1 dans un entier (set)
	mettre un bit à 0 dans un entier (clear)
	inverser un bit dans un entier (flip)

	et pour une assurance visuelle des résultats
	les afficher à l'écran
*/

/* l'ordre des bits dans un entier selon la tradition  */
/*  commence à 0 , ordre du bit le moins significatif   */

/*  Les entiers sur nos petites machines sont à 32 bits */
/*    au début du vingt et unième siècle */

/**********************************************************/

#ifndef  __MODULE_OPBITS2018__
#define  __MODULE_OPBITS2018__

/*****************************************************/
/*****************************************************/
/*		CONSTANTE					*/
/*****************************************************/
/*  symbole du nombre de bits dans un entier */
#define BITS_INT  (sizeof(int) * 8)
/*****************************************************/


typedef unsigned int uint ;
/*****************************************************/

/**********************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/**********************************************************/


/******************* GET_BIT **********************/
/* 
	donne la valeur du  bit d'ordre spécifié.		
	PARAMETRES : nombre , un entier non signé						
	             ordre du bit voulu dans nombre. 
	RETOUR : 0 ou 1 								
	SPECIFICATIONS :							
	Si ordre n'est pas dans l'intervalle [0, BITS_INT-1], 
	la fonction retourne 0.	
*/

int get_bit_int( uint nombre, uint ordre);

#define GET_BIT_INT(nombre,ordre)  ((!((ordre) < BITS_INT)) ? 0:(((nombre) & (1<<(ordre))) !=0))
/**********************************************************/

/*********************** SET_BIT **************************/
/* 
	donne la valeur du nombre avec le bit d'ordre spécifié mis à 1 
    PARAMETRES : nombre , un entier non signé					
                 ordre , spécifie le bit mis à 1 dans nombre. 
	RETOUR : la valeur obtenue du paramètre avec ce bit à 1								
	SPECIFICATIONS :								
	Si ordre n'est pas dans l'intervalle [0, BITS_INT-1], 
	la	fonction retourne la valeur reçue.	
*/

uint set_bit_int( uint nombre, uint ordre);

#define SET_BIT_INT(nombre,ordre) ((!((ordre) < BITS_INT)) ? (nombre) : ((nombre) | (1 << (ordre))))
/**********************************************************/

/****************** CLEAR_BIT **************************/
/* 
	donne la valeur du nombre  avec le bit d'ordre spécifié mis à 0 
	PARAMETRES : nombre , un entier non signé						
	             ordre , spécifie le bit mis à 0 dans nombre. 
	RETOUR : la valeur obtenue du paramètre avec ce bit à 0						
	SPECIFICATIONS :								
	Si ordre n'est pas dans l'intervalle [0, BITS_INT-1], 
	 la fonction retourne la valeur reçue.
*/

uint clear_bit_int( uint nombre, uint ordre);

#define CLEAR_BIT_INT(nombre,ordre) (((!((ordre) < BITS_INT)) ? (nombre):((nombre) & (~(1 << (ordre))))))
/**********************************************************/

/******************** FLIP_BIT *************************/
/* 
	donne la valeur du nombre reçu  après l'inversaion du  
	bit d'ordre spécifié
	PARAMETRES: nombre : un entier non signé					
	          ordre : spécifie le bit  à inverser dans nombre. 
	RETOUR : la valeur obtenue du paramètre avec ce bit inversé					
	SPECIFICATIONS :							
	Si ordre n'est pas dans l'intervalle [0, BITS_INT-1], 
	 la fonction retourne la valeur reçue.	
*/

uint flip_bit_int(uint nombre, uint ordre);

 #define FLIP_BIT_INT(nombre,ordre) ((!((ordre) < BITS_INT)) ? (nombre) : GET_BIT_INT(nombre, ordre)? CLEAR_BIT_INT(nombre, ordre) :SET_BIT_INT(nombre, ordre))
/**********************************************************/

/***************** VOIR_BITS ****************************/
/*
	Affiche les bits du nombre reçu à l'écran.
	PARAMETRE : nombre , un entier non signé
	RETOUR : rien
	SPECIFICATIONS :
	Les bits sont affichés du plus significatif au moins significatif
	Peu importe en fait le signe du paramètre effectif(int compris)
*/

void voir_bits_int(uint nombre);
/**********************************************************/

#endif
/**********************************************************/

