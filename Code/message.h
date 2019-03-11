/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : message.h                                                                           */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : repertorier les prototypes des fonctions de manipulation de messages                      */
/* ---------------------------------------------------------------------------------------------------- */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "LCH.h"

void afficher_messages_non_expires(message_t*);
void supprimer_messages_obsoletes(message_t**);
void mettre_a_jour_messages(int old_date_deb, int new_date_deb, message_t** tete);
void afficher_messages_si_motif(message_t*, char*);

message_t* lire_fichier(char*);
void sauv_fichier(char*, message_t*);

#endif 