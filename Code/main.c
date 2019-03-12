#include "LCH.h"
#include "date.h"
#include "message.h"

//Penser a ajouter les gardiens partout
int main(int argc, char** argv)
{
    message_t*  tete=NULL; 
    int date_cour;

    if(argc == 2)
    {
        tete = lire_fichier(argv[1]);
        afficher_LCH(tete);
    }
    
    date_cour = recuperer_date_courante();
    afficher_messages_non_expires(tete);    
    supprimer_messages_obsoletes(&tete);
    afficher_LCH(tete);
    mettre_a_jour_messages(20000101, date_cour, &tete);
    afficher_LCH(tete);
    afficher_messages_si_motif(tete, "Ca va ?");

    liberer_LCH(tete);
    return 0;
}
