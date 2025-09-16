#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct MotInfo            
{
    char valeurMot[100];  
    int nbOccurrences;         
    int longueur;
    int positions[500];
}; 

void saisirTexte(char text[]){  //fonction pour saisi le text
    /*
    printf("Entrez un texte : \n");
    fgets(text, sizeof text, stdin);
    text[strcspn(text, "\n")] = '\0';
    */
}

void supprimerPonctuation(char text[]){
    char temp[2000];
    char punct[] = ".,;:!?\"\'()[]{}";
    int j = 0;
    int nbCaracters = strlen(text);
    for(int i = 0; i<nbCaracters; i++){
        if (strchr(punct, text[i]) == NULL){
           temp[j] = text[i];
           j++;
           
        }
    }
    temp[j] = '\0';
    strcpy(text, temp); 
}

void mettreEnMinuscules(char text[]){      //fonction pour mettre en miniscule 
    int nbCaracters = strlen(text);
    for(int i=0; i<nbCaracters; i++){
        text[i] = tolower((unsigned char)text[i]);
    }
}

int construireDictionnaire(struct MotInfo tableau[], int nbmot, char text[])
{   
    int positionIndex = 1;

    mettreEnMinuscules(text);                             //l'appel de tominuscule fonction
    supprimerPonctuation(text);

    char *token = strtok(text, " ");
    while(token != NULL){
        int found = 0;
        tableau[nbmot].longueur = strlen(token);   //calculer la longueur de mot 

        for (int i=0; i<nbmot; i++){
            if(strcmp(tableau[i].valeurMot, token) == 0 ){
                int count = tableau[i].nbOccurrences;
                tableau[i].positions[count] = positionIndex;
                tableau[i].nbOccurrences++;
                found = 1;
                break;
            }
        }
        if(!found){
            strcpy(tableau[nbmot].valeurMot, token);
            tableau[nbmot].nbOccurrences = 1;
            tableau[nbmot].positions[0] = positionIndex;
            nbmot++;
        }

        token = strtok(NULL, " ");
        positionIndex++;
    }

    return nbmot;
}
void afficherDictionnaire(struct MotInfo tableau[], int nbmot){    //fonction pour afficher
    if(nbmot == 0){
        printf("Aucun mot à afficher. Veuillez d'abord saisir un texte. \n");
    }
    else{
        printf("Liste des mots : \n");
        for (int i=0; i<nbmot; i++){
            printf("%s --> occurrences =  %d, longueur = %d, positions = [ ", tableau[i].valeurMot, tableau[i].nbOccurrences, 
            tableau[i].longueur);
            for(int j=0; j<tableau[i].nbOccurrences; j++){
                printf("%d ", tableau[i].positions[j]);
            }
            printf("]\n");
        }
    }
}

void rechercherMot(char searchMot[], struct MotInfo tab[], int nbmot){
    int found = 0;
    for(int i=0; i<nbmot; i++){
      if(strcmp(tab[i].valeurMot, searchMot) == 0){
        found = 1;
        printf("%s --> occurrences =  %d, longueur = %d, positions = [ ", tab[i].valeurMot, tab[i].nbOccurrences, tab[i].longueur);
        for(int j=0; j<tab[i].nbOccurrences; j++){
            printf("%d ", tab[i].positions[j]);
        }
        printf("]\n");
      }
    }
    if(!found){
        printf("Ce mot n'est pas trouve \n");
    }
}

void rechercherPartiel(char searchPartiel[], struct MotInfo tab[], int nbmot){
    int found = 0;
    for(int i=0; i<nbmot; i++){
      if(strstr(tab[i].valeurMot, searchPartiel) != NULL){
        found = 1;
        printf("%s --> occurrences =  %d, longueur = %d, positions = [ ", tab[i].valeurMot, tab[i].nbOccurrences, tab[i].longueur);
        for(int j=0; j<tab[i].nbOccurrences; j++){
            printf("%d ", tab[i].positions[j]);
        }
        printf("]\n");
      }
    }
    if(!found){
        printf("Aucun mot contenant '%s' n'a été trouvé.\n", rechercherPartiel);
    }
}

