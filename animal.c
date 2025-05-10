#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "animal.h"
#include <ctype.h>
#include <time.h>

void afficher_animal(Animal a) {
    printf("Nom : %s\n", a.nom);
    printf("Poids : %d kg\n", a.poids);
    printf("Âge : %d ans (%d)\n", a.age, 2025 - a.age);  // Âge avec l'année de naissance calculée
    printf("Race : %s\n", a.race);
    printf("Commentaire : %s\n", a.commentaire);
}

void ajouter_animal(Animal* animaux, int* nb_animaux) {
    if (*nb_animaux >= TAILLE_MAX) {
        printf("Le refuge est plein.\n");
        return;
    }

    Animal a;

    // Nom de l'animal : vérification que ce n'est pas un nombre
    do {
        printf("Nom : ");
        scanf("%s", a.nom);

        int est_valide = 1;
        for (int i = 0; a.nom[i] != '\0'; i++) {
            if (!isalpha(a.nom[i])) {
                est_valide = 0;
                break;
            }
        }

        if (!est_valide) {
            printf("❌ Le nom doit être composé uniquement de lettres.\n");
        }

    } while (a.nom[0] == '\0' || !isalpha(a.nom[0]));

    // Poids : vérification des chiffres
    char input_poids[20];
    int poids_valide = 0;

    do {
        printf("Poids en kg : ");
        scanf("%s", input_poids);

        poids_valide = 1;
        for (int i = 0; input_poids[i] != '\0'; i++) {
            if (!isdigit(input_poids[i])) {
                poids_valide = 0;
                break;
            }
        }

        if (poids_valide) {
            a.poids = atoi(input_poids);
            if (a.poids <= 0) {
                poids_valide = 0;
                printf("❌ Entrez un poids supérieur à 0.\n");
            }
        } else {
            printf("❌ Erreur : le poids doit être un nombre entier en kg (ex: 12).\n");
        }

    } while (!poids_valide);

    // Âge : vérification des chiffres
    char input_age[10];
    int age_valide = 0;

    do {
        printf("Âge : ");
        scanf("%s", input_age);

        age_valide = 1;
        for (int i = 0; input_age[i] != '\0'; i++) {
            if (!isdigit(input_age[i])) {
                age_valide = 0;
                break;
            }
        }

        if (age_valide) {
            a.age = atoi(input_age);
            if (a.age <= 0) {
                age_valide = 0;
                printf("❌ Entrez un âge supérieur à 0.\n");
            }
        } else {
            printf("❌ Erreur : l'âge doit être un nombre entier (ex: 3).\n");
        }

    } while (!age_valide);

    // Race : vérification des valeurs valides
    int race_valide = 0;
    do {
        printf("Espèce (chat, chien, hamster, autruche) : ");
        scanf("%s", a.race);

        if (strcmp(a.race, "chat") == 0 || strcmp(a.race, "chien") == 0 ||
            strcmp(a.race, "hamster") == 0 || strcmp(a.race, "autruche") == 0) {
            race_valide = 1;
        } else {
            printf("❌ La race doit être l'un des suivants : chat, chien, hamster, autruche.\n");
        }

    } while (!race_valide);

    // Commentaire
    getchar();  // Nettoie le buffer
    printf("Commentaire : ");
    fgets(a.commentaire, COMMENTAIRE_TAILLE, stdin);
    a.commentaire[strcspn(a.commentaire, "\n")] = 0;

    // Ajouter l'animal
    animaux[*nb_animaux] = a;
    (*nb_animaux)++;
    
    printf("\n");
    printf("Animal ajouté avec succès.\n\n");
}

int charger_animaux(const char* nom_fichier, Animal* animaux, int max) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Aucun fichier existant. Création en cours.\n");
        return 0;
    }

    int nb = 0;
    while (nb < max && fscanf(fichier, "%d %s %d %s %[^\n]", &animaux[nb].id, animaux[nb].nom, &animaux[nb].poids, animaux[nb].race, animaux[nb].commentaire) == 5) {
        animaux[nb].age = 2025 - (animaux[nb].poids);  // Calcul approximatif pour charger l'âge
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
        fprintf(fichier, "%d %s %d %s %s\n", animaux[i].id, animaux[i].nom, animaux[i].poids, animaux[i].race, animaux[i].commentaire);
    }

    fclose(fichier);
}

void afficher_animaux(Animal* animaux, int nb_animaux) {
    for (int i = 0; i < nb_animaux; i++) {
        printf("\nAnimal %d:\n", i + 1);
        afficher_animal(animaux[i]);
    }
}

