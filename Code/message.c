#include "message.h"
#include "date.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : message.c                                                                           */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : manipuler les messages                                                                    */
/* Fonctions :                                                                                          */
/*  - afficher_messages_non_expires                                                                     */
/*  - supprimer_messages_obsoletes                                                                      */
/*  - afficher_messages_si_motif                                                                         */
/*  - lire_fichier                                                                                      */
/*  - sauv_fichier                                                                                      */
/* ---------------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_messages_non_expires            Affiche les messages non expires d'une LCH message_t        */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      tete Le maillon de tete de la LCH a afficher                                                    */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On recupere la date courante                                                                    */
/*      Si la liste est non vide                                                                        */
/*          Tant que la date de fin du message n'est pas depassee                                       */
/*              On parcourt la liste en appelant sur chaque maillon la fonction afficher_maillon_LCH    */
/*                                                                                                      */
/*                                                                                                      */
/* Lexique :                                                                                            */
/*      nb : entier contenant le numero du message a afficher                                           */
/*      cour : pointeur sur les maillons de la liste initialise sur le premier element. Il sert a       */
/*      parcourir la liste                                                                              */
/*      date_courante :  entier de la forme AAAAMMJJ contenant la date courante                         */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_messages_non_expires(message_t* tete)
{
    int         nb = 1;
    message_t * cour = tete;
    int         date_courante = recuperer_date_courante();

    printf("====================================================================\n");
    printf("\t\tAFFICHAGES DES MESSAGES NON EXPIRES\n");
    printf("====================================================================\n\n");

    if (cour == NULL)
    {
        printf("Aucun message n'est valide\n");
    }
    else 
    {
        while (cour != NULL)
        {
            if (cour->date_fin >= date_courante)
            {
                printf("==================================\n");
                printf("\tMessage n°%d\n", nb);
                printf("==================================\n");
                afficher_maillon_LCH(cour);
                printf("\n");
                nb++;
            }
            cour = cour->suiv;
        }
    }    
}

/* ---------------------------------------------------------------------------------------------------- */
/* supprimer_messages_obsoletes             Supprime les messages obsoletes d'une LCH                   */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      tete le pointeur vers le pointeur de la tete                                                    */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void supprimer_messages_obsoletes(message_t** tete)
{
    message_t     * cour = *tete;
    message_t    ** prec = tete;
    int date_auj = recuperer_date_courante();

    while (cour != NULL)
    {
        if (cour->date_fin < date_auj)
        {
            supprimer_maillon_LCH(prec);
        }
        else 
        {
            prec = &cour->suiv;
        }
        cour = cour->suiv;
    }
}


