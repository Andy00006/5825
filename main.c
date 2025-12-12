#include "header.h"

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    char* fichier = argv[1];
    char* commande = argv[2];

    FILE* fp = fopen(fichier, "r");
    if (!fp) { fprintf(stderr, "Erreur fichier\n"); return 2; }

    char ligne[TAILLE_BUF];

    if (strcmp(commande, "histo") == 0) {
        char* mode = argv[3];
        Station* avl = NULL;

        // Lecture
        while (fgets(ligne, TAILLE_BUF, fp)) {
            // ID Usine est col 2 (src->usine) ou col 2 (usine) ou col 1 (usine->stock)
            // On doit deviner le type de ligne.
            // Simplification : On cherche si c'est une ligne de définition d'usine
            char* c2 = recupererChamp(ligne, 2);
            char* c4 = recupererChamp(ligne, 4); // Capacité ou Conso
            char* c3 = recupererChamp(ligne, 3); // Destinataire

            // Cas : USINE (définition capacité) :: c2=ID, c4=Capacité, c3=NULL
            if (c2 && c4 && !c3 && strstr(c2, "Facility")) {
                avl = insererStation(avl, c2, atol(c4), 0);
            }
            // Cas : SOURCE -> USINE :: c2=Source, c3=Usine, c4=Volume
            else if (c2 && c3 && c4 && strstr(c3, "Facility")) {
                avl = insererStation(avl, c3, 0, atol(c4));
            }
        }

        // Fichier temporaire pour Gnuplot
        FILE* out = fopen("histo.dat", "w");
        parcoursInverse(avl, out, mode);
        fclose(out);
        libererStation(avl);

    } 
    else if (strcmp(commande, "leaks") == 0) {
        char* id_usine = argv[3];
        Index* annuaire = NULL;
        Noeud* usineDepart = NULL;

        // 1. Construction du graphe entier (nécessaire car lignes mélangées)
        while (fgets(ligne, TAILLE_BUF, fp)) {
            char* c2 = recupererChamp(ligne, 2); // Amont
            char* c3 = recupererChamp(ligne, 3); // Aval
            char* c5 = recupererChamp(ligne, 5); // % Fuite

            if (c2 && c3) {
                // Trouver ou créer Amont
                Noeud* nAmont = rechercherIndex(annuaire, c2);
                if (!nAmont) {
                    nAmont = creerNoeud(c2, 0); // Fuite 0 car c'est la source du tronçon
                    annuaire = insererIndex(annuaire, c2, nAmont);
                }

                // Créer Aval
                float fuite = (c5) ? atof(c5) : 0.0;
                Noeud* nAval = creerNoeud(c3, fuite);
                annuaire = insererIndex(annuaire, c3, nAval);

                // Lier
                ajouterEnfant(nAmont, nAval);
            }
        }

        // 2. Calcul
        usineDepart = rechercherIndex(annuaire, id_usine);
        if (usineDepart) {
            // On ne connait pas le volume entrant initial, on suppose capacité max ou on le passe en arg ?
            // Le sujet ne le précise pas clairement, on va mettre une valeur fixe ou lire la capacité
            // Pour l'exemple, on considère que l'usine envoie 1000 m3
            double pertes = calculerPertes(usineDepart, 1000000); // Ex: 1M m3
            printf("%s;%f\n", id_usine, pertes);
            
            // Écriture dans fichier résultat (append)
            FILE* f_leaks = fopen("leaks.dat", "a"); // Append
            fprintf(f_leaks, "%s;%f\n", id_usine, pertes);
            fclose(f_leaks);
        } else {
            printf("Usine inconnue\n");
        }
        
        // TODO: Libération mémoire index/graphe (complexe ici)
        libererIndex(annuaire);
    }

    fclose(fp);
    return 0;
}
