#include "LCH.h"

/* ---------------------------------------------------------------------------------------------------- */
/* creer_maillon                   Crée un maillon message_t                                            */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      date_deb Un entier représentant la date de début de validité du message                         */
/*      date_fin Un entier représentant la date de fin de validité du message                           */
/*      texte Une chaine de caractère représentant le texte du message                                  */
/*                                                                                                      */      
/* En sortie: Un pointeur vers le maillon nouvellement créé                                             */
/*                                                                                                      */
/* Principe:                                                                                            */
/*                                                                                                      */
/* Lexique:                                                                                             */
/*      
/* ---------------------------------------------------------------------------------------------------- */
message_t* creer_maillon_LCH(int date_deb, int date_fin, char* texte)
{
    int         taille_txt = strlen(texte);
    message_t * message = (message_t *) malloc(sizeof(message_t));
    if (message == NULL)
    {
        printf("Pb allocation mémoire maillon message_t\n");
    }
    else 
    {
        message->texte = (char *) malloc(sizeof(char)*taille_txt +1);
        if (message->texte == NULL)
        {
            printf("Pb allocation mémoire tableau texte\n");
            free(message);
            message = NULL;
        }
        else 
        {
            message->date_deb = date_deb;
            message->date_fin = date_fin;
            strcpy(message->texte, texte);
            message->texte[taille_txt+1] = "\0";
        }
    }

    return message;
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_maillon             Affiche les champs d'un maillon message_t                               */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      message Le maillon à afficher                                                                 */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_maillon_LCH(message_t message)
{
    printf("Date de début de validité du message : %d\n", message.date_deb);
    printf("Date de fin de validité du message : %d\n", message.date_fin);
    printf("Corps du message :\n%s\n", message.texte);   
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_LCH                 Affiche les champs d'une LCH message_t                                  */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete Le maillon de tête de la LCH à afficher                                                    */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_LCH(message_t tete)
{
    int         nb = 1;
    message_t * cour = &tete;

    printf("====================================================================\n");
    printf("\t\tAFFICHAGE DE TOUS LES MESSAGES\n");
    printf("====================================================================\n\n");

    if (cour == NULL)
    {
        printf("Il n'y a aucun message\n");
    }
    else 
    {
        while (cour != NULL)
        {
            printf("==================================\n");
            printf("\tMessage n°%d\n", nb);
            printf("==================================\n");
            afficher_maillon_LCH(*cour);
            cour = cour->suiv;
            printf("\n");
            nb++;
        }
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* recherche_prec_triee        Recherche le précédent d'un élément dans une LCH message_t               */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      date_deb Un entier représentant la date de début de validation du message, critère pour         */
/* déterminer le précédent                                                                              */
/*      tete Un pointeur sur le pointeur de la tête de la LCH                                           */                                 
/*                                                                                                      */      
/* En sortie: Un pointeur vers le pointeur du précédent                                                 */
/* ---------------------------------------------------------------------------------------------------- */
message_t** rech_prec_triee_LCH(int date_deb, message_t** tete)
{
    message_t      * cour = *tete;
    message_t     ** prec = tete;
    while (cour != NULL && cour->date_deb < date_deb)
    {
        prec = &cour->suiv;
        cour = cour->suiv;
    }
    
    return prec;
}

/* ---------------------------------------------------------------------------------------------------- */
/* adj_cell                     Ajoute un maillon dans la LCH message_t                                 */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      prec Un pointeur vers un pointeur de l'élément précédant le nouvel élément à ajouter            */
/*      nouv Un pointeur sur le nouvel élément à ajouter                                                */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void adj_cell_LCH(message_t **prec, message_t *nouv)
{
    nouv->suiv = *prec;
    *prec = nouv;
}

/* ---------------------------------------------------------------------------------------------------- */
/* lire_fichier         Lit le fichier passé en paramètre et construit une LCH avec son contenu         */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      nom Nom du fichier à lire                                                                       */                          
/*                                                                                                      */      
/* En sortie: La nouvelle LCH                                                                             */
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
/* En entrée:                                                                                           */
/*      nom Le nom du fichier à éditer                                                                  */
/*      tete Un pointeur vers le premier élément de la LCH                                              */                             
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void sauv_fichier(char *nom, message_t *tete)
{
    FILE      * flot;
    int         taille;
    message_t * cour;

    cour = tete;
    flot = fopen(nom, "w");
    if (flot == NULL)
    {
        printf("Pb d'ouverture du fichier %s en écriture\n", nom);
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

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_messages_non_expires            Affiche les messages non expirés d'une LCH message_t        */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete Le maillon de tête de la LCH à afficher                                                    */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_messages_non_expires(message_t tete)
{
    int         nb = 1;
    message_t * cour = &tete;
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
                afficher_maillon_LCH(*cour);
                printf("\n");
                nb++;
            }
            cour = cour->suiv;
        }
    }    
}

/* ---------------------------------------------------------------------------------------------------- */
/* supprimer_maillon                            Supprime un maillon d'une LCH                           */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      prec le pointeur vers le pointeur de l'élément à supprimer                                      */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void supprimer_maillon_LCH(message_t** prec)
{
    message_t * cour = *prec;

    *prec = (*prec)->suiv;
    free(cour->texte);
    free(cour);
}

/* ---------------------------------------------------------------------------------------------------- */
/* supprimer_messages_obsoletes             Supprime les messages obsolètes d'une LCH                   */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete le pointeur vers le pointeur de la tête                                                    */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void supprimer_messages_obsoletes_LCH(message_t** tete)
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
        prec = &cour->suiv;
        cour = cour->suiv;
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* liberer_LCH                                  Libère une LCH                                          */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete le pointeur de tête                                                                        */
/*                                                                                                      */
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void liberer_LCH(message_t* tete)
{
    message_t * cour = tete;
    while (tete != NULL)
    {
        tete = tete->suiv;
        free(cour->texte);
        free(cour);
        cour = tete;
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_si_motif_LCH                    Affiche les messages contenant un motif                     */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete le pointeur de tête                                                                        */
/*      motif le motif à respecter                                                                      */
/*                                                                                                      */
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_si_motif_LCH(message_t* tete, char* motif)
{
    message_t * cour = tete;
    int         nb = 0;

    printf("====================================================================\n");
    printf("\t\tAFFICHAGES DES MESSAGES CONTENANT UN MOTIF\n");
    printf("====================================================================\n\n");
    printf("Le motif vérifié est : \"%s\"\n\n", motif);
    while (cour != NULL)
    {
        // Réécrire strstr
        if (strstr(cour->texte, motif))
        {
            nb++;
            printf("==================================\n");
            printf("\tMessage n°%d\n", nb);
            printf("==================================\n");
            afficher_maillon_LCH(*cour);
            printf("\n");
        } 
        cour = cour->suiv;
    }
    if (nb == 0)
    {
        printf("Aucun message ne contient le motif : \"%s\"\n\n", motif);
    }
}