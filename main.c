#include <stdio.h>
#include "animal.h"

int main() {
    Animal animaux[TAILLE_MAX];
    int nb_animaux = charger_animaux(FICHIER_DATA, animaux, TAILLE_MAX);

    int choix;
    do {
        printf("\n=== Menu du refuge ===\n\n");
        printf("1. Ajouter un animal\n");
        printf("2. Rechercher un animal\n");
        printf("3. Adopter un animal\n");
        printf("4. Afficher l'inventaire des animaux\n");
        printf("5. Quitter\n\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        printf("\n");

        switch (choix) {
            case 1:
                ajouter_animal(animaux, &nb_animaux);
                break;
            case 2:
                rechercher_animaux(animaux, nb_animaux);
                break;
            case 3:
                {
                    int id_a_adopter;
                    printf("\nEntrez l'ID de l'animal à adopter : ");
                    scanf("%d", &id_a_adopter);
                    adopter_animal_par_id(animaux, &nb_animaux, id_a_adopter);
                }
                break;
            case 4:
                afficher_inventaire(animaux, nb_animaux);
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
