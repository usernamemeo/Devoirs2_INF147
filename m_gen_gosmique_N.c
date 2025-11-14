//
// Created by Méo Charlet on 2025-11-14.
//

#import "m_gen_gosmique_N.h"

/*--------------------------------------------------------------------------*/
/* creation gen cosmique                                                    */
/*--------------------------------------------------------------------------*/

t_Gen_GosmiqueN* creer_gen_gosmique_n(int nb_lignes, double p_transit_vide) {

    t_Gen_GosmiqueN* gen = (t_Gen_GosmiqueN*)malloc(sizeof(t_Gen_GosmiqueN));
    assert(gen != NULL);

    gen->nb_lignes = nb_lignes;
    gen->p_transit_vide = p_transit_vide;
    gen->p_opaq_vide = P_OPAQ_VIDE;

    // Allocation de la matrice (tableau de pointeurs)
    gen->grille = malloc(nb_lignes * sizeof(int*));
    if (gen->grille == NULL) {
        free(gen);
        return NULL;
    }

    // Allocation de chaque ligne
    int i, j;
    for (i = 0; i < nb_lignes; i++) {
        gen->grille[i] = (int*)malloc(NB_COLONNES * sizeof(int));
        if (gen->grille[i] == NULL) {
            // Libérer ce qui a déjà été alloué
            for (j = 0; j < i; j++) {
                free(gen->grille[j]);
            }
            free(gen->grille);
            free(gen);
            fprintf(stderr, "Erreur: allocation ligne échouée\n");
            return NULL;
        }

        // Initialiser tous les capteurs à VIDE
        for (j = 0; j < NB_COLONNES; j++) {
            gen->grille[i][j] = VIDE;
        }
    }

    // Initialisation des statistiques
    gen->nb_parcours_total = 0;
    gen->longueur_dernier_parcours = 0;
    gen->somme_longueurs = 0;
    gen->somme_carres_longueurs = 0;

    // Initialisation du parcours
    gen->parcours_en_cours = 0;
    gen->position_colonne_actuelle =0;
    gen->position_ligne_actuelle =0;
    gen->longueur_parcours_actuel = 0;

    return gen;
}

/*--------------------------------------------------------------------------*/
/* destruction gen cosmique                                                 */
/*--------------------------------------------------------------------------*/

void detruire_Gen_GosmiqueN(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return;

    // Libérer chaque ligne
    if (gen->grille != NULL) {
        int i;
        for (i = 0; i < gen->nb_lignes; i++) {
            if (gen->grille[i] != NULL) {
                free(gen->grille[i]);
            }
        }
        free(gen->grille);
    }

    // Libérer la structure
    free(gen);
}

/*==========================================================================*/
/*                  fonctions utilse pour la suite                          */
/*==========================================================================*/

int position_valide_N(t_Gen_GosmiqueN* gen, int ligne, int colonne) {
    if (gen == NULL) return 0;
    return (ligne >= 0 && ligne < gen->nb_lignes &&
            colonne >= 0 && colonne < NB_COLONNES);
}

int get_etat_capteur_N(t_Gen_GosmiqueN* gen, int ligne, int colonne) {
    if (!position_valide_N(gen, ligne, colonne)) return -1;
    return gen->grille[ligne][colonne];
}

int set_etat_capteur_N(t_Gen_GosmiqueN* gen, int ligne, int colonne, int nouvel_etat) {
    if (!position_valide_N(gen, ligne, colonne)) return 0;
    if (nouvel_etat < VIDE || nouvel_etat > OPAQ) return 0;

    gen->grille[ligne][colonne] = nouvel_etat;
    return 1;
}

int est_ligne_frontiere_N(t_Gen_GosmiqueN* gen, int ligne) {
    if (gen == NULL) return 0;
    return (ligne == 0 || ligne == gen->nb_lignes - 1);
}
/*==========================================================================*/
/*==========================================================================*/


/*--------------------------------------------------------------------------*/
/* obtenir une position aleatoire dans l'objet                              */
/*--------------------------------------------------------------------------*/

int entree_rayonnement_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0; // Déjà un parcours en cours

    // Choisir aléatoirement première (0) ou dernière ligne
    int ligne_entree = (randi00_born(0, gen->nb_lignes)) ? 0 : (gen->nb_lignes - 1);

    // Chercher tous les capteurs VIDE sur cette ligne
    int capteurs_vides[NB_COLONNES];
    int nb_vides = 0;
    int col;

    for (col = 0; col < NB_COLONNES; col++) {
        if (gen->grille[ligne_entree][col] == VIDE) {
            capteurs_vides[nb_vides] = col;
            nb_vides++;
        }
    }

    // Aucun capteur VIDE disponible
    if (nb_vides == 0) return 0;

    // Choisir aléatoirement parmi les capteurs VIDE
    int index_choisi = rand() % nb_vides;
    int colonne_entree = capteurs_vides[index_choisi];

    // Démarrer le parcours
    gen->grille[ligne_entree][colonne_entree] = TRANSIT;
    gen->position_colonne_actuelle = colonne_entree;
    gen->position_ligne_actuelle = ligne_entree;
    gen->longueur_parcours_actuel = 1;
    gen->parcours_en_cours = 1;

    return 1;
}

