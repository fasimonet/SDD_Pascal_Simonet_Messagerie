#ifndef MESSAGE_H
#define MESSAGE_H

#include "LCH.h"

void afficher_messages_non_expires(message_t*);
void supprimer_messages_obsoletes_LCH(message_t**);
void afficher_si_motif_LCH(message_t*, char*);

message_t* lire_fichier(char*);
void sauv_fichier(char*, message_t*);

#endif 