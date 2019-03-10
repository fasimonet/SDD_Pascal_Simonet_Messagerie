#include "date.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : manipulation_date.c                                                                 */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : realiser les tests sur les fonctions de manipulation de dates                             */
/* ---------------------------------------------------------------------------------------------------- */

int main()
{
    // teste des fonctions de récupération et d'affichage de date
    int x;
    x = recuperer_date_courante();
    printf("Date : %d\n",x);
    printf("Test fonction affichage \n");
    afficher_date_courante();
    return 0;
}