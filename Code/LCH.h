#ifndef LCH_H
#define LCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct message
{
    int date_deb;
    int date_fin;
    char* texte;
    struct message* suiv;
} message_t;

// Gestion de LCH en elle-même
message_t* creer_maillon_LCH(int, int, char*);
void supprimer_maillon_LCH(message_t**);
void afficher_maillon_LCH(message_t);
void afficher_LCH(message_t);
void afficher_messages_non_expires_LCH(message_t);// deplacer
void supprimer_messages_obsoletes_LCH(message_t**);// deplacer
message_t** rech_prec_triee_LCH(int, message_t**);
void adj_cell_LCH(message_t**, message_t*);
void liberer_LCH(message_t*);
void afficher_si_motif_LCH(message_t*, char*);// deplacer


// Gestion de LCH par rapport à un fichier
message_t* lire_fichier(char*);// deplacer
void sauv_fichier(char*, message_t*);// deplacer

#endif