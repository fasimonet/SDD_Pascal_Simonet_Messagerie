#include "LCH.h"

/* ---------------------------------------------------------------------------------------------------- */
/* creer_maillon                   Crée un maillon message_t                                            */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      date_deb Un entier représentant la date de début de validité du message                         */
/*      date_fin Un entier représentant la date de fin de validité du message                           */
/*      texte Une chaine de caractère représentant le texte du message                                  */
/*                                                                                                      */      
/* En sortie: Un pointeur vers le maillon nouvellement créé                                             */
/*                                                                                                      */
/* Principe:                                                                                            */
/*      on définie un pointeur sur une structure de type message_t à laquelle on alloue la mémoire      */ 
/*      nécéssaire                                                                                      */
/*      si il n'y a pas de problème d'allocation, on alloue la mémoire nécéssaire à l'espace contenant  */
/*      le texte du message                                                                             */
/*      si il n'y a pas de problème d'allocation on rentre dans la structure les valeurs des paramètres */
/*      en entrée                                                                                       */
/*      sinon on libere l'espace mémoire                                                                */
/*                                                                                                      */
/* Lexique:                                                                                             */
/*      taille_txt : entier donnant la longueure du message (nombre de caractère)                       */
/*      message : pointeur vers une structure de type message_t contenant le message créé               */
/* ---------------------------------------------------------------------------------------------------- */
message_t* creer_maillon_LCH(int date_deb, int date_fin, char* texte)
{
    int         taille_txt = strlen(texte);
    message_t * message = (message_t *) malloc(sizeof(message_t));
    if (message == NULL)
    {
        printf("Pb allocation mémoire maillon message_t\n");
    }
    else 
    {
        message->texte = (char *) malloc(sizeof(char)*taille_txt +1);
        if (message->texte == NULL)
        {
            printf("Pb allocation mémoire tableau texte\n");
            free(message); // ???
            message = NULL;
        }
        else 
        {
            message->date_deb = date_deb;
            message->date_fin = date_fin;
            strcpy(message->texte, texte);
            message->texte[taille_txt+1] = "\0";
        }
    }

    return message;
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_maillon             Affiche les champs d'un maillon message_t                               */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      message Le maillon à afficher                                                                   */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */  
/*      affiche respectivement les dates de début, de fin et le corps du message                            */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_maillon_LCH(message_t message)
{
    printf("Date de début de validité du message : %d\n", message.date_deb);
    printf("Date de fin de validité du message : %d\n", message.date_fin);
    printf("Corps du message :\n%s\n", message.texte);   
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_LCH                 Affiche les champs d'une LCH message_t                                  */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete Le maillon de tête de la LCH à afficher                                                    */
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe:                                                                                            */
/*      si la liste est non vide on la parcours et on appelle la fonction afficher_maillon_LCH sur      */
/*      chaque maillon, sinon on affiche qu'il n'y a aucin pessage                                      */
/*                                                                                                      */
/* Lexique :                                                                                            */
/*      cour : pointeur sur les maillons de la liste initialisé sur le premier élément. Il sert à       */
/*      parcourir la liste                                                                              */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_LCH(message_t tete)
{
    message_t * cour = &tete;

    printf("====================================================================\n");
    printf("\t\tAFFICHAGE DE TOUS LES MESSAGES\n");
    printf("====================================================================\n\n");

    if (cour == NULL)
    {
        printf("Il n'y a aucun message\n");
    }
    else 
    {
        while (cour != NULL)
        {
            printf("==================================\n");
            printf("\tMessage n°%d\n", nb);
            printf("==================================\n");
            afficher_maillon_LCH(*cour);
            cour = cour->suiv;
            printf("\n");
            nb++;
        }
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* recherche_prec_triee        Recherche le précédent d'un élément dans une LCH message_t               */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      date_deb Un entier représentant la date de début de validation du message, critère pour         */
/* déterminer le précédent                                                                              */
/*      tete Un pointeur sur le pointeur de la tête de la LCH                                           */                                 
/*                                                                                                      */      
/* En sortie: Un pointeur vers le pointeur du précédent                                                 */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On utilise un premier pointeur servant à parcourire la liste et un pointeur de pointeur gardant */
/*      en mémoire l'adresse de l'élément précédent celui de l'autre pointeur                           */
/*                                                                                                      */
/* Lexique:                                                                                             */
/*      cour : pointeur sur les maillons de la liste initialisé sur le premier élément. Il sert à       */
/*      parcourir la liste                                                                              */
/*      prec : pointeur vers le pointeur précédent                                                      */
/* ---------------------------------------------------------------------------------------------------- */
message_t** rech_prec_triee_LCH(int date_deb, message_t** tete)
{
    message_t      * cour = *tete;
    message_t     ** prec = tete;
    while (cour != NULL && cour->date_deb < date_deb)
    {
        prec = &cour->suiv;
        cour = cour->suiv;
    }
    
    return prec;
}

/* ---------------------------------------------------------------------------------------------------- */
/* adj_cell                     Ajoute un maillon dans la LCH message_t                                 */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      prec Un pointeur vers un pointeur de l'élément précédant le nouvel élément à ajouter            */
/*      nouv Un pointeur sur le nouvel élément à ajouter                                                */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On effectue le chainage du nouvelle élément en modifiant las valeur des pointeurs vers les      */
/*      éléments suivants                                                                               */
/* ---------------------------------------------------------------------------------------------------- */
void adj_cell_LCH(message_t **prec, message_t *nouv)
{
    nouv->suiv = *prec;
    *prec = nouv;
}

/* ---------------------------------------------------------------------------------------------------- */
/* lire_fichier         Lit le fichier passé en paramètre et construit une LCH avec son contenu         */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      nom Nom du fichier à lire                                                                       */                          
/*                                                                                                      */      
/* En sortie: La nouvelle LCH                                                                           */
/*                                                                                                      */
/* Principe :                                                                                           */ 
/*      Si on a pas de problème d'ouverture de fichier                                                  */
/*          on lit les premières date du fichier que l'on stock dans des variables                      */
/*          tant que l'on est pas à la fin du fichier                                                   */
/*              on récupère le texte du message dans un tableau de taille 100                           */
/*              on alloue l'espace nécessaire puis on copie le contenue du tableau à cette endroit si   */
/*              il n'y a pas eu de probleme d'allocation                                                */
/*              on appelle la fonction creer_maillon_LCH avec les dates et le tableau sur mesure        */
/*              on appelle la fonction rech_prec_triee_LCH avec la date et la tête de la liste          */
/*              on appelle la fonction adj_cell_LCH avec les résulats des deux fonctions précédentes    */
/*              si il a été allouer on libère l'éspace du tableau sur mesure                            */
/*              on lit les dates suivantes                                                              */
/*          on ferme le fichier                                                                         */
/*      on retourne la tête de la liste chainée                                                         */
/*                                                                                                      */
/* Lexique                                                                                              */
/*      t : pointeur de tête vers la nouvelle liste chainée                                             */
/*      nouv : pointeur vers les vouveaux éléments à entrer dans la liste                               */
/*      prec : pointeur vers le pointeur du précédent                                                   */
/*      date_deb : entier stockant la date de debut du nouvelle élément à insérer                       */
/*      date_fin : entier stockant la date de fin du nouvelle élément à insérer                         */
/*      texte : tableau lisant au maximum 100 caractères du fichier composant le corps du message       */
/*      texte_redim : pointeur vers un tableau de charachtère de taille optimal par rapport au message  */
/*      flot :                                                                                          */
/* ---------------------------------------------------------------------------------------------------- */
message_t* lire_fichier(char *nom)
{
    message_t     * t = NULL;
    message_t     * nouv;
    message_t    ** prec;
    int             date_deb;
    int             date_fin;
    char            texte[101];
    char          * texte_redim;
    FILE          * flot;

    flot = fopen(nom, "r");
    if (flot == NULL)
    {
        printf("Pb d'ouverture du fichier %s en lecture\n", nom);
    }
    else 
    {
        fscanf(flot, "%d %d", &date_deb, &date_fin);
        while (!feof(flot))
        {
            fseek(flot, 1, SEEK_CUR);
            fgets(texte, 101, flot);
            texte_redim = (char *) malloc(strlen(texte));

            if(texte_redim)
            {
                strcpy(texte_redim, texte);
                texte_redim[strlen(texte)-1] = '\0';
            } 
            nouv = creer_maillon_LCH(date_deb, date_fin, texte_redim);
            prec = rech_prec_triee_LCH(date_deb, &t);
            adj_cell_LCH(prec, nouv);
            if(texte_redim){
                free(texte_redim);
                texte_redim = NULL;
            } 
            fscanf(flot, "%d %d", &date_deb, &date_fin);
        }
        fclose(flot);
    }
    return t;
}

/* ---------------------------------------------------------------------------------------------------- */
/* sauv_fichier           Sauvegarde une LCH message_t dans un fichier non binaire                      */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      nom Le nom du fichier à éditer                                                                  */
/*      tete Un pointeur vers le premier élément de la LCH                                              */                             
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      Si on a pas de problème d'ouverture de fichier en écriture                                      */
/*          On parcours la liste en écrivant à la suite dans le fichier les maillons séparer par des    */
/*          retours à la ligne. Les éléments du maillon sont séparés par des espaces                    */
/*                                                                                                      */
/* Lexique :                                                                                            */
/*      cour : pointeur sur les maillons de la liste initialisé sur le premier élément. Il sert à       */
/*      parcourir la liste                                                                              */
/*      flot :                                                                                          */
/* ---------------------------------------------------------------------------------------------------- */
void sauv_fichier(char *nom, message_t *tete)
{
    FILE      * flot;
    message_t * cour;

    cour = tete;
    flot = fopen(nom, "w");
    if (flot == NULL)
    {
        printf("Pb d'ouverture du fichier %s en écriture\n", nom);
    }
    else 
    {
        while (cour != NULL)
        {
            fprintf(flot, "%d %d %s\n", cour->date_deb, cour->date_fin, cour->texte);
            cour = cour->suiv;
        }
        fclose(flot);
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_messages_non_expires            Affiche les messages non expirés d'une LCH message_t        */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete Le maillon de tête de la LCH à afficher                                                    */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/*                                                                                                      */
/* Principe :                                                                                           */
/*      On récupère la date courante                                                                    */
/*      Si la liste est non vide                                                                        */
/*          Tant que la date de fin du message n'est pas dépassée                                       */
/*              On parcour la liste en appelant sur chaque maillon la fonction afficher_maillon_LCH     */
/*                                                                                                      */
/*                                                                                                      */
/* Lexique :                                                                                            */
/*      nb : entier contenant le numero du message afficher                                             */
/*      cour : pointeur sur les maillons de la liste initialisé sur le premier élément. Il sert à       */
/*      parcourir la liste                                                                              */
/*      date_courante :  entier de la forme AAAAMMJJ contenant la date courante                         */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_messages_non_expires(message_t tete)
{
    int         nb = 1;
    message_t * cour = &tete;
    int         date_courante = recuperer_date_courante();

    printf("====================================================================\n");
    printf("\t\tAFFICHAGES DES MESSAGES NON EXPIRES\n");
    printf("====================================================================\n\n");

    if (cour == NULL)
    {
        printf("Aucun message n'est valide\n");
    }
    else 
    {
        while (cour != NULL)
        {
            if (cour->date_fin >= date_courante) // AND cour!=NULL ???
            {
                printf("==================================\n");
                printf("\tMessage n°%d\n", nb);
                printf("==================================\n");
                afficher_maillon_LCH(*cour);
                printf("\n");
                nb++;
            }
            cour = cour->suiv;
        }
    }    
}

/* ---------------------------------------------------------------------------------------------------- */
/* supprimer_maillon                            Supprime un maillon d'une LCH                           */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      prec le pointeur vers le pointeur de l'élément à supprimer                                      */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void supprimer_maillon_LCH(message_t** prec)
{
    message_t * cour = *prec;

    *prec = (*prec)->suiv;
    free(cour->texte);
    free(cour);
}

/* ---------------------------------------------------------------------------------------------------- */
/* supprimer_messages_obsoletes             Supprime les messages obsolètes d'une LCH                   */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete le pointeur vers le pointeur de la tête                                                    */                                 
/*                                                                                                      */      
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void supprimer_messages_obsoletes_LCH(message_t** tete)
{
    message_t     * cour = *tete;
    message_t    ** prec = tete;
    int date_auj = recuperer_date_courante();

    while (cour != NULL)
    {
        if (cour->date_fin < date_auj)
        {
            supprimer_maillon_LCH(prec);
        }

        prec = &cour->suiv;
        cour = cour->suiv;
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* liberer_LCH                                  Libère une LCH                                          */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete le pointeur de tête                                                                        */
/*                                                                                                      */
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void liberer_LCH(message_t* tete)
{
    message_t * cour = tete;
    while (tete != NULL)
    {
        tete = tete->suiv;
        free(cour->texte);
        free(cour);
        cour = tete;
    }
}

/* ---------------------------------------------------------------------------------------------------- */
/* afficher_si_motif_LCH                    Affiche les messages contenant un motif                     */
/*                                                                                                      */
/* En entrée:                                                                                           */
/*      tete le pointeur de tête                                                                        */
/*      motif le motif à respecter                                                                      */
/*                                                                                                      */
/* En sortie: Aucune sortie                                                                             */
/* ---------------------------------------------------------------------------------------------------- */
void afficher_si_motif_LCH(message_t* tete, char* motif)
{
    message_t * cour = tete;
    int         nb = 0;

    printf("====================================================================\n");
    printf("\t\tAFFICHAGES DES MESSAGES CONTENANT UN MOTIF\n");
    printf("====================================================================\n\n");
    printf("Le motif vérifié est : \"%s\"\n\n", motif);
    while (cour != NULL)
    {
        // Réécrire strstr
        if (strstr(cour->texte, motif))
        {
            nb++;
            printf("==================================\n");
            printf("\tMessage n°%d\n", nb);
            printf("==================================\n");
            afficher_maillon_LCH(*cour);
            printf("\n");
        } 
        cour = cour->suiv;
    }
    if (nb == 0)
    {
        printf("Aucun message ne contient le motif : \"%s\"\n\n", motif);
    }
}