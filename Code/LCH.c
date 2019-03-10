#include "LCH.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : LCH.c                                                                               */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : manipuler les listes chainees                                                             */
/* Fonctions :                                                                                          */
/*  - creer_maillon_LCH                                                                                 */
/*  - afficher_maillon_LCH                                                                              */
/*  - afficher_LCH                                                                                      */
/*  - rech_prec_triee_LCH                                                                               */
/*  - adj_cell_LCH                                                                                      */
/*  - supprimer_maillon_LCH                                                                             */
/*  - liberer_LCH                                                                                       */
/* ---------------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------------- */
/* creer_maillon_LCH                   Cree un maillon message_t                                        */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      date_deb Un entier representant la date de debut de validite du message                         */
/*      date_fin Un entier representant la date de fin de validite du message                           */
/*      texte Une chaine de caractere representant le texte du message                                  */
/*                                                                                                      */      
/* En sortie: Un pointeur vers le maillon nouvellement cree                                             */
/*                                                                                                      */
/* Principe:                                                                                            */
/*      on definit un pointeur sur une structure de type message_t a laquelle on alloue la memoire      */ 
/*      necessaire                                                                                      */
/*      si il n'y a pas de probleme d'allocation, on alloue la memoire necessaire a l'espace contenant  */
/*      le texte du message                                                                             */
/*      si il n'y a pas de probleme d'allocation on rentre dans la structure les valeurs des parametres */
/*      en entree                                                                                       */
/*      sinon on libere l'espace memoire                                                                */
/*                                                                                                      */
/* Lexique:                                                                                             */
/*      taille_txt : entier donnant la longueur du message (nombre de caracteres)                       */
/*      message : pointeur vers une structure de type message_t contenant le message cree               */
/* ---------------------------------------------------------------------------------------------------- */
message_t* creer_maillon_LCH(int date_deb, int date_fin, char* texte)
{
    int         taille_txt = strlen(texte);
    message_t * message = (message_t *) malloc(sizeof(message_t));
    if (message == NULL)
    {
        printf("Pb allocation memoire maillon message_t\n");
    }
    else 
    {
        message->texte = (char *) malloc(sizeof(char)*taille_txt +1);
        if (message->texte == NULL)
        {
            printf("Pb allocation memoire tableau texte\n");
            free(message); // ???
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
/* afficher_maillon_LCH             Affiche les champs d'un maillon message_t                           */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      message Le maillon a afficher                                                                   */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */  
/*      affiche respectivement les dates de debut, de fin et le corps du message                        */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_maillon_LCH(message_t* message)
{
    printf("Date de debut de validite du message : %d\n", message->date_deb);
    printf("Date de fin de validite du message : %d\n", message->date_fin);
    printf("Corps du message :\n%s\n", message->texte);   
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_LCH                 Affiche les champs d'une LCH message_t                                  */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      tete Le pointeur vers le maillon de tete de la LCH a afficher                                   */
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe:                                                                                            */
/*      si la liste est non vide on la parcourt et on appelle la fonction afficher_maillon_LCH sur      */
/*      chaque maillon, sinon on affiche qu'il n'y a aucun message                                      */
/*                                                                                                      */
/* Lexique :                                                                                            */
/*      cour : pointeur sur les maillons de la liste initialise sur le premier element. Il sert a       */
/*      parcourir la liste                                                                              */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_LCH(message_t* tete)
{
    message_t * cour = tete;
    int nb = 1;

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
            afficher_maillon_LCH(cour);
            cour = cour->suiv;
            printf("\n");
            nb++;
        }
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* recherche_prec_triee_LCH        Recherche le precedent d'un element dans une LCH message_t           */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      date_deb Un entier representant la date de debut de validation du message, critere pour         */
/* determiner le precedent                                                                              */
/*      tete Un pointeur sur le pointeur de la tete de la LCH                                           */                                 
/*                                                                                                      */      
/* En sortie: Un pointeur vers le pointeur du precedent                                                 */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On utilise un premier pointeur servant a parcourir la liste et un pointeur de pointeur gardant  */
/*      en memoire l'adresse de l'element precedant celui de l'autre pointeur                           */
/*                                                                                                      */
/* Lexique:                                                                                             */
/*      cour : pointeur sur les maillons de la liste initialise sur le premier element. Il sert a       */
/*      parcourir la liste                                                                              */
/*      prec : pointeur vers le pointeur precedent                                                      */
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
/* adj_cell_LCH                     Ajoute un maillon dans la LCH message_t                             */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      prec Un pointeur vers un pointeur de l'element precedant le nouvel element a ajouter            */
/*      nouv Un pointeur sur le nouvel element a ajouter                                                */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On effectue le chainage du nouvel element en modifiant las valeurs des pointeurs vers les       */
/*      elements suivants                                                                               */
/* ---------------------------------------------------------------------------------------------------- */
void adj_cell_LCH(message_t **prec, message_t *nouv)
{
    nouv->suiv = *prec;
    *prec = nouv;
}

/* ---------------------------------------------------------------------------------------------------- */
/* supprimer_maillon                            Supprime un maillon d'une LCH                           */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      prec le pointeur vers le pointeur de l'element a supprimer                                      */                                 
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
/* liberer_LCH                                  Libere une LCH                                          */
/*                                                                                                      */
/* En entree:                                                                                           */
/*      tete le pointeur de tete                                                                        */
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