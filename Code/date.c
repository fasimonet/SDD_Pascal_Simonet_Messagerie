#include "date.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : date.c                                                                              */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : manipuler les dates                                                                       */
/* Fonctions :                                                                                          */
/*  - recuperer_date_courante                                                                           */
/* ---------------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------------- */
/* recuperer_date_courante       Recupere la date courante en la mettant au bon format                  */
/*                                                                                                      */
/* En entree: Aucune entree                                                                             */                                 
/*                                                                                                      */      
/* En sortie: La date courante correctement formattee                                                   */
/*                                                                                                      */
/* Principe                                                                                             */
/*      On recupere la date courante                                                                    */
/*      On recupere le nombre d'annee que l'on multiplie par 100                                        */
/*      On lui additionne le nombre de mois puis on multiplie encors une fois par 100                   */
/*      On lui ajoute le nombre de jours                                                                */     
/*                                                                                                      */
/* Lexique                                                                                              */
/*      timestamp : variable de type time_t issue de la librairie time.h contenant la date et l'heure   */
/*      courante                                                                                        */
/*      t : pointeur sur la structure date de la librairie time.h. Cette structure permet de recuperer  */
/*      des informations sur la date                                                                    */
/*      annee : entier contenant l'annee en cours                                                       */
/*      mois : entier contenant le mois en cours                                                        */
/*      jour : entier contenant le jour en cours                                                        */
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
