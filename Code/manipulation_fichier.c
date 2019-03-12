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
    // Test 1 : lire un fichier inexistant
    //message_t     * tete_test1 = lire_fichier("existepas.txt");

    // Test 2 : lire un fichier vide
    message_t     * tete_test2 = lire_fichier("fichier_test_fichier_vide.txt");
    afficher_LCH(tete_test2);

    // Test 3 : lire un fichier non vide
    message_t     * tete_test3 = lire_fichier("fichier_test_lecture.txt");
    afficher_LCH(tete_test3);

    // Test 4 : sauvegarder dans un fichier
    message_t     * tete_test4 = lire_fichier("fichier_test_lecture.txt");
    sauv_fichier("fichier_test_stockage", tete_test4);


    // teste lecture de fichier avec élément de plus de 100 caractere
    /*message_t     * t = lire_fichier("fichier_test_lecture");
    afficher_LCH(t);
    //teste de stockage dans un fichier
    char          * nom;
    fscanf(stdin,"%s", nom);
    sauv_fichier(nom,t);*/
    return 0;
}