void mettre_a_jour_messages(int old_date_deb, int new_date_deb, message_t** tete)
{
    message_t   * cour = *tete;
    
    while(cour != NULL)
    {
        if (cour->date_deb == old_date_deb)
        {
            cour->date_deb = new_date_deb;
        }
        cour = cour->suiv;
    }
    sauv_fichier("maj.txt", *tete);
    liberer_LCH(*tete);
    *tete = lire_fichier("maj.txt");
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_message_si_motif                    Affiche les messages contenant un motif                     */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      tete le pointeur de tete                                                                        */
/*      motif le motif a respecter                                                                      */
/*                                                                                                      */
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_messages_si_motif(message_t* tete, char* motif)
{
    message_t * cour = tete;
    int         nb = 0;

    printf("====================================================================\n");
    printf("\t\tAFFICHAGES DES MESSAGES CONTENANT UN MOTIF\n");
    printf("====================================================================\n\n");
    printf("Le motif verifie est : \"%s\"\n\n", motif);
    while (cour != NULL)
    {
        // Reecrire strstr
        if (strstr(cour->texte, motif))
        {
            nb++;
            printf("==================================\n");
            printf("\tMessage n°%d\n", nb);
            printf("==================================\n");
            afficher_maillon_LCH(cour);
            printf("\n");
        } 
        cour = cour->suiv;
    }
    if (nb == 0)
    {
        printf("Aucun message ne contient le motif : \"%s\"\n\n", motif);
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* lire_fichier         Lit le fichier passe en parametre et construit une LCH avec son contenu         */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      nom Nom du fichier a lire                                                                       */                          
/*                                                                                                      */      
/* En sortie: La nouvelle LCH                                                                           */
/*                                                                                                      */
/* Principe :                                                                                           */ 
/*      Si on n'a pas de probleme d'ouverture de fichier                                                */
/*          on lit les premieres dates du fichier que l'on stocke dans des variables                    */
/*          tant que l'on est pas a la fin du fichier                                                   */
/*              on recupere le texte du message dans un tableau de taille 100                           */
/*              on alloue l'espace necessaire puis on copie le contenu du tableau a cet endroit si      */
/*              il n'y a pas eu de probleme d'allocation                                                */
/*              on appelle la fonction creer_maillon_LCH avec les dates et le tableau sur mesure        */
/*              on appelle la fonction rech_prec_triee_LCH avec la date et la tete de la liste          */
/*              on appelle la fonction adj_cell_LCH avec les resulats des deux fonctions precedentes    */
/*              si il a ete alloue on libere l'espace du tableau sur mesure                             */
/*              on lit les dates suivantes                                                              */
/*          on ferme le fichier                                                                         */
/*      on retourne la tete de la liste chainee                                                         */
/*                                                                                                      */
/* Lexique                                                                                              */
/*      t : pointeur de tete vers la nouvelle liste chainee                                             */
/*      nouv : pointeur vers les nouveaux elements a entrer dans la liste                               */
/*      prec : pointeur vers le pointeur du precedent                                                   */
/*      date_deb : entier stockant la date de debut du nouvel element a inserer                         */
/*      date_fin : entier stockant la date de fin du nouvel element a inserer                           */
/*      texte : tableau lisant au maximum 100 caracteres du fichier composant le corps du message       */
/*      texte_redim : pointeur vers un tableau de characteres de taille optimale par rapport au message */
/*      flot : structure representant le fichier                                                        */
/* ---------------------------------------------------------------------------------------------------- */
message_t* lire_fichier(char *nom)
{
    message_t     * t = NULL;
    message_t     * nouv;
    message_t    ** prec;
    int             date_deb;
    int             date_fin;
    char            texte[101];
    char          * texte_redim;
    FILE          * flot;

    flot = fopen(nom, "r");
    if (flot == NULL)
    {
        printf("Pb d'ouverture du fichier %s en lecture\n", nom);
    }
    else 
    {
        fscanf(flot, "%d %d", &date_deb, &date_fin);
        while (!feof(flot))
        {
            fseek(flot, 1, SEEK_CUR);
            fgets(texte, 101, flot);
            texte_redim = (char *) malloc(strlen(texte));

            if(texte_redim)
            {
                strcpy(texte_redim, texte);
                texte_redim[strlen(texte)-1] = '\0';
            } 
            nouv = creer_maillon_LCH(date_deb, date_fin, texte_redim);
            prec = rech_prec_triee_LCH(date_deb, &t);
            adj_cell_LCH(prec, nouv);
            if(texte_redim){
                free(texte_redim);
                texte_redim = NULL;
            } 
            fscanf(flot, "%d %d", &date_deb, &date_fin);
        }
        fclose(flot);
    }
    return t;
}

/* ---------------------------------------------------------------------------------------------------- */
/* sauv_fichier           Sauvegarde une LCH message_t dans un fichier non binaire                      */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      nom Le nom du fichier a editer                                                                  */
/*      tete Un pointeur vers le premier element de la LCH                                              */                             
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      Si on n'a pas de probleme d'ouverture de fichier en ecriture                                    */
/*          On parcourt la liste en ecrivant dans le fichier les maillons separes par des               */
/*          retours a la ligne. Les elements du maillon sont separes par des espaces                    */
/*                                                                                                      */
/* Lexique :                                                                                            */
/*      cour : pointeur sur les maillons de la liste initialise sur le premier element. Il sert a       */
/*      parcourir la liste                                                                              */
/*      flot : structure representant le fichier                                                        */
/* ---------------------------------------------------------------------------------------------------- */
void sauv_fichier(char *nom, message_t *tete)
{
    FILE      * flot;
    message_t * cour;

    cour = tete;
    flot = fopen(nom, "w");
    if (flot == NULL)
    {
        printf("Pb d'ouverture du fichier %s en ecriture\n", nom);
    }
    else 
    {
        while (cour != NULL)
        {
            fprintf(flot, "%d %d %s\n", cour->date_deb, cour->date_fin, cour->texte);
            cour = cour->suiv;
        }
        fclose(flot);
    }
}