/*--------------------------------------------------------------------------------------------*/
/* Obtenir dans un objet T le choix aléatoire du prochain capteur du parcours courant         */
/*--------------------------------------------------------------------------------------------*/

int prochain_capteur_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return 0;
    if (!gen->parcours_en_cours) return 0;

    int ligne_actuelle = gen->position_ligne_actuelle;
    int colonne_actuelle = gen->position_colonne_actuelle;

    // Tableau pour stocker les positions adjacentes valides
    typedef struct {
        int ligne;
        int colonne;
    } Position;

    Position candidats[6]; // Maximum 6 voisins possibles
    int nb_candidats = 0;

    // Règles de déplacement:
    // - Ligne: doit changer (K-1 ou K+1)
    // - Colonne: peut rester ou changer (C-1, C, C+1)

    int lignes_possibles[2];
    int nb_lignes_possibles = 0;

    // Ligne au-dessus
    if (ligne_actuelle > 0) {
        lignes_possibles[nb_lignes_possibles++] = ligne_actuelle - 1;
    }
    // Ligne en-dessous
    if (ligne_actuelle < gen->nb_lignes - 1) {
        lignes_possibles[nb_lignes_possibles++] = ligne_actuelle + 1;
    }

    // Pour chaque ligne possible
    int i, nouvelle_ligne, nouvelle_colonne;
    for (i = 0; i < nb_lignes_possibles; i++) {
        nouvelle_ligne = lignes_possibles[i];

        // Colonnes possibles: C-1, C, C+1
        int colonnes_a_tester[3] = {
            colonne_actuelle - 1,
            colonne_actuelle,
            colonne_actuelle + 1
        };

        int j;
        for (j = 0; j < 3; j++) {
            nouvelle_colonne = colonnes_a_tester[j];

            // Vérifier si position valide et capteur VIDE
            if (position_valide_N(gen, nouvelle_ligne, nouvelle_colonne) &&
                gen->grille[nouvelle_ligne][nouvelle_colonne] == VIDE) {

                candidats[nb_candidats].ligne = nouvelle_ligne;
                candidats[nb_candidats].colonne = nouvelle_colonne;
                nb_candidats++;
            }
        }
    }

    // Aucun déplacement possible -> fin du parcours
    if (nb_candidats == 0) {
        // Terminer le parcours
        gen->parcours_en_cours = 0;
        gen->nb_parcours_total++;
        gen->longueur_dernier_parcours = gen->longueur_parcours_actuel;
        gen->somme_longueurs += gen->longueur_parcours_actuel;
        gen->somme_carres_longueurs += (long long)(gen->longueur_parcours_actuel) * (long long)(gen->longueur_parcours_actuel);
        return 0;
    }

    // Choisir aléatoirement parmi les candidats
    int index_choisi = randi00(nb_candidats);
    nouvelle_ligne = candidats[index_choisi].ligne;
    nouvelle_colonne = candidats[index_choisi].colonne;

    // Déplacer le rayonnement
    gen->grille[nouvelle_ligne][nouvelle_colonne] = TRANSIT;
    gen->position_ligne_actuelle = ligne_actuelle;
    gen->position_colonne_actuelle = colonne_actuelle;
    gen->longueur_parcours_actuel++;

    return 1;
}

/*--------------------------------------------------------------------------------------------*/
/* Obtenir dans un objet T un nouveau parcours                                                */
/*--------------------------------------------------------------------------------------------*/

int parcours_complet_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0; // Déjà un parcours en cours

    // Démarrer l'entrée
    if (!entree_rayonnement_N(gen)) {
        return 0; // Échec de l'entrée
    }

    // Continuer jusqu'à la fin
    while (prochain_capteur_N(gen)) {
        // Continue tant que possible
    }

    return gen->longueur_dernier_parcours;
}

/*--------------------------------------------------------------------------------------------*/
/* Déclencher dans un objet T le possible passage de ses capteurs de l’état OPAQ à l’état VIDE*/
/*--------------------------------------------------------------------------------------------*/

int transition_opaq_vide_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0; // Pas pendant un parcours

    int nb_transitions = 0;
    int i, j;

    for (i = 0; i < gen->nb_lignes; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            if (gen->grille[i][j] == OPAQ) {
                // Test aléatoire avec probabilité P_OPAQ_VIDE
                if (randf00() < gen->p_opaq_vide) {
                    gen->grille[i][j] = VIDE;
                    nb_transitions++;
                }
            }
        }
    }

    return nb_transitions;
}

/*------------------------------------------------------------------------------------------------*/
/* Déclencher dans un objet T le possible passage de ses capteurs de l’état TRANSIT à l’état VIDE */
/*------------------------------------------------------------------------------------------------*/

int transition_transit_N(t_Gen_GosmiqueN* gen) {
    if (gen == NULL) return 0;
    if (gen->parcours_en_cours) return 0; // Pas pendant un parcours

    int nb_transitions = 0;
    int i, j;

    for (i = 0; i < gen->nb_lignes; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            if (gen->grille[i][j] == TRANSIT) {
                // Test aléatoire avec probabilité P_TRANSIT_VIDE
                if (randf00() < gen->p_transit_vide) {
                    gen->grille[i][j] = VIDE;
                } else {
                    gen->grille[i][j] = OPAQ;
                }
                nb_transitions++;
            }
        }
    }

    return nb_transitions;
}