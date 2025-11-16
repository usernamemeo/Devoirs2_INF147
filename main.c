//
// Created by Méo Charlet on 2025-11-16.
//

//
// Programme principal de comparaison des versions N et B
// Comme demandé dans le PDF du devoir
//

#include <stdio.h>
#include <stdlib.h>

#include "affich_informatrice_log.h"
#include "m_gen_gosmique_N.h"
#include "m_gen_gosmique_B.h"
#include "m_alea00.h"

#define NB_LIGNES 5
#define P_TRANSIT 0.7
#define NB_CYCLES 100

int main() {
    srand00_system();

    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║   COMPARAISON VERSION N vs VERSION B                     ║\n");
    printf("║   Test de cohérence des deux implémentations            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    //========================================================
    // 1. INSTANCIER LES DEUX OBJETS (Constructeurs)
    //========================================================
    printf("Étape 1: Création des objets Gen_Gosmique...\n");

    t_Gen_GosmiqueN* gen_N = creer_gen_gosmique_n(NB_LIGNES, P_TRANSIT);
    if (gen_N == NULL) {
        fprintf(stderr, "Erreur: création Gen_GosmiqueN échouée\n");
        return 1;
    }
    printf("  ✓ Version N créée (%d lignes, P=%.2f)\n", NB_LIGNES, P_TRANSIT);

    t_Gen_GosmiqueB* gen_B = creer_gen_gosmique_b(NB_LIGNES, P_TRANSIT);
    if (gen_B == NULL) {
        fprintf(stderr, "Erreur: création Gen_GosmiqueB échouée\n");
        detruire_Gen_GosmiqueN(gen_N);
        return 1;
    }
    printf("  ✓ Version B créée (%d lignes, P=%.2f)\n", NB_LIGNES, P_TRANSIT);

    //========================================================
    // 2. OUVRIR LES FICHIERS LOG
    //========================================================
    printf("\nÉtape 2: Ouverture des fichiers LOG...\n");

    FILE* log_N = fopen("log_version_N.csv", "w");
    if (log_N == NULL) {
        fprintf(stderr, "Erreur: impossible de créer log_version_N.csv\n");
        detruire_Gen_GosmiqueN(gen_N);
        detruire_gen_gosmique_b(gen_B);
        return 1;
    }

    FILE* log_B = fopen("log_version_B.csv", "w");
    if (log_B == NULL) {
        fprintf(stderr, "Erreur: impossible de créer log_version_B.csv\n");
        fclose(log_N);
        detruire_Gen_GosmiqueN(gen_N);
        detruire_gen_gosmique_b(gen_B);
        return 1;
    }

    // En-têtes CSV
    fprintf(log_N, "Cycle,NbParcours,DerniereLongueur,SommeLongueurs,Energie,LongMoy,VIDE,TRANSIT,OPAQ\n");
    fprintf(log_B, "Cycle,NbParcours,DerniereLongueur,SommeLongueurs,Energie,LongMoy,VIDE,TRANSIT,OPAQ\n");

    printf("  ✓ Fichier log_version_N.csv ouvert\n");
    printf("  ✓ Fichier log_version_B.csv ouvert\n");

    //========================================================
    // 3. BOUCLE DE SIMULATION (N cycles)
    //========================================================
    printf("\nÉtape 3: Simulation de %d cycles...\n", NB_CYCLES);
    printf("Progression: ");
    fflush(stdout);

    int cycle;
    for (cycle = 0; cycle < NB_CYCLES; cycle++) {
        // Affichage progression
        if (cycle % 10 == 0) {
            printf(".");
            fflush(stdout);
        }

        //========================================
        // VERSION N
        //========================================

        // a) Insérer les informatrices dans le LOG
        fprintf(log_N, "%d,%d,%d,%ld,%lld,%.2f,%d,%d,%d\n",
                cycle,
                get_nb_parcours_N(gen_N),
                get_longueur_dernier_N(gen_N),
                get_somme_longueurs_N(gen_N),
                get_somme_carres_N(gen_N),
                get_longueur_moyenne_N(gen_N),
                compter_capteurs_etat_N(gen_N, VIDE),
                compter_capteurs_etat_N(gen_N, TRANSIT),
                compter_capteurs_etat_N(gen_N, OPAQ));

        // b) Fonction #5: Parcours complet
        parcours_complet_N(gen_N);

        // c) Fonction #6: Transition OPAQ -> VIDE
        transition_opaq_vide_N(gen_N);

        // d) Fonction #7: Transition TRANSIT -> VIDE/OPAQ
        transition_transit_N(gen_N);

        //========================================
        // VERSION B
        //========================================

        // a) Insérer les informatrices dans le LOG
        fprintf(log_B, "%d,%d,%d,%ld,%lld,%.2f,%d,%d,%d\n",
                cycle,
                get_nb_parcours_B(gen_B),
                get_longueur_dernier_B(gen_B),
                get_somme_longueurs_B(gen_B),
                get_somme_carres_B(gen_B),
                get_longueur_moyenne_B(gen_B),
                compter_capteurs_etat_B(gen_B, VIDE),
                compter_capteurs_etat_B(gen_B, TRANSIT),
                compter_capteurs_etat_B(gen_B, OPAQ));

        // b) Fonction #5: Parcours complet
        parcours_complet_B(gen_B);

        // c) Fonction #6: Transition OPAQ -> VIDE
        transition_opaq_vide_B(gen_B);

        // d) Fonction #7: Transition TRANSIT -> VIDE/OPAQ
        transition_transit_B(gen_B);
    }

    printf(" ✓\n");

    //========================================================
    // 4. FERMER LES FICHIERS
    //========================================================
    printf("\nÉtape 4: Fermeture des fichiers...\n");
    fclose(log_N);
    fclose(log_B);
    printf("  ✓ Fichiers LOG fermés\n");

    //========================================================
    // 5. AFFICHER LES STATISTIQUES FINALES
    //========================================================
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              STATISTIQUES FINALES                        ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");

    printf("\n📊 VERSION N (Matrice d'entiers):\n");
    printf("───────────────────────────────────\n");
    printf("  Parcours total:     %d\n", get_nb_parcours_N(gen_N));
    printf("  Dernier parcours:   %d capteurs\n", get_longueur_dernier_N(gen_N));
    printf("  Longueur moyenne:   %.2f capteurs\n", get_longueur_moyenne_N(gen_N));
    printf("  Énergie totale:     %.0f unités\n", get_energie_totale_N(gen_N));
    printf("  État capteurs:      VIDE=%d, TRANSIT=%d, OPAQ=%d\n",
           compter_capteurs_etat_N(gen_N, VIDE),
           compter_capteurs_etat_N(gen_N, TRANSIT),
           compter_capteurs_etat_N(gen_N, OPAQ));

    printf("\n📊 VERSION B (Manipulation de bits):\n");
    printf("───────────────────────────────────\n");
    printf("  Parcours total:     %d\n", get_nb_parcours_B(gen_B));
    printf("  Dernier parcours:   %d capteurs\n", get_longueur_dernier_B(gen_B));
    printf("  Longueur moyenne:   %.2f capteurs\n", get_longueur_moyenne_B(gen_B));
    printf("  Énergie totale:     %.0f unités\n", get_energie_totale_B(gen_B));
    printf("  État capteurs:      VIDE=%d, TRANSIT=%d, OPAQ=%d\n",
           compter_capteurs_etat_B(gen_B, VIDE),
           compter_capteurs_etat_B(gen_B, TRANSIT),
           compter_capteurs_etat_B(gen_B, OPAQ));

    //========================================================
    // 6. VÉRIFICATION DE COHÉRENCE
    //========================================================
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║           VÉRIFICATION DE COHÉRENCE                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    int nb_parcours_N = get_nb_parcours_N(gen_N);
    int nb_parcours_B = get_nb_parcours_B(gen_B);
    double energie_N = get_energie_totale_N(gen_N);
    double energie_B = get_energie_totale_B(gen_B);
    double moy_N = get_longueur_moyenne_N(gen_N);
    double moy_B = get_longueur_moyenne_B(gen_B);

    printf("Comparaison des résultats:\n");
    printf("─────────────────────────────────────────────────────────\n");
    printf("  Nombre de parcours:   N=%d  vs  B=%d  (Δ=%d)\n",
           nb_parcours_N, nb_parcours_B, abs(nb_parcours_N - nb_parcours_B));
    printf("  Énergie totale:       N=%.0f  vs  B=%.0f  (Δ=%.0f)\n",
           energie_N, energie_B, fabs(energie_N - energie_B));
    printf("  Longueur moyenne:     N=%.2f  vs  B=%.2f  (Δ=%.2f)\n",
           moy_N, moy_B, fabs(moy_N - moy_B));

    printf("\nAnalyse des différences:\n");
    printf("─────────────────────────────────────────────────────────\n");

    // Les résultats doivent être similaires (variations aléatoires acceptables)
    int diff_parcours = abs(nb_parcours_N - nb_parcours_B);
    double diff_moy = fabs(moy_N - moy_B);
    double diff_energie_pct = fabs(energie_N - energie_B) / ((energie_N + energie_B) / 2.0) * 100.0;

    int coherent = 1;

    // Vérification nombre de parcours (doit être identique ou très proche)
    if (diff_parcours <= 5) {
        printf("  ✓ Nombre de parcours: COHÉRENT (différence acceptable: %d)\n", diff_parcours);
    } else {
        printf("  ✗ Nombre de parcours: INCOHÉRENCE (différence: %d)\n", diff_parcours);
        coherent = 0;
    }

    // Vérification longueur moyenne
    if (diff_moy <= 2.0) {
        printf("  ✓ Longueur moyenne: COHÉRENT (différence: %.2f)\n", diff_moy);
    } else {
        printf("  ⚠ Longueur moyenne: Différence notable (%.2f)\n", diff_moy);
    }

    // Vérification énergie (en pourcentage)
    if (diff_energie_pct <= 15.0) {
        printf("  ✓ Énergie totale: COHÉRENT (différence: %.1f%%)\n", diff_energie_pct);
    } else {
        printf("  ✗ Énergie totale: INCOHÉRENCE (différence: %.1f%%)\n", diff_energie_pct);
        coherent = 0;
    }

    printf("\n");
    if (coherent) {
        printf("╔══════════════════════════════════════════════════════════╗\n");
        printf("║  ✓✓✓ LES DEUX VERSIONS SONT COHÉRENTES ✓✓✓             ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n");
        printf("\nLes variations observées sont dues au caractère aléatoire\n");
        printf("de la simulation et sont dans les limites acceptables.\n");
    } else {
        printf("╔══════════════════════════════════════════════════════════╗\n");
        printf("║  ✗✗✗ INCOHÉRENCE DÉTECTÉE ✗✗✗                          ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n");
        printf("\n⚠ Attention: Des différences importantes ont été détectées.\n");
        printf("Vérifier l'implémentation des deux versions.\n");
    }

    //========================================================
    // 7. INFORMATIONS COMPLÉMENTAIRES
    //========================================================
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              INFORMATIONS COMPLÉMENTAIRES                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    printf("📁 Fichiers générés:\n");
    printf("  • log_version_N.csv - Données détaillées version N\n");
    printf("  • log_version_B.csv - Données détaillées version B\n\n");

    printf("📊 Analyse des fichiers LOG:\n");
    printf("  Ouvrez les fichiers CSV avec Excel, LibreOffice ou Python\n");
    printf("  pour visualiser l'évolution des parcours dans le temps:\n");
    printf("  - Graphique de l'énergie cumulée\n");
    printf("  - Évolution de la longueur moyenne\n");
    printf("  - État des capteurs (VIDE/TRANSIT/OPAQ)\n\n");

    printf("💾 Utilisation mémoire (pour %d lignes):\n", NB_LIGNES);
    int capteurs = NB_LIGNES * NB_COLONNES;
    int memoire_N = capteurs * sizeof(int);  // Version N
    int memoire_B = (capteurs * 2 + 7) / 8;  // Version B (2 bits par capteur)
    printf("  Version N: ~%d bytes (matrice d'entiers)\n", memoire_N);
    printf("  Version B: ~%d bytes (manipulation de bits)\n", memoire_B);
    printf("  Gain mémoire: %.1fx (Version B utilise %.0f%% de la mémoire de N)\n",
           (double)memoire_N / memoire_B,
           100.0 * memoire_B / memoire_N);

    //========================================================
    // 8. DESTRUCTION DES OBJETS
    //========================================================
    printf("\nÉtape 5: Libération de la mémoire...\n");
    detruire_Gen_GosmiqueN(gen_N);
    detruire_gen_gosmique_b(gen_B);
    printf("  ✓ Mémoire libérée\n");

    //========================================================
    // CONCLUSION
    //========================================================
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              TEST TERMINÉ AVEC SUCCÈS                    ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    return 0;
}