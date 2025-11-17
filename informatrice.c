//
// Created by Méo Charlet on 2025-11-17.
//

#include "informatrice.h"

int get_nb_parcours_N(t_Gen_GosmiqueN* gen) {
    return gen ? gen->nb_parcours_total : 0;
}

int get_longueur_dernier_N(t_Gen_GosmiqueN* gen) {
    return gen ? gen->longueur_dernier_parcours : 0;
}

long get_somme_longueurs_N(t_Gen_GosmiqueN* gen) {
    return gen ? gen->somme_longueurs : 0;
}

long long get_somme_carres_N(t_Gen_GosmiqueN* gen) {
    return gen ? gen->somme_carres_longueurs : 0;
}

double get_longueur_moyenne_N(t_Gen_GosmiqueN* gen) {
    if (!gen || gen->nb_parcours_total == 0) return 0.0;
    return (double)gen->somme_longueurs / gen->nb_parcours_total;
}

double get_moyenne_carres_N(t_Gen_GosmiqueN* gen) {
    if (!gen || gen->nb_parcours_total == 0) return 0.0;
    return (double)gen->somme_carres_longueurs / gen->nb_parcours_total;
}

int get_nb_parcours_B(t_Gen_GosmiqueB* gen) {
    return gen ? gen->nb_parcours_total : 0;
}

int get_longueur_dernier_B(t_Gen_GosmiqueB* gen) {
    return gen ? gen->longueur_dernier_parcours : 0;
}

long get_somme_longueurs_B(t_Gen_GosmiqueB* gen) {
    return gen ? gen->somme_longueurs : 0;
}

long long get_somme_carres_B(t_Gen_GosmiqueB* gen) {
    return gen ? gen->somme_carres_longueurs : 0;
}

double get_longueur_moyenne_B(t_Gen_GosmiqueB* gen) {
    if (!gen || gen->nb_parcours_total == 0) return 0.0;
    return (double)gen->somme_longueurs / gen->nb_parcours_total;
}

double get_moyenne_carres_B(t_Gen_GosmiqueB* gen) {
    if (!gen || gen->nb_parcours_total == 0) return 0.0;
    return (double)gen->somme_carres_longueurs / gen->nb_parcours_total;
}