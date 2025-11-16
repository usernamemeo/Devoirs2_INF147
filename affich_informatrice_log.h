//
// Created by Méo Charlet on 2025-11-14.
//

#ifndef DEVOIRS2_AFFICH_INFORMATRICE_LOG_H
#define DEVOIRS2_AFFICH_INFORMATRICE_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "m_alea00.h"
#include "m_gen_gosmique_N.h"
#include "m_gen_gosmique_B.h"
/*==========================================================*/
// AFFICHAGE
/*==========================================================*/

void afficher_grille_N(t_Gen_GosmiqueN* gen);

void afficher_statistiques_N(t_Gen_GosmiqueN* gen);

/*==========================================================*/
//INFORMATRICE
/*==========================================================*/

int get_nb_parcours_N(t_Gen_GosmiqueN* gen);

int get_longueur_dernier_N(t_Gen_GosmiqueN* gen);

long get_somme_longueurs_N(t_Gen_GosmiqueN* gen);

long long get_somme_carres_N(t_Gen_GosmiqueN* gen);

double get_energie_totale_N(t_Gen_GosmiqueN* gen);

double get_longueur_moyenne_N(t_Gen_GosmiqueN* gen);

int est_parcours_en_cours_N(t_Gen_GosmiqueN* gen);

/*==========================================================*/
//LOG
/*==========================================================*/

void ecrire_statistiques_log_N(FILE* fichier, t_Gen_GosmiqueN* gen);

int compter_capteurs_etat_N(t_Gen_GosmiqueN* gen, int etat);


/*==========================================================*/
//affichage B
/*==========================================================*/


int compter_capteurs_etat_B(t_Gen_GosmiqueB* gen, int etat);


void afficher_grille_B(t_Gen_GosmiqueB* gen);
void afficher_statistiques_B(t_Gen_GosmiqueB* gen);
void afficher_parcours_debug_B(t_Gen_GosmiqueB* gen);


void ecrire_statistiques_log_B(FILE* fichier, t_Gen_GosmiqueB* gen);

int get_nb_parcours_B(t_Gen_GosmiqueB* gen);
int get_longueur_dernier_B(t_Gen_GosmiqueB* gen);
long get_somme_longueurs_B(t_Gen_GosmiqueB* gen);
long long get_somme_carres_B(t_Gen_GosmiqueB* gen);
double get_energie_totale_B(t_Gen_GosmiqueB* gen);
double get_longueur_moyenne_B(t_Gen_GosmiqueB* gen);
int est_parcours_en_cours_B(t_Gen_GosmiqueB* gen);


#endif //DEVOIRS2_AFFICH_INFORMATRICE_LOG_H