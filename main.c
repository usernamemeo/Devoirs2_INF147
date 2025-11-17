#include <stdio.h>
#include "m_gen_gosmique_N.h"
#include "m_gen_gosmique_B.h"
#include "m_chronos.h"
#include "informatrice.h"


#if 0

#define NB_LIGNES 10
#define NB_TESTS 200
#define P_TRANSIT_VIDE 0.95


int main() {
    srand00_system();

    t_Gen_GosmiqueN* genN = creer_gen_gosmique_n(NB_LIGNES, P_TRANSIT_VIDE);


    t_chrono chronoN = init_chrono();
    start_chrono(chronoN);
    int minN = 999999, maxN = 0;

    for (int i = 0; i < NB_TESTS; i++) {
        int l = parcours_complet_N(genN);
        if (l < minN) minN = l;
        if (l > maxN) maxN = l;
        transition_transit_N(genN);
        transition_opaq_vide_N(genN);
    }

    double tempsN = get_chrono(chronoN);
    stop_chrono(chronoN);

    printf("\n=== Résultats Gen_GosmiqueN ===\n");
    printf("Moyenne des longueurs : %.2f\n", get_longueur_moyenne_N(genN));
    printf("Moyenne des carrés     : %.2f\n", get_moyenne_carres_N(genN));
    printf("Minimum                : %d\n", minN);
    printf("Maximum                : %d\n", maxN);
    printf("Temps total (ms)       : %.2f\n", tempsN * 1000);

    srand00_system();
    t_Gen_GosmiqueB* genB = creer_gen_gosmique_b(NB_LIGNES, P_TRANSIT_VIDE);

    t_chrono chronoB = init_chrono();
    start_chrono(chronoB);
    int minB = 999999, maxB = 0;

    for (int i = 0; i < NB_TESTS; i++) {
        int l = parcours_complet_B(genB);
        if (l < minB) minB = l;
        if (l > maxB) maxB = l;
        transition_transit_B(genB);
        transition_opaq_vide_B(genB);
    }

    double tempsB = get_chrono(chronoB);
    stop_chrono(chronoB);

    printf("\n=== Résultats Gen_GosmiqueB ===\n");
    printf("Moyenne des longueurs : %.2f\n", get_longueur_moyenne_B(genB));
    printf("Moyenne des carrés     : %.2f\n", get_moyenne_carres_B(genB));
    printf("Minimum                : %d\n", minB);
    printf("Maximum                : %d\n", maxB);
    printf("Temps total (ms)       : %.2f\n", tempsB * 1000);

    detruire_Gen_GosmiqueN(genN);
    detruire_Gen_GosmiqueB(genB);

    return 0;
}

#endif

#define NB_LIGNES 12
#define P_TRANSIT 0.75
#define NB_PARCOURS 250

double calculer_cout(int nb_lignes, double p) {
    return nb_lignes * 8 * pow(10.0, (p - 0.55) / 0.1);
}

int main() {
    srand00_system();

    double p_values[] = {0.55, 0.65, 0.75, 0.85, 0.95};

    FILE* f = fopen("serie1_resultats.csv", "w");
    fprintf(f, "P_TRANSIT,Cout,Long_Moy,Long_Min,Long_Max,Energie,Energie_Moy,Energie_Cout\n");

    printf("Série 1: P_TRANSIT variable (12 lignes, 250 parcours)\n");

    for (int i = 0; i < 5; i++) {
        t_Gen_GosmiqueN* gen = creer_gen_gosmique_n(NB_LIGNES, p_values[i]);

        int min = 999999, max = 0;

        for (int j = 0; j < NB_PARCOURS; j++) {
            int L = parcours_complet_N(gen);
            if (L < min) min = L;
            if (L > max) max = L;
            transition_transit_N(gen);
            transition_opaq_vide_N(gen);
        }

        double moy = get_longueur_moyenne_N(gen);
        long long energie = get_somme_carres_N(gen);
        double energie_moy = (double)energie / NB_PARCOURS;
        double cout = calculer_cout(NB_LIGNES, p_values[i]);
        double ratio = energie / cout;

        fprintf(f, "%.2f,%.2f,%.2f,%d,%d,%lld,%.2f,%.2f\n",
                p_values[i], cout, moy, min, max, energie, energie_moy, ratio);

        printf("P=%.2f: Moy=%.2f, Max=%d, Ratio=%.1f\n",
               p_values[i], moy, max, ratio);

        detruire_Gen_GosmiqueN(gen);
    }

    fclose(f);
    printf("\nFichier créé: serie1_resultats.csv\n");



    srand00_system();

    int lignes_values[] = {10, 15, 20, 25, 30, 35};

    FILE* x = fopen("serie2_resultats.csv", "w");
    fprintf(f, "Nb_Lignes,Cout,Long_Moy,Long_Min,Long_Max,Energie,Energie_Moy,Energie_Cout\n");

    printf("Série 2: Lignes variables (P=0.75, 250 parcours)\n");

    for (int i = 0; i < 6; i++) {
        t_Gen_GosmiqueN* gen = creer_gen_gosmique_n(lignes_values[i], P_TRANSIT);

        int min = 999999, max = 0;

        for (int j = 0; j < NB_PARCOURS; j++) {
            int L = parcours_complet_N(gen);
            if (L < min) min = L;
            if (L > max) max = L;
            transition_transit_N(gen);
            transition_opaq_vide_N(gen);
        }

        double moy = get_longueur_moyenne_N(gen);
        long long energie = get_somme_carres_N(gen);
        double energie_moy = (double)energie / NB_PARCOURS;
        double cout = calculer_cout(lignes_values[i], P_TRANSIT);
        double ratio = energie / cout;

        fprintf(f, "%d,%.2f,%.2f,%d,%d,%lld,%.2f,%.2f\n",
                lignes_values[i], cout, moy, min, max, energie, energie_moy, ratio);

        printf("Lignes=%d: Moy=%.2f, Max=%d, Ratio=%.1f\n",
               lignes_values[i], moy, max, ratio);

        detruire_Gen_GosmiqueN(gen);
    }

    fclose(x);
    printf("\nFichier créé: serie2_resultats.csv\n");


    return 0;
}