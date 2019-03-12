#===================================================
# Nom du fichier : Makefile
# Date de creation : 27/02/2018
# Auteurs : Julien PASCAL et Fabien SIMONET (G21)
# Objectif : 
#	- automatiser la compilation
#	- faire de la compilation separee
#===================================================

#===================================================
# EXECUTABLES A COMPILER
#===================================================
all: main manipulation_LCH manipulation_message manipulation_fichier manipulation_date

#===================================================
# COMPILATEUR
#===================================================
CC = gcc

#===================================================
# OPTIONS DE COMPILATION
#===================================================
CFLAGS = -Wall -Wextra -g -O0

#===================================================
# FICHIERS OBJETS
#===================================================

# fichiers .o communs a tous les executables
COMMON_OBJ = LCH.o date.o message.o

# fichier .o relatif a l'executable "manipulation_LCH"
MANIP_LCH_OBJ = manipulation_LCH.o

# fichier .o relatif a l'executable "main"
MAIN_OBJ = main.o

# fichier .o relatif a l'executable "manipulation_message"
MANIP_MESSAGE_OBJ = manipulation_message.o

# fichier .o relatif a l'executable "manipulation_fichier"
MANIP_FICHIER_OBJ = manipulation_fichier.o

# fichier .o relatif a l'executable "manipulation_date"
MANIP_DATE_OBJ = manipulation_date.o

#===================================================
# REGLES DE PRODUCTION FINALES
#===================================================

# production executable "main"
main: 	$(COMMON_OBJ) $(MAIN_OBJ)
		$(CC) $(COMMON_OBJ) $(MAIN_OBJ) -o main

# production executable "manipulation_LCH"
manipulation_LCH: 	$(COMMON_OBJ) $(MANIP_LCH_OBJ)
					$(CC) $(COMMON_OBJ) $(MANIP_LCH_OBJ) -o manipulation_LCH

# production executable "manipulation_message"
manipulation_message: 	$(COMMON_OBJ) $(MANIP_MESSAGE_OBJ)
						$(CC) $(COMMON_OBJ) $(MANIP_MESSAGE_OBJ) -o manipulation_message

# production executable "manipulation_fichier"
manipulation_fichier: 	$(COMMON_OBJ) $(MANIP_FICHIER_OBJ)
						$(CC) $(COMMON_OBJ) $(MANIP_FICHIER_OBJ) -o manipulation_fichier

# production executable "manipulation_date"
manipulation_date: 	$(COMMON_OBJ) $(MANIP_DATE_OBJ)
					$(CC) $(COMMON_OBJ) $(MANIP_DATE_OBJ) -o manipulation_date

#===================================================
# REGLE DE PRODUCTION DES .o
#===================================================

# production fichier objet "LCH.o"
LCH.o: 	LCH.c
			$(CC) -c LCH.c $(CFLAGS)

# production fichier objet "main.o"
main.o: 	main.c
			$(CC) -c main.c $(CFLAGS)

# production fichier objet "date.o"
date.o :	date.c
			$(CC) -c date.c $(CFLAGS)

# production fichier objet "manipulation_LCH.o"
manipulation_LCH.o:		manipulation_LCH.c
						$(CC) -c manipulation_LCH.c $(CFLAGS)

# production fichier objet "manipulation_message.o"
manipulation_message.o:		manipulation_message.c
							$(CC) -c manipulation_message.c $(CFLAGS)

# production fichier objet "manipulation_fichier.o"
manipulation_fichier.o:		manipulation_fichier.c
							$(CC) -c manipulation_fichier.c $(CFLAGS)

# production fichier objet "manipulation_date.o"
manipulation_date.o:		manipulation_date.c
							$(CC) -c manipulation_date.c $(CFLAGS)

#===================================================
# NETTOYAGE DES .o
#===================================================
clean:
			@rm -f *.o

#===================================================
# NETTOYAGE DES EXECUTABLES
#===================================================
mrproper:
			rm -f main
			rm -f manipulation_LCH
			rm -f manipulation_message
			rm -f manipulation_fichier
			rm -f manipulation_date