// Fonction de recherche avec plusieurs critères
void rechercher_animaux(Animal* animaux, int nb_animaux) {
    int critere;
    char input_nom[NOM_TAILLE], input_race[NOM_TAILLE];
    int critere_age;

    printf("\n=== Recherche d'animal ===\n\n");
    printf("Choisissez le critère de recherche:\n\n");
    printf("1. Recherche par nom\n");
    printf("2. Recherche par espèce\n");
    printf("3. Recherche par âge (jeune ou senior)\n");
    printf("\n");
    printf("Votre choix : ");
    scanf("%d", &critere);
    printf("\n");

    switch (critere) {
        case 1: {
            // Recherche par nom
            printf("Entrez le nom de l'animal à rechercher : ");
            scanf("%s", input_nom);

            printf("\n=== Résultats de la recherche par nom ===\n\n");
            int trouve = 0;
            for (int i = 0; i < nb_animaux; i++) {
                if (strcmp(animaux[i].nom, input_nom) == 0) {
                    afficher_animal(animaux[i]);
                    printf("\n");
                    trouve = 1;
                }
            }
            if (!trouve) {
                printf("Aucun animal trouvé avec le nom %s.\n", input_nom);
            }
            break;
        }
        case 2: {
            // Recherche par espèce
            printf("Entrez l'espèce de l'animal (chat, chien, hamster, autruche) : ");
            scanf("%s", input_race);

            printf("\n=== Résultats de la recherche par espèce ===\n\n");
            int trouve = 0;
            for (int i = 0; i < nb_animaux; i++) {
                if (strcmp(animaux[i].race, input_race) == 0) {
                    afficher_animal(animaux[i]);
                    printf("\n");
                    trouve = 1;
                }
            }
            if (!trouve) {
                printf("Aucun animal trouvé avec l'espèce %s.\n", input_race);
            }
            break;
        }
        case 3: {
            // Recherche par âge (jeune, adulte, senior)
            printf("Choisissez le type d'âge :\n");
            printf("1. Animaux jeunes (< 2 ans)\n");
            printf("2. Animaux adultes (2 - 10 ans)\n");
            printf("3. Animaux seniors (> 10 ans)\n");
            printf("Votre choix : ");
            scanf("%d", &critere_age);

            printf("\n=== Résultats de la recherche par âge ===\n\n");
            int trouve = 0;
            for (int i = 0; i < nb_animaux; i++) {
                if (critere_age == 1 && animaux[i].age < 2) {
                    afficher_animal(animaux[i]);
                    printf("\n");
                    trouve = 1;
                } 
                else if (critere_age == 2 && animaux[i].age >= 2 && animaux[i].age <= 10) {
                    afficher_animal(animaux[i]);
                    printf("\n");
                    trouve = 1;
                }
                else if (critere_age == 3 && animaux[i].age > 10) {
                    afficher_animal(animaux[i]);
                    printf("\n");
                    trouve = 1;
                }
            }
            if (!trouve) {
                printf("Aucun animal trouvé selon les critères d'âge choisis.\n");
            }
            break;
        }
        default:
            printf("Critère de recherche invalide.\n");
            break;
    }
}

void calculer_croquettes(Animal a) {
    float croquettes;

    if (strcmp(a.race, "hamster") == 0) {
        croquettes = 20;  // 20g de croquettes
    } else if (strcmp(a.race, "autruche") == 0) {
        croquettes = 2500;  // 2.5kg = 2500g de croquettes
    } else if (strcmp(a.race, "chat") == 0 || strcmp(a.race, "chien") == 0) {
        if (a.age < 2) {
            croquettes = 500;  // Moins de 2 ans -> 500g
        } else {
            croquettes = 100 * a.poids;  // 10% du poids de l'animal
        }
    }

    printf("Cet animal a besoin de %.2f grammes de croquettes par jour.\n", croquettes);
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
            (*nb_animaux)--; // Réduire le nombre d'animaux
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

void afficher_inventaire(Animal* animaux, int nb_animaux) {
    // Compter le nombre d'animaux par espèce
    int compteur[4] = {0};  // Tableau pour compter les animaux par espèce
    const char* races[] = {"hamster", "autruche", "chat", "chien"};
    
    // Parcourir tous les animaux et compter les occurrences de chaque espèce
    for (int i = 0; i < nb_animaux; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(animaux[i].race, races[j]) == 0) {
                compteur[j]++;
            }
        }
    }
    
    // Afficher le nombre total d'animaux
    printf("Nombre total d'animaux dans le refuge : %d\n", nb_animaux);
    
    // Créer un tableau d'index pour trier les espèces
    int indices[4] = {0, 1, 2, 3};  // Indices correspondant aux races
    
    // Trier les indices par nombre d'animaux de chaque espèce (tri décroissant)
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (compteur[indices[i]] < compteur[indices[j]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
    
    // Afficher les résultats triés
    printf("\nDétail des animaux par espèce :\n");
    for (int i = 0; i < 4; i++) {
        printf("%s : %d\n", races[indices[i]], compteur[indices[i]]);
    }
}
