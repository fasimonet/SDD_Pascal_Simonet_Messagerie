#include "LCH.h"

int main()
{
    // test afficher message non expirer
    message_t     * t = lire_fichier(fic2.txt);
    afficher_messages_non_expires_LCH(*t);

    // test afficher si motif
    afficher_si_motif_LCH(t, "Ca va ?"); // le motif n'est pas dans la liste
    afficher_si_motif_LCH(tete, "Joyeux");// le motif est dans la liste

    // test supprimer message obsolete
    supprimer_messages_obsoletes_LCH(&t);
    afficher_LCH(*t);

    return 0;
}