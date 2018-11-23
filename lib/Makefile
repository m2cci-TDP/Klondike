# définition des cibles particulières
.PHONY: clean

# désactivation des règles implicites
.SUFFIXES:
.SUFFIXES: .c .o

#DIR=/u/c/carrierf/LIB_REUSSITES/
#DIR=/home/theo/Documents/M2CCI/Klondike/LIB_REUSSITES/
#DIR=.
LIB = bin
INCL = include
SRC = src

CC = gcc
CFLAGS = -I$(INCL) -c -g
EXEC = libmachine_trace.a
OBJ = machine_trace.o graphlib_w.o memoire.o Fichiers.o

all: $(EXEC) install

.%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $<
#	chgrp dsu-ens *.o
#	chmod g+w *.o

%.o: $(SRC)/%.c $(INCL)/%.h
	$(CC) $(CFLAGS) $<
#	chgrp dsu-ens *.o
#	chmod g+w *.o

$(EXEC): $(OBJ)
	ar rc $(EXEC) $(OBJ)
#	chgrp dsu-ens libmachine_trace.a
#	chmod g+w libmachine_trace.a

clean:
	rm -f $(LIB)/$(EXEC) $(LIB)/*.o
	rm -f $(EXEC) $(OBJ)

install:
	mkdir -p $(LIB)
	mv $(OBJ) $(EXEC) $(LIB)/
