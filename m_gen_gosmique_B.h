#ifndef M_GEN_GOSMIQUE_B_H
#define M_GEN_GOSMIQUE_B_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "m_opbits_char.h"
#include "m_alea00.h"

#define VIDE 0
#define TRANSIT 1
#define OPAQ 2

#define NB_COLONNES 8
#define P_OPAQ_VIDE 0.53


typedef struct {
    uchar* grille_bits;
    int taille_tableau;

    // Dimensions
    int nb_lignes;

    // Probabilités
    double p_transit_vide;
    double p_opaq_vide;

    // Statistiques globales
    int nb_parcours_total;
    int longueur_dernier_parcours;
    int somme_longueurs;
    int somme_carres_longueurs;

    // État du parcours en cours
    int parcours_en_cours;
    int position_ligne_actuelle;
    int position_colonne_actuelle;
    int longueur_parcours_actuel;
} t_Gen_GosmiqueB;

t_Gen_GosmiqueB* creer_gen_gosmique_b(int nb_lignes, double p_transit_vide);
void detruire_Gen_GosmiqueB(t_Gen_GosmiqueB* gen);
int entree_rayonnement_B(t_Gen_GosmiqueB* gen);
int prochain_capteur_B(t_Gen_GosmiqueB* gen);
int parcours_complet_B(t_Gen_GosmiqueB* gen);
int transition_opaq_vide_B(t_Gen_GosmiqueB* gen);
int transition_transit_B(t_Gen_GosmiqueB* gen);

#endif
