#ifndef EN_TETE_H
#define EN_TETE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAILLE_MAX_LIGNE 1024
#define TAILLE_ID 64

// --- STRUCTURES POUR L'HISTOGRAMME (AVL) ---

typedef struct UsineAVL {
    int id;                 // ID numérique (extrait du string)
    char id_str[TAILLE_ID]; // ID complet (ex: "Facility complex #RH4...")
    long capacite;          // Capacité max
    long consommation;      // Volume capté (sources)
    struct UsineAVL* gauche;
    struct UsineAVL* droite;
    int hauteur;
} UsineAVL;

// --- STRUCTURES POUR LES FUITES (Arbre N-aire + Index) ---

// Noeud de l'arbre de distribution (Arbre N-aire)
typedef struct Noeud {
    char id_str[TAILLE_ID];
    float pourcentage_fuite;
    struct Noeud* premierEnfant;  // Pointeur vers le premier enfant
    struct Noeud* frereSuivant;   // Pointeur vers le frère
} Noeud;

// AVL utilisé comme annuaire pour retrouver rapidement l'adresse d'un noeud
typedef struct AnnuaireAVL {
    char id_str[TAILLE_ID]; // Clé de recherche
    Noeud* adresseNoeud;    // Pointeur vers le noeud réel
    struct AnnuaireAVL* gauche;
    struct AnnuaireAVL* droite;
    int hauteur;
} AnnuaireAVL;

// --- PROTOTYPES DES FONCTIONS ---

// Fonctions AVL (Histo)
UsineAVL* creerUsine(int id, char* id_str);
int hauteur(UsineAVL* n);
int max(int a, int b);
UsineAVL* rotationDroite(UsineAVL* y);
UsineAVL* rotationGauche(UsineAVL* x);
int obtenirEquilibre(UsineAVL* n);
UsineAVL* insererUsine(UsineAVL* noeud, int id, char* id_str, long capacite, long apport);
void parcoursInfixe(UsineAVL* racine, FILE* fichier, char* mode);
void libererAVL(UsineAVL* racine);

// Fonctions Fuites (Arbre + Annuaire)
Noeud* creerNoeud(char* id_str, float fuite);
void ajouterEnfant(Noeud* parent, Noeud* enfant);
double calculerPertes(Noeud* noeud, double volume);

// Fonctions Annuaire (AVL pour indexer les noeuds)
AnnuaireAVL* insererAnnuaire(AnnuaireAVL* noeud, char* id_str, Noeud* adresse);
Noeud* chercherDansAnnuaire(AnnuaireAVL* racine, char* id_str);
void libererAnnuaire(AnnuaireAVL* racine);

#endif
