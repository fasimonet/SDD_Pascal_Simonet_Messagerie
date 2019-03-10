/* ---------------------------------------------------------------------------------------------------- */
/* Nom du fichier : LCH.h                                                                               */
/* Date de creation : 27/02/2018                                                                        */
/* Auteurs : Julien PASCAL et Fabien SIMONET (G21)                                                      */
/* Objectif : repertorier les prototypes des fonctions de manipulation de listes chainees               */
/* ---------------------------------------------------------------------------------------------------- */

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

// Gestion de LCH en elle-meme
message_t* creer_maillon_LCH(int, int, char*);
void supprimer_maillon_LCH(message_t**);
void afficher_maillon_LCH(message_t*);
void afficher_LCH(message_t*);
message_t** rech_prec_triee_LCH(int, message_t**);
void adj_cell_LCH(message_t**, message_t*);
void liberer_LCH(message_t*);

#endif