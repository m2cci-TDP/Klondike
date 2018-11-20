# définition des cibles particulières
.PHONY: clean, mrproper, install, lib

# désactivation des règles implicites
.SUFFIXES:
.SUFFIXES: .c .o

# définition des variables
#DIR = /home/theo/Documents/M2CCI/Klondike/LIB_REUSSITES/
libDIR = lib
libINCL = $(libDIR)/include
libBIN = $(libDIR)/bin
#libSRC = $(libDIR)/src

dirSRC = src
dirSrcR7 = $(dirSRC)/R7
dirSrcC4 = $(dirSRC)/C4
dirSrcQLL = $(dirSRC)/QLL
dirINCL = include
dirInclR7 = $(dirINCL)/R7
dirBIN = bin

CC = gcc
CFLAGS = -g -no-pie -I$(libINCL) -I$(dirINCL) -I$(dirInclR7) -Iimg
LDFLAGS = -L$(libBIN) -lmachine_trace -L/usr/X11R6/lib -lX11 -lm
SRC = $(dirSRC)/AfficherTas.c $(dirSRC)/Alea.c
srcR7 = $(dirSrcR7)/R7.c $(dirSrcR7)/InteractionR7.c
OBJ = $(dirBIN)/Tas.o $(patsubst %.c, %.o, $(SRC))
objR7 = $(patsubst %.c, %.o, $(srcR7))

all: lib ReussiteR7.e install

$(dirBIN)/%.o: %.c
	$(CC) $(CFLAGS) -Wall -ansi -c $<

ReussiteR7.e: $(libBIN)/libmachine_trace.a $(OBJ) $(objR7) $(dirSrcR7)/ReussiteR7.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReussiteC4.e: $(libBIN)/libmachine_trace.a $(OBJ) C4.o InteractionC4.o $(dirSrcC4)/ReussiteC4.c
	$(CC) $(CFLAGS) -o ReussiteC4.e $(dirSrcC4)/ReussiteC4.c ${libBIN}/graphlib_w.o InteractionC4.o C4.o $(OBJ) $(LDFLAGS)

ReussiteQLL.e: $(libBIN)/libmachine_tra	ce.a $(OBJ) QLL.o InteractionQLL.o $(dirSrcQLL)/ReussiteQLL.c
	$(CC) $(CFLAGS) -o ReussiteQLL.e $(dirSrcQLL)/ReussiteQLL.c ${libBIN}/graphlib_w.o InteractionQLL.o QLL.o $(OBJ) $(LDFLAGS)

Reussites.e: $(libBIN)/libmachine_trace.a $(OBJ) R7.o C4.o QLL.o InteractionToutes.o $(dirSRC)/Reussites.c
	$(CC) $(CFLAGS) -o Reussites.e $(dirSRC)/Reussites.c ${libBIN}/graphlib_w.o InteractionToutes.o QLL.o C4.o R7.o $(OBJ) $(LDFLAGS)

lib:
	make -C $(libDIR)

install:
	mkdir -p $(dirBIN)
	mv $(OBJ) $(objR7) ${dirBIN}/

clean:
	make -C $(libDIR) clean
	rm -f $(dirBIN)/AfficherTas.o $(dirBIN)/Alea.o $(dirBIN)/InteractionR7.o $(dirBIN)/R7.o

mrproper:
	rm -rf *.e
