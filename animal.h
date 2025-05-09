#ifndef ANIMAL_H
#define ANIMAL_H

#define TAILLE_MAX 100
#define NOM_TAILLE 50
#define COMMENTAIRE_TAILLE 100
#define FICHIER_DATA "animaux/data.txt"

typedef struct {
    char nom[NOM_TAILLE];
    int age;
    char race[NOM_TAILLE];
    char genre;
    char commentaire[COMMENTAIRE_TAILLE];
} Animal;

void afficher_animal(Animal a);
void ajouter_animal(Animal* animaux, int* nb_animaux);
int charger_animaux(const char* nom_fichier, Animal* animaux, int max);
void enregistrer_animaux(const char* nom_fichier, Animal* animaux, int nb_animaux);
void afficher_animaux(Animal* animaux, int nb_animaux);
void rechercher_animaux(Animal* animaux, int nb_animaux);

#endif
