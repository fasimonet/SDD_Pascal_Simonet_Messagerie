#include "LCH.h"

int main() 
{
    // Cas 1 => creer maillon, afficher maillon
    message_t *nouv_cas1 = creer_maillon_LCH(20160710, 20160720, "Félicitation ! Tu as ton BAC !");
    afficher_maillon_LCH(*nouv_cas1);
    
    // Cas 2 => creer maillon, rech_prec, ajouter dans liste, afficher liste (liste vide initialement)
    message_t *tete_cas2 = NULL;
    message_t *nouv_cas2 = creer_maillon_LCH(22220505, 24540909, "Brrr");
    message_t **prec_cas2 = rech_prec_triee_LCH(22220505, &tete_cas2);
    adj_cell_LCH(prec_cas2, nouv_cas2);
    if (tete_cas2 != NULL) afficher_LCH(*tete_cas2);

    // Cas 3 => creer maillon, rech_prec, ajouter dans liste, afficher liste (liste non vide initialement, ajout en tete)
    message_t *tete_cas3 = NULL;
    message_t *nouv1_cas3 = creer_maillon_LCH(22220505, 24540909, "Brrr");
    message_t *nouv2_cas3 = creer_maillon_LCH(11111111, 34561010, "FIRST!!!");   
    message_t **prec_cas3 = rech_prec_triee_LCH(22220505, &tete_cas3);

    adj_cell_LCH(prec_cas3, nouv1_cas3);
    prec_cas3 = rech_prec_triee_LCH(11111111, &tete_cas3);
    adj_cell_LCH(prec_cas3, nouv2_cas3);
    if (tete_cas3 != NULL) afficher_LCH(*tete_cas3);    

    // Cas 4 => creer maillon, rech_prec, ajouter dans liste, afficher liste (liste non vide initialement, ajout non tete)
    message_t *tete_cas4 = NULL;
    message_t *nouv1_cas4 = creer_maillon_LCH(22220505, 24540909, "Brrr");
    message_t *nouv2_cas4 = creer_maillon_LCH(33330808, 34561010, "plus FIRST!!!");   
    message_t **prec_cas4 = rech_prec_triee_LCH(22220505, &tete_cas4);

    adj_cell_LCH(prec_cas4, nouv1_cas4);
    prec_cas4 = rech_prec_triee_LCH(33330808, &tete_cas4);
    adj_cell_LCH(prec_cas4, nouv2_cas4);
    if (tete_cas4 != NULL) afficher_LCH(*tete_cas4);  
    
    return 0;
}