# définition des cibles particulières
.PHONY: clean, mrproper

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
dirSrcMD = $(dirSRC)/MD
#dirSrcQLL = $(dirSRC)/QLL
dirINCL = include
dirInclR7 = $(dirINCL)/R7
dirInclC4 = $(dirINCL)/C4
dirInclMD = $(dirINCL)/MD
dirBIN = bin

CC = gcc
EXEC = Reussites.e
EXECR7 = ReussiteR7.e
EXECC4 = ReussiteC4.e
CFLAGS = -g -no-pie -I$(libINCL) -I$(dirINCL) -I$(dirInclR7) -I$(dirInclC4) -Iimg
LDFLAGS = -L$(libBIN) -lmachine_trace -L/usr/X11R6/lib -lX11 -lm
SRC = $(dirSRC)/AfficherTas.c $(dirSRC)/Alea.c $(dirSRC)/Interaction.c $(dirSRC)/stats.c $(dirSRC)/Tas.c
srcR7 = $(dirSrcR7)/R7.c
srcC4 = $(dirSrcC4)/C4.c
OBJ = $(patsubst %.c, %.o, $(SRC))
objR7 = $(patsubst %.c, %.o, $(srcR7))
objC4 = $(patsubst %.c, %.o, $(srcC4))
objMD = $(patsubst %.c, %.o, $(srcMD))

all: librairies $(EXECR7) $(EXECC4) $(EXEC) install

$(dirBIN)/%.o: %.c
	$(CC) $(CFLAGS) -Wall -ansi -c $<

$(EXECR7): $(libBIN)/libmachine_trace.a $(OBJ) $(objR7) $(dirSrcR7)/ReussiteR7.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECC4): $(libBIN)/libmachine_trace.a $(OBJ) $(objC4) $(dirSrcC4)/ReussiteC4.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReussiteMD.e: $(libBIN)/libmachine_trace.a $(OBJ) $(objMD) $(dirSrcMD)/ReussiteMD.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

#ReussiteQLL.e: $(libBIN)/libmachine_tra	ce.a $(OBJ) QLL.o InteractionQLL.o $(dirSrcQLL)/ReussiteQLL.c
#	$(CC) $(CFLAGS) -o ReussiteQLL.e $(dirSrcQLL)/ReussiteQLL.c ${libBIN}/graphlib_w.o InteractionQLL.o QLL.o $(OBJ) $(LDFLAGS)
#
$(EXEC): $(libBIN)/libmachine_trace.a $(OBJ) $(objR7) $(objC4) $(dirSRC)/mainReussite.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

librairies:
	make -C $(libDIR)/

install:
	mkdir -p $(dirBIN)
	mv $(OBJ) $(objR7) $(objC4) $(objMD) ${dirBIN}/

check:
	make -C tests #check.e
	#tests/check.e

clean:
	make -C tests clean
	make -C $(dirSRC) clean
	make -C $(libDIR) clean
	rm -f $(dirBIN)/*.o

mrproper:
	rm -rf *.e