void trierParOrdreAlphabetique(struct MotInfo tab[], int nbmot){
    
    struct MotInfo temp;
    for(int i=0; i<nbmot; i++)
    {
        for(int j = i+1; j < nbmot; j++)
        {
            if(strcmp( tab[i].valeurMot, tab[j].valeurMot) > 0)
            {
                temp = tab[j];
                tab[j] = tab[i];
                tab[i] = temp;
            }
            
        }
    }

    afficherDictionnaire(tab, nbmot);
}

void trierParNbOccurrences(struct MotInfo tab[], int nbmot){
    
    struct MotInfo temp;
    for(int i=0; i<nbmot; i++)
    {
        for(int j = i+1; j < nbmot; j++)
        {
            if(tab[i].nbOccurrences < tab[j].nbOccurrences)
            {
                temp = tab[j];
                tab[j] = tab[i];
                tab[i] = temp;
            }
            
        }
    }

    afficherDictionnaire(tab, nbmot);
}

void trierParLongueur(struct MotInfo tab[], int nbmot){
    
    struct MotInfo temp;
    for(int i=0; i<nbmot; i++)
    {
        for(int j = i+1; j < nbmot; j++)
        {
            if(tab[i].longueur > tab[j].longueur)
            {
                temp = tab[j];
                tab[j] = tab[i];
                tab[i] = temp;
            }
            
        }
    }

    afficherDictionnaire(tab, nbmot);
}
 
int main()
{
    char text[2000];

    struct MotInfo tabMots[200];
    int nbMots = 0;

    int choix, souchoix;

    do
    {
        printf("\n===== Menu principal =====\n");
        printf("1. saisir texte et construire dictionnaire\n");
        printf("2. Afficher tous les mots (dictionnaire)\n");
        printf("3. Rechercher un mot exact\n");
        printf("4. Rechercher un mot partiel\n");
        printf("5. Trier les mots\n");
        printf("6. Statistiques globales\n");
        printf("7. Analyses par :\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            getchar();
            ///////
            printf("Entrez un texte : ");
            fgets(text, sizeof text, stdin);
            text[strcspn(text, "\n")] = '\0';
            ////////
            //saisirTexte(text);
            nbMots = construireDictionnaire(tabMots, nbMots, text);
            break;
        case 2:
            afficherDictionnaire(tabMots, nbMots);
            break;
        case 3:
            getchar();
            char searchMot[100];
            printf("Entrez le mot a cherche \n");
            fgets(searchMot, sizeof searchMot, stdin);
            searchMot[strcspn(searchMot, "\n")] = '\0';
            rechercherMot(searchMot, tabMots, nbMots);
            break;
        case 4:
            getchar();
            char searchPartiel[100];
            printf("Entrez le partiel a cherche \n");
            fgets(searchPartiel, sizeof searchPartiel, stdin);
            searchPartiel[strcspn(searchPartiel, "\n")] = '\0';
            rechercherPartiel(searchPartiel, tabMots, nbMots);
            break;
        case 5:
        
        do{
            printf("\n===== Trier les mots par : =====\n");
            printf("1. Ordre alphabetique \n");
            printf("2. Frequence (decroissante) \n");
            printf("3. Longueur (croissante) \n");
            printf("0. Reutour au menu principal \n");
            printf("Votre choix : ");
            scanf("%d", &souchoix);
            
            
             switch (souchoix)
                {
                case 1:
                    trierParOrdreAlphabetique(tabMots, nbMots);
                    break;
                case 2:
                    trierParNbOccurrences(tabMots, nbMots);
                    break;
                case 3:
                    trierParLongueur(tabMots, nbMots);
                    break;
                case 0:
                    
                    break;
                
                default:
                     printf("Choix invalide.\n");
                     break;
                }
            }
            while(souchoix != 0);  
                
            break;
        case 6:

            break;
        case 7:
            printf("\n===== Analyses par : =====\n");
            printf("1. Palindromes : \n");
            printf("2. Anagrammes : \n");
            printf("3. Nuage de mots : \n");
            printf("0. Routour le menu principale \n");
            printf("Votre choix : ");
            scanf("%d", &souchoix);
        /*    do{  switch (souchoix)
                {
                case 1:
                    
                    break;
                case 2:
                    
                    break;
                case 3:
                    
                    break;
                case 4:
                    
                    break;
                
                default:
                     
                     break;
                }  
            }
            while (souchoix != 0);*/
            
        case 0:
            printf("Quitter le programme.\n");
            break;
        default:
            printf("Choix invalide.\n");
            break;
        }
    } while (choix != 0);

    return 0;
}
