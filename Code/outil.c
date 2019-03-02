#include "LCH.h"
#include "date.h"

//Penser a ajouter les gardiens partout
int main(int argc, char** argv)
{
    message_t*  tete=NULL;
    /*message_t* message4 = creer_maillon(20151102, 20191102, "Ceci est un message!");
    message_t*  message2 = creer_maillon(20190207, 20170207, "Eh oh eh oh!");
    message_t** prec = rech_prec_triee(message2->date_deb, &tete);
    message_t*  message3 = creer_maillon(20160207, 20170207, "Fabien est un dieu!");

    adj_cell(prec, message2);
    prec = rech_prec_triee(message3->date_deb, &tete);
    adj_cell(prec, message3);
    prec = rech_prec_triee(message4->date_deb, &tete);
    adj_cell(prec, message4);
    afficher_LCH(*tete);*/
    
    if(argc == 2)
    {
        //tete = lire_fichier("fic.txt");
        tete = lire_fichier(argv[1]);
        if(tete != NULL)
        {
            afficher_LCH(*tete);
        }
    }
    sauv_fichier("fic4.txt", tete);
    //afficher_LCH(*tete);

    recuperer_date_courante();
    
    if(tete != NULL)
    {
       // afficher_messages_non_expires(*tete);
    }
    supprimer_messages_obsoletes_LCH(&tete);

    //supprimer_maillon(&(tete->suiv));
    if(tete != NULL) afficher_LCH(*tete);

    if(tete != NULL) afficher_si_motif_LCH(tete, "Ca va ?");

    if(tete != NULL) afficher_si_motif_LCH(tete, "HHH");

    liberer_LCH(tete);
    return 0;
}
