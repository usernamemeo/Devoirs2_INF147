//
// Created by Méo Charlet on 2025-11-14.
//

#ifndef DEVOIRS2_M_GEN_COSMIQUE_B_H
#define DEVOIRS2_M_GEN_COSMIQUE_B_H

//
// Created by Méo Charlet on 2025-11-15
// Module Gen_Gosmique - Version B (manipulation de bits)
// Chaque capteur est représenté par 2 bits dans un tableau de unsigned char
//

#ifndef M_GEN_GOSMIQUE_B_H
#define M_GEN_GOSMIQUE_B_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "m_R3.h"
#include "m_alea00.h"
#include "m_opbits_char.h"

// Constantes pour les états des capteurs
#define VIDE 0
#define TRANSIT 1
#define OPAQ 2

// Constantes de la grille
#define NB_COLONNES 8
#define P_OPAQ_VIDE 0.3

// Structure principale du générateur cosmique (version bits)
typedef struct {
    // Grille des capteurs (tableau de bits)
    uchar* grille_bits;          // Tableau de unsigned char contenant les bits
    int taille_tableau;          // Nombre de unsigned char alloués

    // Dimensions
    int nb_lignes;

    // Probabilités
    double p_transit_vide;
    double p_opaq_vide;

    // Statistiques globales
    int nb_parcours_total;
    int longueur_dernier_parcours;
    long somme_longueurs;
    long long somme_carres_longueurs;

    // État du parcours en cours
    int parcours_en_cours;           // 0 = non, 1 = oui
    int position_ligne_actuelle;      // Position actuelle
    int position_colonne_actuelle;    // Position actuelle
    int longueur_parcours_actuel;    // Longueur du parcours en cours

} t_Gen_GosmiqueB;

//========================================================
// FONCTIONS PRINCIPALES
//========================================================

// 1. CONSTRUCTEUR
t_Gen_GosmiqueB* creer_gen_gosmique_b(int nb_lignes, double p_transit_vide);

// 2. DESTRUCTEUR
void detruire_gen_gosmique_b(t_Gen_GosmiqueB* gen);

// 3. ENTRÉE DU RAYONNEMENT
int entree_rayonnement_B(t_Gen_GosmiqueB* gen);

// 4. PROCHAIN CAPTEUR
int prochain_capteur_B(t_Gen_GosmiqueB* gen);

// 5. PARCOURS COMPLET
int parcours_complet_B(t_Gen_GosmiqueB* gen);

// 6. TRANSITION OPAQ -> VIDE
int transition_opaq_vide_B(t_Gen_GosmiqueB* gen);

// 7. TRANSITION TRANSIT -> VIDE ou OPAQ
int transition_transit_B(t_Gen_GosmiqueB* gen);

//========================================================
// FONCTIONS UTILITAIRES
//========================================================

// Obtient l'état d'un capteur (lecture des 2 bits)
int get_etat_capteur_B(t_Gen_GosmiqueB* gen, int ligne, int colonne);

// Modifie l'état d'un capteur (écriture des 2 bits)
int set_etat_capteur_B(t_Gen_GosmiqueB* gen, int ligne, int colonne, int nouvel_etat);

// Compte le nombre de capteurs dans un état donné
int compter_capteurs_etat_B(t_Gen_GosmiqueB* gen, int etat);

// Vérifie si une position est valide
int position_valide_B(t_Gen_GosmiqueB* gen, int ligne, int colonne);

// Vérifie si sur ligne frontière
int est_ligne_frontiere_B(t_Gen_GosmiqueB* gen, int ligne);

// Affichage pour débogage
void afficher_grille_B(t_Gen_GosmiqueB* gen);
void afficher_statistiques_B(t_Gen_GosmiqueB* gen);
void afficher_parcours_debug_B(t_Gen_GosmiqueB* gen);

//========================================================
// FONCTIONS POUR FICHIER LOG
//========================================================

void ecrire_statistiques_log_B(FILE* fichier, t_Gen_GosmiqueB* gen);

//========================================================
// FONCTIONS INFORMATRICES
//========================================================

int get_nb_parcours_B(t_Gen_GosmiqueB* gen);
int get_longueur_dernier_B(t_Gen_GosmiqueB* gen);
long get_somme_longueurs_B(t_Gen_GosmiqueB* gen);
long long get_somme_carres_B(t_Gen_GosmiqueB* gen);
double get_energie_totale_B(t_Gen_GosmiqueB* gen);
double get_longueur_moyenne_B(t_Gen_GosmiqueB* gen);
int est_parcours_en_cours_B(t_Gen_GosmiqueB* gen);

#endif // M_GEN_GOSMIQUE_B_H

#endif //DEVOIRS2_M_GEN_COSMIQUE_B_H