#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "data.h"

/* Programme unique pour histo et leaks:
   usage:
   ./eau_analyse histo <csv> <max|src|real>
   ./eau_analyse leaks <csv> "<FactoryID>"
*/

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s histo <csv> <max|src|real>  OR  %s leaks <csv> \"FactoryID\"\n", argv[0], argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "histo") == 0) {
        if (argc != 4) { fprintf(stderr, "histo requires: <csv> <max|src|real>\n"); return 2; }
        const char *csv = argv[2];
        const char *mode = argv[3];
        if (!(strcmp(mode,"max")==0 || strcmp(mode,"src")==0 || strcmp(mode,"real")==0)) {
            fprintf(stderr, "mode inconnu %s\n", mode); return 3;
        }
        AVL *avl_usines = avl_creer();
        AVL *avl_noeuds = avl_creer();
        if (construire_depuis_csv(csv, avl_usines, avl_noeuds) != 0) {
            avl_liberer(avl_usines, NULL);
            avl_liberer(avl_noeuds, NULL);
            return 4;
        }
        if (generer_histo(avl_usines, mode) != 0) {
            avl_liberer(avl_usines, liberer_usine); /* liberer_usine non visible ici -> workaround below */
        }
        /* libérer */
        avl_liberer(avl_usines, liberer_usine);
        avl_liberer(avl_noeuds, liberer_noeud);
        printf("Fichier vol_%s.dat créé\n", mode);
        return 0;
    } else if (strcmp(argv[1], "leaks") == 0) {
        if (argc != 4) { fprintf(stderr, "leaks requires: <csv> \"FactoryID\"\n"); return 5; }
        const char *csv = argv[2];
        const char *id = argv[3];
        AVL *avl_usines = avl_creer();
        AVL *avl_noeuds = avl_creer();
        if (construire_depuis_csv(csv, avl_usines, avl_noeuds) != 0) {
            avl_liberer(avl_usines, NULL);
            avl_liberer(avl_noeuds, NULL);
            return 6;
        }
        double res = calculer_fuites(avl_usines, avl_noeuds, id);
        if (res < 0.0) {
            printf("-1\n");
        } else {
            printf("%.6f\n", res);
        }
        avl_liberer(avl_usines, liberer_usine);
        avl_liberer(avl_noeuds, liberer_noeud);
        return 0;
    } else {
        fprintf(stderr, "commande inconnue %s\n", argv[1]);
        return 7;
    }
}
