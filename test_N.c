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
    srand00_system();

    printf("=== TEST DU MODULE Gen_GosmiqueN ===\n\n");

    // TEST 1 : Création
    t_Gen_GosmiqueN* gen = creer_gen_gosmique_n(5, 0.7);
    assert(gen != NULL);
    assert(gen->nb_lignes == 5);
    assert(gen->p_transit_vide == 0.7);
    assert(gen->nb_parcours_total == 0);
    assert(gen->parcours_en_cours == 0);
    assert(compter_capteurs_etat_N(gen, VIDE) == 40);  // 5×8 = 40

    afficher_grille_N(gen);

    // TEST 2 : Parcours complet
    int longueur = parcours_complet_N(gen);
    assert(longueur > 0);  // longueur doit être > 0
    assert(gen->parcours_en_cours == 0);  // parcours terminé
    assert(gen->nb_parcours_total == 1);  // 1 parcours effectué
    assert(gen->longueur_dernier_parcours == longueur);
    assert(gen->somme_longueurs == longueur);
    assert(gen->somme_carres_longueurs == (long long)longueur * longueur);

    afficher_grille_N(gen);
    afficher_statistiques_N(gen);

    // TEST 3 : Transition TRANSIT
    int nb_transit_avant = compter_capteurs_etat_N(gen, TRANSIT);
    int nb_trans = transition_transit_N(gen);
    assert(nb_trans == nb_transit_avant);  // tous les TRANSIT changent
    assert(compter_capteurs_etat_N(gen, TRANSIT) == 0);  // plus de TRANSIT

    afficher_grille_N(gen);

    // TEST 4 : Plusieurs parcours
    int nb_parcours_avant = gen->nb_parcours_total;
    for (int i = 0; i < 10; i++) {
        int L = parcours_complet_N(gen);
        assert(L > 0);
        assert(gen->parcours_en_cours == 0);

        int t1 = transition_transit_N(gen);
        assert(t1 >= 0);
        assert(compter_capteurs_etat_N(gen, TRANSIT) == 0);

        int t2 = transition_opaq_vide_N(gen);
        assert(t2 >= 0);

        // Conservation des capteurs
        int total = compter_capteurs_etat_N(gen, VIDE) +
                    compter_capteurs_etat_N(gen, TRANSIT) +
                    compter_capteurs_etat_N(gen, OPAQ);
        assert(total == 40);
    }

    assert(gen->nb_parcours_total == nb_parcours_avant + 10);

    afficher_statistiques_N(gen);

    // TEST 5 : Fichier LOG
    FILE* log = fopen("test_log_N.csv", "w");
    assert(log != NULL);

    fprintf(log, "NbParcours,DerniereLongueur,SommeLongueurs,Energie,LongueurMoyenne\n");

    int nb_avant_log = gen->nb_parcours_total;
    for (int i = 0; i < 100; i++) {
        parcours_complet_N(gen);
        transition_transit_N(gen);
        transition_opaq_vide_N(gen);

        if (i % 10 == 0)
            ecrire_statistiques_log_N(log, gen);
    }

    assert(gen->nb_parcours_total == nb_avant_log + 100);

    fclose(log);

    // TEST 6 : Informateurs
    assert(get_nb_parcours_N(gen) == gen->nb_parcours_total);
    assert(get_longueur_dernier_N(gen) == gen->longueur_dernier_parcours);
    assert(get_somme_longueurs_N(gen) == gen->somme_longueurs);
    assert(get_somme_carres_N(gen) == gen->somme_carres_longueurs);
    assert(get_energie_totale_N(gen) == (double)gen->somme_carres_longueurs);

    double moy_calculee = (double)gen->somme_longueurs / gen->nb_parcours_total;
    assert(get_longueur_moyenne_N(gen) == moy_calculee);

    // Vérifier que compter_capteurs_etat_N renvoie bien une valeur valide
    int nb_vide   = compter_capteurs_etat_N(gen, VIDE);
    int nb_trans2 = compter_capteurs_etat_N(gen, TRANSIT);
    int nb_opaq   = compter_capteurs_etat_N(gen, OPAQ);

    assert(nb_vide   >= 0);
    assert(nb_trans2 >= 0);
    assert(nb_opaq   >= 0);

    // TEST : somme cohérente avec la taille totale
    assert(nb_vide + nb_trans2 + nb_opaq == 40);

    // TRANSIT devrait être 0 entre les parcours
    assert(nb_trans2 == 0);

    // Il doit rester des capteurs VIDE
    assert(nb_vide > 0);

    printf("\nÉtat final des capteurs:\n");
    printf("  VIDE:    %d (%.1f%%)\n", nb_vide, 100.0*nb_vide/40);
    printf("  TRANSIT: %d (%.1f%%)\n", nb_trans2, 100.0*nb_trans2/40);
    printf("  OPAQ:    %d (%.1f%%)\n", nb_opaq, 100.0*nb_opaq/40);

    detruire_Gen_GosmiqueN(gen);

    printf("\n=== TOUS LES TESTS PASSÉS ===\n");
    return 0;
}