//
// Created by Méo Charlet on 2025-11-14.
//

#include "m_gen_gosmique_B.h"


static int capteur_to_index(int ligne, int colonne) {
    return ligne * NB_COLONNES + colonne;
}

int get_etat_capteur_B(t_Gen_GosmiqueB* gen, int ligne, int colonne) {
    if (!position_valide_B(gen, ligne, colonne)) return -1;

    int index_capteur = capteur_to_index(ligne, colonne);
    int bit_position = index_capteur * 2;
    int byte_index = bit_position / BITS_CHAR;
    int bit_offset = bit_position % BITS_CHAR;

    uchar byte = gen->grille_bits[byte_index];
    int bit0 = get_bit_char(byte, bit_offset);
    int bit1 = get_bit_char(byte, bit_offset + 1);

    return bit0 + (bit1 << 1);
}

int set_etat_capteur_B(t_Gen_GosmiqueB* gen, int ligne, int colonne, int nouvel_etat) {
    if (!position_valide_B(gen, ligne, colonne)) return 0;
    if (nouvel_etat < VIDE || nouvel_etat > OPAQ) return 0;

    int index_capteur = capteur_to_index(ligne, colonne);
    int bit_position = index_capteur * 2;
    int byte_index = bit_position / BITS_CHAR;
    int bit_offset = bit_position % BITS_CHAR;

    int bit0 = nouvel_etat & 1;
    int bit1 = (nouvel_etat >> 1) & 1;

    if (bit0) {
        gen->grille_bits[byte_index] = set_bit_char(gen->grille_bits[byte_index], bit_offset);
    } else {
        gen->grille_bits[byte_index] = clear_bit_char(gen->grille_bits[byte_index], bit_offset);
    }

    if (bit1) {
        gen->grille_bits[byte_index] = set_bit_char(gen->grille_bits[byte_index], bit_offset + 1);
    } else {
        gen->grille_bits[byte_index] = clear_bit_char(gen->grille_bits[byte_index], bit_offset + 1);
    }

    return 1;
}

int position_valide_B(t_Gen_GosmiqueB* gen, int ligne, int colonne) {
    if (gen == NULL) return 0;
    return (ligne >= 0 && ligne < gen->nb_lignes &&
            colonne >= 0 && colonne < NB_COLONNES);
}

int est_ligne_frontiere_B(t_Gen_GosmiqueB* gen, int ligne) {
    if (gen == NULL) return 0;
    return (ligne == 0 || ligne == gen->nb_lignes - 1);
}

t_Gen_GosmiqueB* creer_gen_gosmique_b(int nb_lignes, double p_transit_vide) {
    if (nb_lignes <= 0 || p_transit_vide < 0.0 || p_transit_vide > 1.0) {
        return NULL;
    }

    t_Gen_GosmiqueB* gen = (t_Gen_GosmiqueB*)malloc(sizeof(t_Gen_GosmiqueB));
    if (gen == NULL) return NULL;

    gen->nb_lignes = nb_lignes;
    gen->p_transit_vide = p_transit_vide;
    gen->p_opaq_vide = P_OPAQ_VIDE;

    int nb_capteurs = nb_lignes * NB_COLONNES;
    int nb_bits = nb_capteurs * 2;
    gen->taille_tableau = (nb_bits + BITS_CHAR - 1) / BITS_CHAR;

    gen->grille_bits = (uchar*)calloc(gen->taille_tableau, sizeof(uchar));
    if (gen->grille_bits == NULL) {
        free(gen);
        return NULL;
    }

    gen->nb_parcours_total = 0;
    gen->longueur_dernier_parcours = 0;
    gen->somme_longueurs = 0;
    gen->somme_carres_longueurs = 0;
    gen->parcours_en_cours = 0;
    gen->position_colonne_actuelle=0;
    gen->position_ligne_actuelle=0;
    gen->longueur_parcours_actuel = 0;

    return gen;
}

void detruire_gen_gosmique_b(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return;
    if (gen->grille_bits != NULL) {
        free(gen->grille_bits);
    }
    free(gen);
}

int entree_rayonnement_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0;

    int ligne_entree = (RANDI00(2) == 1) ? 0 : (gen->nb_lignes - 1);

    int capteurs_vides[NB_COLONNES];
    int nb_vides = 0;

    for (int col = 0; col < NB_COLONNES; col++) {
        if (get_etat_capteur_B(gen, ligne_entree, col) == VIDE) {
            capteurs_vides[nb_vides] = col;
            nb_vides++;
        }
    }

    if (nb_vides == 0) return 0;

    int index_choisi = RANDI00(nb_vides) - 1;
    int colonne_entree = capteurs_vides[index_choisi];

    set_etat_capteur_B(gen, ligne_entree, colonne_entree, TRANSIT);
    gen->position_colonne_actuelle = colonne_entree;
    gen->position_ligne_actuelle= ligne_entree;
    gen->longueur_parcours_actuel = 1;
    gen->parcours_en_cours = 1;

    return 1;
}

