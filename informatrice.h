//
// Created by Méo Charlet on 2025-11-17.
//

#ifndef DEVOIRS2_INFORAMTRICE_H
#define DEVOIRS2_INFORAMTRICE_H


#include "m_gen_gosmique_N.h"
#include "m_gen_gosmique_B.h"

int get_nb_parcours_N(t_Gen_GosmiqueN* gen);
int get_longueur_dernier_N(t_Gen_GosmiqueN* gen);
long get_somme_longueurs_N(t_Gen_GosmiqueN* gen);
long long get_somme_carres_N(t_Gen_GosmiqueN* gen);
double get_longueur_moyenne_N(t_Gen_GosmiqueN* gen);
double get_moyenne_carres_N(t_Gen_GosmiqueN* gen);

int get_nb_parcours_B(t_Gen_GosmiqueB* gen);
int get_longueur_dernier_B(t_Gen_GosmiqueB* gen);
long get_somme_longueurs_B(t_Gen_GosmiqueB* gen);
long long get_somme_carres_B(t_Gen_GosmiqueB* gen);
double get_longueur_moyenne_B(t_Gen_GosmiqueB* gen);
double get_moyenne_carres_B(t_Gen_GosmiqueB* gen);






#endif //DEVOIRS2_INFORAMTRICE_H