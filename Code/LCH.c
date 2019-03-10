#include "LCH.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : LCH.c                                                                               */
/* Date de création : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : manipuler les listes chainees                                                             */
/* ---------------------------------------------------------------------------------------------------- */

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
/*      on définie un pointeur sur une structure de type message_t à laquelle on alloue la mémoire      */ 
/*      nécéssaire                                                                                      */
/*      si il n'y a pas de problème d'allocation, on alloue la mémoire nécéssaire à l'espace contenant  */
/*      le texte du message                                                                             */
/*      si il n'y a pas de problème d'allocation on rentre dans la structure les valeurs des paramètres */
/*      en entrée                                                                                       */
/*      sinon on libere l'espace mémoire                                                                */
/*                                                                                                      */
/* Lexique:                                                                                             */
/*      taille_txt : entier donnant la longueure du message (nombre de caractère)                       */
/*      message : pointeur vers une structure de type message_t contenant le message créé               */
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
/* afficher_maillon             Affiche les champs d'un maillon message_t                               */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      message Le maillon à afficher                                                                   */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */  
/*      affiche respectivement les dates de début, de fin et le corps du message                            */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_maillon_LCH(message_t* message)
{
    printf("Date de début de validité du message : %d\n", message->date_deb);
    printf("Date de fin de validité du message : %d\n", message->date_fin);
    printf("Corps du message :\n%s\n", message->texte);   
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_LCH                 Affiche les champs d'une LCH message_t                                  */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete Le pointeur vers le maillon de tête de la LCH à afficher                                                    */
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe:                                                                                            */
/*      si la liste est non vide on la parcours et on appelle la fonction afficher_maillon_LCH sur      */
/*      chaque maillon, sinon on affiche qu'il n'y a aucin pessage                                      */
/*                                                                                                      */
/* Lexique :                                                                                            */
/*      cour : pointeur sur les maillons de la liste initialisé sur le premier élément. Il sert à       */
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
/* recherche_prec_triee        Recherche le précédent d'un élément dans une LCH message_t               */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      date_deb Un entier représentant la date de début de validation du message, critère pour         */
/* déterminer le précédent                                                                              */
/*      tete Un pointeur sur le pointeur de la tête de la LCH                                           */                                 
/*                                                                                                      */      
/* En sortie: Un pointeur vers le pointeur du précédent                                                 */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On utilise un premier pointeur servant à parcourire la liste et un pointeur de pointeur gardant */
/*      en mémoire l'adresse de l'élément précédent celui de l'autre pointeur                           */
/*                                                                                                      */
/* Lexique:                                                                                             */
/*      cour : pointeur sur les maillons de la liste initialisé sur le premier élément. Il sert à       */
/*      parcourir la liste                                                                              */
/*      prec : pointeur vers le pointeur précédent                                                      */
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
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On effectue le chainage du nouvelle élément en modifiant las valeur des pointeurs vers les      */
/*      éléments suivants                                                                               */
/* ---------------------------------------------------------------------------------------------------- */
void adj_cell_LCH(message_t **prec, message_t *nouv)
{
    nouv->suiv = *prec;
    *prec = nouv;
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