int prochain_capteur_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return 0;
    if (!gen->parcours_en_cours) return 0;

    int ligne_actuelle = gen->position_ligne_actuelle;
    int colonne_actuelle = gen->position_colonne_actuelle;

    int peut_sortir = (ligne_actuelle == 0 || ligne_actuelle == gen->nb_lignes - 1);

    typedef struct {
        int ligne;
        int colonne;
    } Position;

    Position candidats[6];
    int nb_candidats = 0;

    int lignes_possibles[2];
    int nb_lignes_possibles = 0;

    if (ligne_actuelle > 0) {
        lignes_possibles[nb_lignes_possibles++] = ligne_actuelle - 1;
    }
    if (ligne_actuelle < gen->nb_lignes - 1) {
        lignes_possibles[nb_lignes_possibles++] = ligne_actuelle + 1;
    }

    for (int i = 0; i < nb_lignes_possibles; i++) {
        int nouvelle_ligne = lignes_possibles[i];
        int colonnes_a_tester[3] = {colonne_actuelle - 1, colonne_actuelle, colonne_actuelle + 1};

        for (int j = 0; j < 3; j++) {
            int nouvelle_colonne = colonnes_a_tester[j];

            if (position_valide_B(gen, nouvelle_ligne, nouvelle_colonne) &&
                get_etat_capteur_B(gen, nouvelle_ligne, nouvelle_colonne) == VIDE) {

                candidats[nb_candidats].ligne = nouvelle_ligne;
                candidats[nb_candidats].colonne = nouvelle_colonne;
                nb_candidats++;
            }
        }
    }

    int sort_du_gen = 0;
    if (peut_sortir && nb_candidats > 0) {
        if (RANDF00() < 0.05) {
            sort_du_gen = 1;
        }
    }

    if (nb_candidats == 0 || sort_du_gen) {
        gen->parcours_en_cours = 0;
        gen->nb_parcours_total++;
        gen->longueur_dernier_parcours = gen->longueur_parcours_actuel;
        gen->somme_longueurs += gen->longueur_parcours_actuel;
        gen->somme_carres_longueurs += (long long)(gen->longueur_parcours_actuel) * (long long)(gen->longueur_parcours_actuel);
        return 0;
    }

    int index_choisi = RANDI00(nb_candidats) - 1;
    int nouvelle_ligne = candidats[index_choisi].ligne;
    int nouvelle_colonne = candidats[index_choisi].colonne;

    set_etat_capteur_B(gen, nouvelle_ligne, nouvelle_colonne, TRANSIT);
    gen->position_colonne_actuelle=colonne_actuelle;
    gen->position_ligne_actuelle=ligne_actuelle;
    gen->longueur_parcours_actuel++;

    return 1;
}

int parcours_complet_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0;

    if (!entree_rayonnement_B(gen)) {
        return 0;
    }

    int max_iterations = gen->nb_lignes * NB_COLONNES * 2;
    int iterations = 0;

    while (prochain_capteur_B(gen) && iterations < max_iterations) {
        iterations++;
    }

    if (iterations >= max_iterations && gen->parcours_en_cours) {
        gen->parcours_en_cours = 0;
        gen->nb_parcours_total++;
        gen->longueur_dernier_parcours = gen->longueur_parcours_actuel;
        gen->somme_longueurs += gen->longueur_parcours_actuel;
        gen->somme_carres_longueurs += (long long)(gen->longueur_parcours_actuel) * (long long)(gen->longueur_parcours_actuel);
    }

    return gen->longueur_dernier_parcours;
}

int transition_opaq_vide_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0;

    int nb_transitions = 0;

    for (int i = 0; i < gen->nb_lignes; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (get_etat_capteur_B(gen, i, j) == OPAQ) {
                if (RANDF00() < gen->p_opaq_vide) {
                    set_etat_capteur_B(gen, i, j, VIDE);
                    nb_transitions++;
                }
            }
        }
    }

    return nb_transitions;
}

int transition_transit_B(t_Gen_GosmiqueB* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0;

    int nb_transitions = 0;

    for (int i = 0; i < gen->nb_lignes; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (get_etat_capteur_B(gen, i, j) == TRANSIT) {
                if (RANDF00() < gen->p_transit_vide) {
                    set_etat_capteur_B(gen, i, j, VIDE);
                } else {
                    set_etat_capteur_B(gen, i, j, OPAQ);
                }
                nb_transitions++;
            }
        }
    }

    return nb_transitions;
}

