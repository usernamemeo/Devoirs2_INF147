//
// Created by Méo Charlet on 2025-11-14.
//

#ifndef DEVOIRS2_M_GEN_COSMIQUE_N_H
#define DEVOIRS2_M_GEN_COSMIQUE_N_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "m_alea00.h"

// Constantes pour les états des capteurs
#define VIDE 0
#define TRANSIT 1
#define OPAQ 2

// Constantes de la grille
#define NB_COLONNES 8
#define P_OPAQ_VIDE 0.53


typedef struct {
    // Grille des capteurs (matrice dynamique)
    int** grille;              // grille[ligne][colonne] contient l'état du capteur

    // Dimensions
    int nb_lignes;             // Nombre de lignes de capteurs

    // Probabilités
    double p_transit_vide;     // Probabilité TRANSIT -> VIDE
    double p_opaq_vide;        // Probabilité OPAQ -> VIDE (fixe)

    // Statistiques globales
    int nb_parcours_total;           // Nombre total de parcours effectués
    int longueur_dernier_parcours;   // Longueur du dernier parcours terminé
    long somme_longueurs;            // Somme des longueurs de tous les parcours
    long long somme_carres_longueurs;// Somme des carrés des longueurs (énergie totale)

    // État du parcours en cours
    int parcours_en_cours;           // 0 = non, 1 = oui
    int position_ligne_actuelle;      // Position actuelle
    int position_colonne_actuelle;    // Position actuelle
    int longueur_parcours_actuel;    // Longueur du parcours en cours

} t_Gen_GosmiqueN;

t_Gen_GosmiqueN* creer_gen_gosmique_n(int nb_lignes, double p_transit_vide); //#1

void detruire_Gen_GosmiqueN(t_Gen_GosmiqueN* gen); //#2

int position_valide_N(t_Gen_GosmiqueN* gen, int ligne, int colonne);

int get_etat_capteur_N(t_Gen_GosmiqueN* gen, int ligne, int colonne);

int set_etat_capteur_N(t_Gen_GosmiqueN* gen, int ligne, int colonne, int nouvel_etat);

int est_ligne_frontiere_N(t_Gen_GosmiqueN* gen, int ligne) ;

int entree_rayonnement_N(t_Gen_GosmiqueN* gen);//#3

int prochain_capteur_N(t_Gen_GosmiqueN* gen) ;//#4

int parcours_complet_N(t_Gen_GosmiqueN* gen);//#5

int transition_opaq_vide_N(t_Gen_GosmiqueN* gen);//#6

int transition_transit_N(t_Gen_GosmiqueN* gen) ;//#7





#endif //DEVOIRS2_M_GEN_COSMIQUE_N_H

