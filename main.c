//
// Created by Méo Charlet on 2025-11-14.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "m_gen_gosmique_N.h"
#include "affich_informatrice_log.h"


int main() {
    srand((unsigned int)time(NULL));

    printf("=== TEST DU MODULE Gen_GosmiqueN ===\n\n");

    // TEST 1 : Création
    t_Gen_GosmiqueN* gen = creer_gen_gosmique_n(1, 0.7);
    assert(gen != NULL);

    afficher_grille_N(gen);

    // TEST 2 : Parcours complet
    int longueur = parcours_complet_N(gen);
    assert(longueur >= 0);  // longueur valide ?

    afficher_grille_N(gen);
    afficher_statistiques_N(gen);

    // TEST 3 : Transition TRANSIT
    int nb_trans = transition_transit_N(gen);
    assert(nb_trans >= 0);  // au moins 0 capteurs changés

    afficher_grille_N(gen);

    // TEST 4 : Plusieurs parcours
    for (int i = 0; i < 10; i++) {
        int L = parcours_complet_N(gen);
        assert(L >= 0);

        int t1 = transition_transit_N(gen);
        assert(t1 >= 0);

        int t2 = transition_opaq_vide_N(gen);
        assert(t2 >= 0);
    }

    afficher_statistiques_N(gen);

    // TEST 5 : Fichier LOG
    FILE* log = fopen("test_log_N.csv", "w");
    assert(log != NULL);

    fprintf(log, "NbParcours,DerniereLongueur,SommeLongueurs,Energie,LongueurMoyenne\n");

    for (int i = 0; i < 100; i++) {
        parcours_complet_N(gen);
        transition_transit_N(gen);
        transition_opaq_vide_N(gen);

        if (i % 10 == 0)
            ecrire_statistiques_log_N(log, gen);
    }

    fclose(log);

    // TEST 6 : Informateurs
    assert(get_nb_parcours_N(gen) >= 0);
    assert(get_longueur_dernier_N(gen) >= 0);
    assert(get_energie_totale_N(gen) >= 0);
    assert(get_longueur_moyenne_N(gen) >= 0);

    // Vérifier que compter_capteurs_etat_N renvoie bien une valeur valide
    int nb_vide   = compter_capteurs_etat_N(gen, VIDE);
    int nb_trans2 = compter_capteurs_etat_N(gen, TRANSIT);
    int nb_opaq   = compter_capteurs_etat_N(gen, OPAQ);

    assert(nb_vide   == 8);
    assert(nb_trans2 >= 0);
    assert(nb_opaq   >= 0);

    // TEST : somme cohérente avec la taille totale (si connue)
    // assert(nb_vide + nb_trans2 + nb_opaq == gen->taille);

    detruire_Gen_GosmiqueN(gen);

    printf("\n=== TOUS LES TESTS PASSÉS ===\n");
    return 0;
}
