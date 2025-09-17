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

void supprimerPonctuation(char text[]){          //fonction pour nettoye les ponctuation entre les mots
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

int construireDictionnaire(struct MotInfo tableau[], int nbmot, char text[])   //fonction pour construire le dictionnaire
{   
    int positionIndex = 1;

    mettreEnMinuscules(text);                             
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
        printf("Aucun mot a afficher. Veuillez d'abord saisir un texte. \n");
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

void rechercherMot(char searchMot[], struct MotInfo tab[], int nbmot){     //fonction pour rechercher mot
    mettreEnMinuscules(searchMot);                           
    supprimerPonctuation(searchMot);
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

void rechercherPartiel(char searchPartiel[], struct MotInfo tab[], int nbmot){     //fonction pour rechercher partiel 
    mettreEnMinuscules(searchPartiel);                             
    supprimerPonctuation(searchPartiel);
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

void trierParOrdreAlphabetique(struct MotInfo tab[], int nbmot){    //fonction pour trier alphabetique
    
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

void trierParNbOccurrences(struct MotInfo tab[], int nbmot){        //fonction pour trier par nombre d'occurrences
    
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

void trierParLongueur(struct MotInfo tab[], int nbmot){         //fonction pour trier par la longueur
    
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
 
void statistiquesGlobales(struct MotInfo tableau[], int nbmot) {       //fonction pour calculer et affiche les statistique
    if(nbmot == 0) {
        printf("Aucun mot saisi.\n");
        return;
    }

    int total = 0;
    int sommeLongueurs = 0;

    
    struct MotInfo plusLong = tableau[0];
    struct MotInfo plusCourt = tableau[0];
    struct MotInfo plusFrequent = tableau[0];

    for(int i=0; i<nbmot; i++) {
        total += tableau[i].nbOccurrences;
        sommeLongueurs += tableau[i].longueur;
    }
    
    for(int i=1; i<nbmot; i++){
        if(tableau[i].longueur > plusLong.longueur)
            plusLong = tableau[i];

        if(tableau[i].longueur < plusCourt.longueur)
            plusCourt = tableau[i];

        if(tableau[i].nbOccurrences > plusFrequent.nbOccurrences)
            plusFrequent = tableau[i];
    }

    float diversite = (float)nbmot / total;
    float longueurMoyenne = (float)sommeLongueurs / nbmot;    

    printf("\n--- Statistiques Globales ---\n");
    printf("Nombre total de mots       : %d\n", total);
    printf("Nombre de mots uniques     : %d\n", nbmot);
    printf("Diversite lexicale         : %.2f\n", diversite);
    printf("Longueur moyenne (unique)  : %.2f\n", longueurMoyenne);
    printf("Mot le plus long           : %s (%d)\n", plusLong.valeurMot, plusLong.longueur);
    printf("Mot le plus court          : %s (%d)\n", plusCourt.valeurMot, plusCourt.longueur);
    printf("Mot le plus frequent       : %s (%d)\n", plusFrequent.valeurMot, plusFrequent.nbOccurrences);
}

int estPalindrome(char mot[]){          //palindrome fonction 
    int gauche = 0;
    int droit = strlen(mot)-1;
    while (gauche < droit)
    {
        if(mot[gauche] != mot[droit]){
            return 0; // pas palindtrome
        }
        gauche++;
        droit--;
    }
    return 1;    // est palidrome    
}

void palindromeMot(struct MotInfo tableau[], int nbmot){    //fonction pour checker le mot si palindrome ou non
    int found = 0;
    printf("\n--- Mots Palindromes ---\n");
    for(int i=0; i<nbmot; i++){
        if(estPalindrome(tableau[i].valeurMot) == 1){
            found = 1;
            printf("%s --> occurrences = %d, longueur = %d\n", 
                tableau[i].valeurMot, tableau[i].nbOccurrences, tableau[i].longueur);
        }
    }
    if(!found){
        printf("Aucun mot palindrome trouve.\n");
    }
}

void trierLettres(char mot[]){         //fonction pour trier alphabetique les caracteres de mot pour utiliser dans anagrammes
    int lon = strlen(mot);
    char temp;
    for(int i = 0; i < lon; i++){
        for(int j = i+1; j < lon; j++){
            if(mot[i] > mot[j]){
                temp = mot[i];
                mot[i] = mot[j];
                mot[j] = temp;
            }
        }
    }
}

int sontAnagramme(char mot1[], char mot2[]){   //fonction pour checker deux mots si anagramme ou non
    if (strlen(mot1) != strlen(mot2)){
        return 0;
    }
    char copie1[100], copie2[100];
    strcpy(copie1, mot1);              //on cree des copies pour ne pas modifier les mots originaux
    strcpy(copie2, mot2);

    trierLettres(copie1);          // trier alphabetique les lettres de chaque mot avec le fonction trierLettres
    trierLettres(copie2);

    if ( strcmp(copie1, copie2) == 0){       //comparaison les deux mots
        return 1;
    }
    else{
        return 0;
    }

}

void anagrammesMots(struct MotInfo tab[], int nbmot){  //fonction pour rechercher les groupes anagrammes dans le tableau structure
    int found = 0;
    printf("\n--- Groupes Anagrammes ---\n");
    for(int i=0; i<nbmot; i++){
        for(int j = i+1; j<nbmot; j++){
            if( sontAnagramme(tab[i].valeurMot, tab[j].valeurMot) == 1){
                found = 1;
                printf("%s <--> %s \n", tab[i].valeurMot, tab[j].valeurMot); 
            }                                                                    
        }
    }
    if(!found){
        printf("Aucun Anagramme trouve. \n");
    }
}

void nuageDeMots(struct MotInfo tab[], int nbMot){    //fonction pour nuage les mots
    printf("\n--- Nuage de mots ---\n");
    for (int i=0; i<nbMot; i++){
        printf("%s : ",tab[i].valeurMot);
        for(int j=0; j<tab[i].nbOccurrences; j++){
            printf("*");
        }
        printf("\n");
    }
}

int reinitialiserTableau(struct MotInfo tab[], int nbMot){    //fonction pour reinitialiser le tableau avant le nouveau saisie
    for (int i = 0; i < nbMot; i++){
        tab[i].valeurMot[0] = '\0';
        tab[i].longueur = 0;
        tab[i].nbOccurrences = 0;
        for(int j=0; j<500; j++){
            tab[i].positions[j] = 0;
        }
    }
    return 0;
}

        

int main()
{

    char text[2000];

    struct MotInfo tabMots[200];
    int nbMots = 0;

    int choix, souchoix;

    do
    {
        printf("\n");
        printf("=============================================\n");
        printf("             MENU PRINCIPAL \n");
        printf("=============================================\n");
        printf(" 1.  Saisir texte et construire dictionnaire\n");
        printf(" 2.  Afficher tous les mots (dictionnaire)\n");
        printf(" 3.  Rechercher un mot exact\n");
        printf(" 4.  Rechercher un mot partiel\n");
        printf(" 5.  Trier les mots\n");
        printf(" 6.  Statistiques globales\n");
        printf(" 7.  Analyses par\n");
        printf(" 0.  Quitter\n");
        printf("=============================================\n");
        printf("  Votre choix : ");

        scanf("%d", &choix);
        printf("=============================================\n");

        switch (choix)
        {
        case 1:
            getchar();
            printf("Entrez un texte : ");
            fgets(text, sizeof text, stdin);
            text[strcspn(text, "\n")] = '\0';
            nbMots = reinitialiserTableau(tabMots, nbMots);
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
            printf("\n");
            printf("=====================================\n");
            printf("        Trier les mots par : \n");
            printf("=====================================\n");
            printf("1. Ordre alphabetique \n");
            printf("2. Frequence (decroissante) \n");
            printf("3. Longueur (croissante) \n");
            printf("0. Reutour au menu principal \n");
            printf("=====================================\n");
            printf("Votre choix : ");
            scanf("%d", &souchoix);
            printf("=====================================\n");

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
            statistiquesGlobales(tabMots, nbMots);
            break;
        case 7:
        do{
            printf("\n===== Analyses par : =====\n");
            printf("1. Palindromes : \n");
            printf("2. Anagrammes : \n");
            printf("3. Nuage de mots : \n");
            printf("0. Routour le menu principale \n");
            printf("Votre choix : ");
            scanf("%d", &souchoix);
        
            switch (souchoix)
                {
                case 1:
                    palindromeMot(tabMots, nbMots);  
                    break;
                case 2:
                    anagrammesMots(tabMots, nbMots);
                    break;
                case 3:
                    nuageDeMots(tabMots, nbMots);
                    break;
                case 0:                    
                    break;
                default:
                    printf("Choix invalide.\n");
                     break;
                }  
            }
            while (souchoix != 0);
            
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
