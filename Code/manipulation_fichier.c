#include "LCH.h"
#include "message.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : manipulation_fichier.c                                                              */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : realiser les tests sur les fonctions de manipulation de fichiers de messages              */
/* ---------------------------------------------------------------------------------------------------- */

int main()            
{
    // teste lecture de fichier avec élément de plus de 100 caractere
    message_t     * t = lire_fichier("fichier_test_lecture");
    afficher_LCH(t);
    //teste de stockage dans un fichier
    char          * nom;
    fscanf(stdin,"%s", nom);
    sauv_fichier(nom,t);
    return 0;
}