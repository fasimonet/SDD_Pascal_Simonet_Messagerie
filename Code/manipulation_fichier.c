#include "LCH.h"

int main()
{
    // teste lecture de fichier avec élément de plus de 100 caractere
    message_t     * t = lire_fichier(fichier_test_lecture);
    afficher_LCH(*t);
    //teste de stockage dans un fichier
    char          * nom;
    fscanf(stdin,"%s", &nom);
    sauv_fichier(nom,t);
    return 0;
}