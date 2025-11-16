//
// Created by Méo Charlet on 2025-11-14.
//

//========================================================
// AFFICHAGE
//========================================================

#include "affich_informatrice_log.h"

void afficher_grille_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return;

    printf("\n=== GRILLE Gen_Gosmique (%d lignes) ===\n", gen->nb_lignes);
    printf("Légende: . = VIDE, T = TRANSIT, X = OPAQ\n\n");

    int i, j;
    for (i = 0; i < gen->nb_lignes; i++) {
        printf("Ligne %2d: ", i);
        for (j = 0; j < NB_COLONNES; j++) {
            char c;
            switch(gen->grille[i][j]) {
                case VIDE: c = '.'; break;
                case TRANSIT: c = 'T'; break;
                case OPAQ: c = 'X'; break;
                default: c = '?'; break;
            }
            printf("%c ", c);
        }
        printf("\n");
    }
    printf("\n");
}

void afficher_statistiques_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return;

    printf("\n=== STATISTIQUES ===\n");
    printf("Nombre de parcours: %d\n", gen->nb_parcours_total);
    printf("Dernier parcours: %d\n", gen->longueur_dernier_parcours);
    printf("Somme longueurs: %ld\n", gen->somme_longueurs);
    printf("Énergie totale: %lld\n", gen->somme_carres_longueurs);
    if (gen->nb_parcours_total > 0) {
        printf("Longueur moyenne: %.2f\n",
               (double)gen->somme_longueurs / gen->nb_parcours_total);
    }
    printf("Parcours en cours: %s\n", gen->parcours_en_cours ? "OUI" : "NON");
    printf("\n");
}


//========================================================
// INFORMATRICES (getters)
//========================================================
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

double get_energie_totale_N(t_Gen_GosmiqueN* gen) {
    return gen ? (double)gen->somme_carres_longueurs : 0.0;
}

double get_longueur_moyenne_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL || gen->nb_parcours_total == 0) return 0.0;
    return (double)gen->somme_longueurs / gen->nb_parcours_total;
}

int est_parcours_en_cours_N(t_Gen_GosmiqueN* gen) {
    return gen ? gen->parcours_en_cours : 0;
}


//========================================================
// FICHIERS LOG
//========================================================
void ecrire_statistiques_log_N(FILE* fichier, t_Gen_GosmiqueN* gen) {
    if (fichier == NULL || gen == NULL) return;

    fprintf(fichier, "%d,%d,%ld,%lld,%.2f\n",
            gen->nb_parcours_total,
            gen->longueur_dernier_parcours,
            gen->somme_longueurs,
            gen->somme_carres_longueurs,
            get_longueur_moyenne_N(gen));
}

int compter_capteurs_etat_N(t_Gen_GosmiqueN* gen, int etat) {
    if (gen == NULL) return 0;

    int compte = 0;
    int i, j;
    for (i = 0; i < gen->nb_lignes; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            if (gen->grille[i][j] == etat) {
                compte++;
            }
        }
    }
    return compte;
}


//====================================================================
//affichage pour B
//====================================================================

int compter_capteurs_etat_B(t_Gen_GosmiqueB* gen, int etat) {
    if (gen == NULL) return 0;

    int compte = 0;

    for (int i = 0; i < gen->nb_lignes; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (get_etat_capteur_B(gen, i, j) == etat) {
                compte++;
            }
        }
    }

    return compte;
}

void afficher_grille_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return;

    printf("\n=== GRILLE Gen_Gosmique B (%d lignes) ===\n", gen->nb_lignes);
    printf("Légende: . = VIDE, T = TRANSIT, X = OPAQ\n\n");

    for (int i = 0; i < gen->nb_lignes; i++) {
        printf("Ligne %2d: ", i);
        for (int j = 0; j < NB_COLONNES; j++) {
            int etat = get_etat_capteur_B(gen, i, j);
            char c;
            if (etat == VIDE) c = '.';
            else if (etat == TRANSIT) c = 'T';
            else if (etat == OPAQ) c = 'X';
            else c = '?';
            printf("%c ", c);
        }
        printf("\n");
    }
    printf("\n");
}

void afficher_statistiques_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return;

    printf("\n=== STATISTIQUES B ===\n");
    printf("Nombre de parcours: %d\n", gen->nb_parcours_total);
    printf("Dernier parcours: %d\n", gen->longueur_dernier_parcours);
    printf("Somme longueurs: %ld\n", gen->somme_longueurs);
    printf("Énergie totale: %lld\n", gen->somme_carres_longueurs);
    if (gen->nb_parcours_total > 0) {
        printf("Longueur moyenne: %.2f\n",
               (double)gen->somme_longueurs / gen->nb_parcours_total);
    }
    printf("Parcours en cours: %s\n", gen->parcours_en_cours ? "OUI" : "NON");
    printf("\n");
}

void afficher_parcours_debug_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return;

    printf("\n=== DEBUG PARCOURS B ===\n");
    printf("En cours: %s\n", gen->parcours_en_cours ? "OUI" : "NON");
    if (gen->parcours_en_cours) {
        printf("Position: ligne=%d, col=%d\n", gen->position_ligne_actuelle, gen->position_colonne_actuelle);
        printf("Longueur actuelle: %d\n", gen->longueur_parcours_actuel);
    }
    printf("======================\n\n");
}

void ecrire_statistiques_log_B(FILE* fichier, t_Gen_GosmiqueB* gen) {
    if (fichier == NULL || gen == NULL) return;

    fprintf(fichier, "%d,%d,%ld,%lld,%.2f\n",
            gen->nb_parcours_total,
            gen->longueur_dernier_parcours,
            gen->somme_longueurs,
            gen->somme_carres_longueurs,
            get_longueur_moyenne_B(gen));
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

double get_energie_totale_B(t_Gen_GosmiqueB* gen) {
    return gen ? (double)gen->somme_carres_longueurs : 0.0;
}

double get_longueur_moyenne_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL || gen->nb_parcours_total == 0) return 0.0;
    return (double)gen->somme_longueurs / gen->nb_parcours_total;
}

int est_parcours_en_cours_B(t_Gen_GosmiqueB* gen) {
    return gen ? gen->parcours_en_cours : 0;
}