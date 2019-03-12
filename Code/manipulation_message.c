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
    // Test 1 : afficher messages non expires
    message_t     * t = lire_fichier("fic2.txt");
    afficher_messages_non_expires(t);

    // Test 2 : afficher si motif
    afficher_messages_si_motif(t, "Ca va ?"); // le motif n'est pas dans la liste
    afficher_messages_si_motif(t, "Joyeux");// le motif est dans la liste

    // Test 3 : supprimer message obsolete
    supprimer_messages_obsoletes(&t);
    afficher_LCH(t);

    // Test 4 : mettre a jour avec une nouvelle date de debut
    mettre_a_jour_messages(20000101, 11111111, &t);
    afficher_LCH(t);

    return 0;
}