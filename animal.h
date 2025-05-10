#ifndef ANIMAL_H
#define ANIMAL_H

#define TAILLE_MAX 100
#define NOM_TAILLE 50
#define COMMENTAIRE_TAILLE 255
#define FICHIER_DATA "animaux.dat"

// Définition de la structure Animal
typedef struct {
    int id;               // ID unique de l'animal
    char nom[NOM_TAILLE]; // Nom de l'animal
    int poids;            // Poids de l'animal en kg
    int age;              // Âge de l'animal
    char race[NOM_TAILLE]; // Race de l'animal
    char commentaire[COMMENTAIRE_TAILLE]; // Commentaire sur l'animal
} Animal;

// Fonctions prototypes
void afficher_animal(Animal a);
void ajouter_animal(Animal* animaux, int* nb_animaux);
int charger_animaux(const char* nom_fichier, Animal* animaux, int max);
void enregistrer_animaux(const char* nom_fichier, Animal* animaux, int nb_animaux);
void afficher_animaux(Animal* animaux, int nb_animaux);
void rechercher_animaux(Animal* animaux, int nb_animaux);
int adopter_animal_par_id(Animal* animaux, int* nb_animaux, int id_a_adopter);
void calculer_croquettes(Animal a);
void afficher_inventaire(Animal* animaux, int nb_animaux);

#endif // ANIMAL_H
