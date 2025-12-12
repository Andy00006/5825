#include "en_tete.h"

// Crée une nouvelle usine
UsineAVL* creerUsine(int id, char* id_str) {
    UsineAVL* usine = (UsineAVL*)malloc(sizeof(UsineAVL));
    if (!usine) { exit(2); } // Erreur allocation
    usine->id = id;
    strcpy(usine->id_str, id_str);
    usine->capacite = 0;
    usine->consommation = 0;
    usine->gauche = NULL;
    usine->droite = NULL;
    usine->hauteur = 1;
    return usine;
}

int hauteur(UsineAVL* n) {
    if (n == NULL) return 0;
    return n->hauteur;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotation pour rééquilibrer l'arbre
UsineAVL* rotationDroite(UsineAVL* y) {
    UsineAVL* x = y->gauche;
    UsineAVL* T2 = x->droite;
    x->droite = y;
    y->gauche = T2;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    return x;
}

UsineAVL* rotationGauche(UsineAVL* x) {
    UsineAVL* y = x->droite;
    UsineAVL* T2 = y->gauche;
    y->gauche = x;
    x->droite = T2;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    return y;
}

int obtenirEquilibre(UsineAVL* n) {
    if (n == NULL) return 0;
    return hauteur(n->gauche) - hauteur(n->droite);
}

// Insertion ou Mise à jour d'une usine
UsineAVL* insererUsine(UsineAVL* noeud, int id, char* id_str, long capacite, long apport) {
    // 1. Insertion normale BST
    if (noeud == NULL) {
        UsineAVL* nouv = creerUsine(id, id_str);
        nouv->capacite = capacite;
        nouv->consommation = apport;
        return nouv;
    }

    if (id < noeud->id)
        noeud->gauche = insererUsine(noeud->gauche, id, id_str, capacite, apport);
    else if (id > noeud->id)
        noeud->droite = insererUsine(noeud->droite, id, id_str, capacite, apport);
    else {
        // L'usine existe déjà : on met à jour les données (somme)
        if (capacite > 0) noeud->capacite = capacite; // Mise à jour cap max
        if (apport > 0) noeud->consommation += apport; // Cumul des sources
        return noeud;
    }

    // 2. Mise à jour hauteur
    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite));

    // 3. Équilibrage
    int equilibre = obtenirEquilibre(noeud);

    // Cas Gauche Gauche
    if (equilibre > 1 && id < noeud->gauche->id)
        return rotationDroite(noeud);

    // Cas Droite Droite
    if (equilibre < -1 && id > noeud->droite->id)
        return rotationGauche(noeud);

    // Cas Gauche Droite
    if (equilibre > 1 && id > noeud->gauche->id) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }

    // Cas Droite Gauche
    if (equilibre < -1 && id < noeud->droite->id) {
        noeud->droite = rotationDroite(noeud->droite);
        return rotationGauche(noeud);
    }

    return noeud;
}

// Parcours pour écrire dans le fichier de sortie
void parcoursInfixe(UsineAVL* racine, FILE* fichier, char* mode) {
    if (racine != NULL) {
        parcoursInfixe(racine->gauche, fichier, mode);
        
        // Écriture selon le mode choisi
        if (strcmp(mode, "max") == 0) {
            fprintf(fichier, "%s;%ld\n", racine->id_str, racine->capacite);
        } else if (strcmp(mode, "src") == 0) {
            fprintf(fichier, "%s;%ld\n", racine->id_str, racine->consommation);
        }
        // Pour "real", c'est plus complexe (nécessite le calcul de fuite), 
        // ici on met basic source pour l'exemple.
        
        parcoursInfixe(racine->droite, fichier, mode);
    }
}

void libererAVL(UsineAVL* racine) {
    if (racine != NULL) {
        libererAVL(racine->gauche);
        libererAVL(racine->droite);
        free(racine);
    }
}
