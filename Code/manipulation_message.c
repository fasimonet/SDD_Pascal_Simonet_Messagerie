#include "LCH.h"
#include "message.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : manipulation_message.c                                                              */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : realiser les tests sur les fonctions de manipulation de messages                          */
/* ---------------------------------------------------------------------------------------------------- */

int main()             
{
    // test afficher message non expirer
    message_t     * t = lire_fichier("fic2.txt");
    afficher_messages_non_expires(t);

    // test afficher si motif
    afficher_messages_si_motif(t, "Ca va ?"); // le motif n'est pas dans la liste
    afficher_messages_si_motif(t, "Joyeux");// le motif est dans la liste

    // test supprimer message obsolete
    supprimer_messages_obsoletes(&t);
    afficher_LCH(t);

    return 0;
}