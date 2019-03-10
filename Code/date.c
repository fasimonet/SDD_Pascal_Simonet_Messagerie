#include "date.h"

/* ---------------------------------------------------------------------------------------------------- */
/* recuperer_date_courante       Recupere la date courante en la mettant au bon format                  */
/*                                                                                                      */
/* En entree: Aucune entree                                                                             */                                 
/*                                                                                                      */      
/* En sortie: La date courante correctement formattee                                                   */
/* ---------------------------------------------------------------------------------------------------- */
int recuperer_date_courante()
{
    time_t      timestamp = time(NULL);
    struct tm * t;
    int         date_formatee;
    int         annee;
    int         mois;
    int         jour;

    t=localtime(&timestamp);
    annee = t->tm_year + 1900;
    mois = t->tm_mon + 1;
    jour = t->tm_mday;

    date_formatee = annee;
    date_formatee = (date_formatee*100 + mois)*100 + jour;

    return date_formatee;
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_date_courante                             Affiche la date courante                          */
/*                                                                                                      */
/* En entree: Aucune entree                                                                             */                              
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_date_courante()
{
    int date = recuperer_date_courante();
    printf("Date : %d\n", date);
}