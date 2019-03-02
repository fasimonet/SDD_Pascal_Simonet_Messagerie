# compilateur
CC = gcc

# options
CFLAGS = -Wall -Wextra -g -O2

#LDFLAGS = -lm -L

#liste des fichiers objets
OBJ = LCH.o outil.o date.o manipulation_LCH.o

all: outil manipulation_LCH

#règle de production finale
outil: 	$(OBJ)
		$(CC) $(OBJ) -o outil

manipulation_LCH: 	$(OBJ)
					$(CC) $(OBJ) -o manipulation_LCH

#règle de production pour chaque fichier
LCH.o: 	LCH.c
			$(CC) -c LCH.c $(CFLAGS)

outil.o: 	outil.c
			$(CC) -c outil.c $(CFLAGS)

date.o :	date.c
			$(CC) -c date.c $(CFLAGS)

manipulation_LCH.o:		manipulation_LCH.c
						$(CC) -c manipulation_LCH.c $(CFLAGS)

clean: 
			rm -f $(OBJ)

mrproper:
			rm -f outil
			rm -f manipulation_LCH
