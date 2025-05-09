#include <stdio.h>
#include "animal.h"

int main() {
    Animal animaux[TAILLE_MAX];
    int nb_animaux = charger_animaux(FICHIER_DATA, animaux, TAILLE_MAX);

    int choix;
    int reponse;
     int id_a_adopter;
    do {
        printf("\n=== Menu du refuge===\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher tous les animaux\n");
        printf("3. Rechercher un animal\n");
        printf("4. Adopter un animal\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_animal(animaux, &nb_animaux);
                printf("Voulez-vous savoir combien de croquettes cet animal a besoin par jour ? (1/0) : ");
                getchar();  // Pour consommer le '\n' laissé par scanf
                scanf("%d", &reponse);
                if (reponse == 1) {
                    calculer_croquettes(animaux[nb_animaux - 1]); // Appel à la fonction pour le dernier animal ajouté;  // Calculer les croquettes pour l'animal
                } 
                
                break;
            case 2:
                afficher_animaux(animaux, nb_animaux);
                break;
            case 3:
                rechercher_animaux(animaux, nb_animaux);
                break;
            case 4:
                 printf("Entrez l'ID de l'animal à adopter : ");
                    scanf("%d", &id_a_adopter);
                    adopter_animal_par_id(animaux, &nb_animaux, id_a_adopter);
                break;
            case 5:
             enregistrer_animaux(FICHIER_DATA, animaux, nb_animaux);
                printf("Données enregistrées. Au revoir !\n");
                break;
        
            default:
                printf("Choix invalide.\n");
    } 
    } while (choix != 5);
    return 0;
}
