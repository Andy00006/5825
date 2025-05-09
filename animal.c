#include <stdio.h>
#include <string.h>
#include "animal.h"

void afficher_animal(Animal a) {
    printf("Nom : %s\n", a.nom);
    printf("Poids : %d\n", a.poids);
    printf("Âge : %d\n", a.age);
    printf("Race : %s\n", a.race);
    printf("Genre : %c\n", a.genre);
    printf("Commentaire : %s\n", a.commentaire);
}

void ajouter_animal(Animal* animaux, int* nb_animaux) {
    if (*nb_animaux >= TAILLE_MAX) {
        printf("Le refuge est plein.\n");
        return;
    }

    Animal a;

    printf("Nom : ");
    scanf("%s", a.nom);
    printf("Poids: ");
    scanf("%d", a.poids);
    printf("Âge : ");
    scanf("%d", &a.age);
    getchar();  // nettoie le buffer
    printf("Race : ");
    fgets(a.race, NOM_TAILLE, stdin);
    a.race[strcspn(a.race, "\n")] = 0;

    printf("Genre (M/F) : ");
    scanf(" %c", &a.genre);
    getchar();
    printf("Commentaire : ");
    fgets(a.commentaire, COMMENTAIRE_TAILLE, stdin);
    a.commentaire[strcspn(a.commentaire, "\n")] = 0;

    animaux[*nb_animaux] = a;
    (*nb_animaux)++;

    printf("Animal ajouté avec succès.\n");
}

int charger_animaux(const char* nom_fichier, Animal* animaux, int max) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Aucun fichier existant. Création en cours.\n");
        return 0;
    }

    int nb = 0;
    while (nb < max &&
           fscanf(fichier, "%s %d %s %c %[^\n]", animaux[nb].nom, &animaux[nb].age,
                  animaux[nb].race, &animaux[nb].genre, animaux[nb].commentaire) == 5) {
        nb++;
    }

    fclose(fichier);
    return nb;
}

void enregistrer_animaux(const char* nom_fichier, Animal* animaux, int nb_animaux) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        printf("Erreur d'écriture du fichier.\n");
        return;
    }

    for (int i = 0; i < nb_animaux; i++) {
        fprintf(fichier, "%s %d %s %c %s\n", animaux[i].nom, animaux[i].age,
                animaux[i].race, animaux[i].genre, animaux[i].commentaire);
    }

    fclose(fichier);
}

void afficher_animaux(Animal* animaux, int nb_animaux) {
    for (int i = 0; i < nb_animaux; i++) {
        printf("\nAnimal %d:\n", i + 1);
        afficher_animal(animaux[i]);
    }
}

void rechercher_animaux(Animal* animaux, int nb_animaux) {
    char nom_recherche[NOM_TAILLE];
    printf("Nom à rechercher : ");
    scanf("%s", nom_recherche);

    int trouve = 0;
    for (int i = 0; i < nb_animaux; i++) {
        if (strcmp(animaux[i].nom, nom_recherche) == 0) {
            afficher_animal(animaux[i]);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun animal trouvé avec ce nom.\n");
}

int adopter_animal_par_id(Animal* animaux, int* nb_animaux, int id_a_supprimer) {
    int trouve = 0;

    for (int i = 0; i < *nb_animaux; i++) {
        if (animaux[i].id == id_a_supprimer) {
            trouve = 1;
            // Décaler les animaux suivants
            for (int j = i; j < *nb_animaux - 1; j++) {
                animaux[j] = animaux[j + 1];
            }
            (*nb_animaux)--;
            break;
        }
    }

    if (trouve) {
        printf("🎉 L'animal avec l'ID %d a été adopté avec succès !\n", id_a_supprimer);
    } else {
        printf("❌ Aucun animal trouvé avec l'ID %d.\n", id_a_supprimer);
    }

    return trouve;
}

void calculer_croquettes(Animal a) {
    float croquettes;

    // Hamster : 20g par jour
    if (strcmp(a.race, "hamster") == 0) {
        croquettes = 20;  // 20g de croquettes
    }
    // Autruche : 2.5 kg par jour
    else if (strcmp(a.race, "autruche") == 0) {
        croquettes = 2500;  // 2.5kg = 2500g de croquettes
    }
    // Chat ou chien : dépend de l'âge
    else if (strcmp(a.race, "chat") == 0 || strcmp(a.race, "chien") == 0) {
        if (a.age < 2) {
            croquettes = 500;  // Moins de 2 ans -> 500g
        } else {
            // 10% du poids de l'animal
            // Supposons que l'animal ait un attribut "poids" dans la structure
            // croquettes = 0.10 * a.poids;
            printf("Pour un %s, calculer avec son poids est nécessaire.\n", a.race);
            return;
        }
    }
    else {
        printf("Race inconnue pour le calcul des croquettes.\n");
        return;
    }

    printf("Cet animal a besoin de %.2f grammes de croquettes par jour.\n", croquettes);
}
