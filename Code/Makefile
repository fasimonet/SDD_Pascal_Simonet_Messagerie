#===============================
# EXECUTABLES A COMPILER
#===============================
all: outil manipulation_LCH

#===============================
# COMPILATEUR
#===============================
CC = gcc

#===============================
# OPTIONS DE COMPILATION
#===============================
CFLAGS = -Wall -Wextra -g -O2

#===============================
# FICHIERS OBJETS
#===============================

# fichiers .o communs a tous les executables
COMMON_OBJ = LCH.o date.o message.o

# fichier .o relatif a l'executable "manipulation_LCH"
MANIP_OBJ = manipulation_LCH.o

# fichier .o relatif a l'executable "outil"
TOOL_OBJ = outil.o

#===============================
# REGLES DE PRODUCTION FINALES
#===============================

# production executable "outil"
outil: 	$(COMMON_OBJ) $(TOOL_OBJ)
		$(CC) $(COMMON_OBJ) $(TOOL_OBJ) -o outil

# production executable "manipulation_LCH"
manipulation_LCH: 	$(COMMON_OBJ) $(MANIP_OBJ)
					$(CC) $(COMMON_OBJ) $(MANIP_OBJ) -o manipulation_LCH

#===============================
# REGLE DE PRODUCTION DES .o
#===============================

# production fichier objet "LCH.o"
LCH.o: 	LCH.c
			$(CC) -c LCH.c $(CFLAGS)

# production fichier objet "outil.o"
outil.o: 	outil.c
			$(CC) -c outil.c $(CFLAGS)

# production fichier objet "date.o"
date.o :	date.c
			$(CC) -c date.c $(CFLAGS)

# production fichier objet "manipulation_LCH.o"
manipulation_LCH.o:		manipulation_LCH.c
						$(CC) -c manipulation_LCH.c $(CFLAGS)

#===============================
# NETTOYAGE DES .o
#===============================
clean:
			@rm -f *.o

#===============================
# NETTOYAGE DES EXECUTABLES
#===============================
mrproper:
			rm -f outil
			rm -f manipulation_LCH
