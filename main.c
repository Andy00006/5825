#include "en_tete.h"

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    char* fichier_csv = argv[1];
    char* commande = argv[2];

    FILE* fp = fopen(fichier_csv, "r");
    if (!fp) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    char ligne[TAILLE_MAX_LIGNE];
    
    // --- MODE HISTOGRAMME ---
    if (strcmp(commande, "histo") == 0) {
        if (argc < 4) return 1;
        char* mode = argv[3];
        UsineAVL* racineUsines = NULL;

        while (fgets(ligne, sizeof(ligne), fp)) {
            char col1[TAILLE_ID], col2[TAILLE_ID], col3[TAILLE_ID], col4[TAILLE_ID];
            // Parsing manuel simple pour éviter les problèmes de strtok avec les champs vides
            // Format attendu: Col1;Col2;Col3;Col4;Col5
            // On utilise sscanf pour extraire les données. 
            // Attention: sscanf s'arrête aux espaces, il faut un format spécifique ou un parser char par char.
            
            // Pour simplifier dans cet exemple : utilisation strtok avec gestion "-"
            char *ptr = strtok(ligne, ";"); char *c1 = ptr;
            ptr = strtok(NULL, ";"); char *c2 = ptr;
            ptr = strtok(NULL, ";"); char *c3 = ptr;
            ptr = strtok(NULL, ";"); char *c4 = ptr;
            // c5 (fuite) ignoré pour histo sauf si "real"

            // Détection Ligne USINE (Definition capacité)
            // ex: -;Facility complex #RH400057F;-;4749292;-
            if (strcmp(c1, "-") == 0 && strcmp(c3, "-") == 0 && strcmp(c4, "-") != 0) {
                int id = atoi(c2 + 1); // Hack pour ignorer le texte si l'ID est dans le string
                // Mieux : utiliser le string complet comme ID
                // Ici on suppose que tu as une fonction pour extraire l'ID numérique si tu veux trier par num
                // Sinon on trie par string. Modifions le main pour trier par ID num simple.
                
                // Pour CYTech : on prend souvent l'ID numérique à la fin du string
                // Exemple simple : on passe 0 en ID num et on trie par string dans une vraie implémentation.
                racineUsines = insererUsine(racineUsines, 0, c2, atol(c4), 0);
            }
            
            // Détection Ligne SOURCE -> USINE
            // ex: -;Spring #MQ001991L;Facility complex #RH400057F;20892;0.997
            else if (strcmp(c1, "-") == 0 && strcmp(c3, "-") != 0 && strcmp(c4, "-") != 0) {
                // c2 = source, c3 = usine, c4 = volume
                racineUsines = insererUsine(racineUsines, 0, c3, 0, atol(c4));
            }
        }
        
        // Ecriture fichier sortie
        FILE* f_out = fopen("resultat_histo.dat", "w");
        parcoursInfixe(racineUsines, f_out, mode);
        fclose(f_out);
        libererAVL(racineUsines);
    }

    // --- MODE FUITES (LEAKS) ---
    else if (strcmp(commande, "leaks") == 0) {
        // Logique similaire mais avec AnnuaireAVL et Noeud
        // A implémenter selon la logique décrite plus haut :
        // 1. Lire ligne
        // 2. Trouver Parent dans Annuaire (ou créer)
        // 3. Créer Enfant
        // 4. Lier Parent -> Enfant
        // 5. Ajouter Enfant dans Annuaire
        // ...
        // A la fin: chercher l'usine cible et appeler calculerPertes()
    }

    fclose(fp);
    return 0;
}
