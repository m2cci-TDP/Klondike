# https://openclassrooms.com/fr/courses/1130196-compilez-sous-gnu-linux

# définition des cibles particulières
.PHONY: clean, mrproper

# désactivation des règles implicites
.SUFFIXES:

# définition des variables
bindir = binaries
srcdir = sources
includedir = headers
CC = gcc
EXEC = klondike
DEBUG = yes
OBJ = $(bindir)/main.o $(bindir)/editeur.o $(bindir)/fichier.o $(bindir)/jeu.o

LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL
CFLAGS = -I$(includedir) -I/usr/include/SDL
ifeq ($(DEBUG),yes)
	CFLAGS += -g -W -Wall
else
	CFLAGS = CFLAGS
endif


# all conditionnel
all : $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode Debug"
else
	@echo "Génération en mode Release"
endif

$(EXEC): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $(EXEC)

$(bindir)/%o: $(srcdir)/%c
	$(CC) -c $< -o $@ $(CFLAGS)

# clean
clean:
	rm -rf $(bindir)/*.o

# mrproper
mrproper: clean
	rm -rf $(EXEC)
