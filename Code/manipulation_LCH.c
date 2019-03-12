#include "LCH.h"

/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : manipulation_LCH.c                                                                  */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : realiser les tests sur les fonctions de manipulation de listes chainees                   */
/* ---------------------------------------------------------------------------------------------------- */

int main()           
{
    // Test 1 : creer maillon (cas general)
    message_t *nouv_test1 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !"); 
    
    // Test 2 : recherche du precedent lorsque ce dernier est en tete de liste
    message_t *tete_test2 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !");
    message_t **prec_test2 = rech_prec_triee_LCH(20160710, &tete_test2);

    // Test 3 : recherche du precedent dans le cas général
    message_t *tete_test3 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !");
    message_t **prec_test3_1 = rech_prec_triee_LCH(20160710, &tete_test3);
    message_t *nouv_test3 = creer_maillon_LCH(22220505, 24540909, "Brrr");
    adj_cell_LCH(prec_test3_1, nouv_test3);
    message_t **prec_test3_2 = rech_prec_triee_LCH(22220505, &tete_test3);

    // Test 4 : ajouter dans liste vide 
    message_t *tete_test4 = NULL; 
    message_t *nouv_test4 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !");   
    message_t **prec = rech_prec_triee_LCH(20160710, &tete_test4);
    adj_cell_LCH(prec, nouv_test4);

    // Test 5 : ajouter en tete de liste
    message_t *tete_test5 = NULL; 
    message_t *nouv_test5_1 = creer_maillon_LCH(22220505, 24540909, "Brrr");  
    message_t **prec_test_5_1 = rech_prec_triee_LCH(22220505, &tete_test5);
    adj_cell_LCH(prec_test_5_1, nouv_test5_1);
    message_t *nouv_test5_2 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !");
    message_t **prec_test_5_2 = rech_prec_triee_LCH(20160710, &tete_test5); 
    adj_cell_LCH(prec_test_5_2, nouv_test5_2);

    // Test 6 : ajouter dans une position quelconque
    message_t *tete_test6 = NULL; 
    message_t *nouv_test6_1 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !"); 
    message_t **prec_test_6_1 = rech_prec_triee_LCH(20160710, &tete_test6);
    adj_cell_LCH(prec_test_6_1, nouv_test6_1);
    message_t *nouv_test6_2 = creer_maillon_LCH(22220505, 24540909, "Brrr"); 
    message_t **prec_test_6_2 = rech_prec_triee_LCH(22220505, &tete_test6); 
    adj_cell_LCH(prec_test_6_2, nouv_test6_2);

    // Test 7 : supprimer maillon dans une liste non vide
    message_t *tete_test7 = NULL; 
    message_t *nouv_test7_1 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !"); 
    message_t **prec_test_7 = rech_prec_triee_LCH(20160710, &tete_test7);
    adj_cell_LCH(prec_test_7, nouv_test7_1);
    supprimer_maillon_LCH(prec_test_7);

    // Test 8 : liberer liste vide
    message_t *tete_test8 = NULL; 
    liberer_LCH(tete_test8);

    // Test 9 : liberer liste non vide
    message_t *tete_test9 = NULL; 
    message_t *nouv_test9_1 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !"); 
    message_t **prec_test_9_1 = rech_prec_triee_LCH(20160710, &tete_test9);
    adj_cell_LCH(prec_test_9_1, nouv_test9_1);   
    message_t *nouv_test9_2 = creer_maillon_LCH(22220505, 24540909, "Brrr"); 
    message_t **prec_test_9_2 = rech_prec_triee_LCH(22220505, &tete_test9);
    adj_cell_LCH(prec_test_9_2, nouv_test9_2);  
    liberer_LCH(tete_test9);

    return 0;
}