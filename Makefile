# définition des cibles particulières
.PHONY: clean, mrproper

# désactivation des règles implicites
.SUFFIXES:
.SUFFIXES: .c .o

# définition des variables
#DIR = /home/theo/Documents/M2CCI/Klondike/LIB_REUSSITES/
DIR = LIB_REUSSITES
INCL = ${DIR}/include
LIB = ${DIR}/lib
SRC = ${DIR}/src

CC = gcc
CFLAGS = -g -no-pie -I${INCL}
LDFLAGS = -L${LIB} -lmachine_trace -L/usr/X11R6/lib -lX11 -lm
OBJ = Tas.o AfficherTas.o Alea.o

all: lib ReussiteR7.e

.c.o :
	gcc $(CFLAGS) -Wall -ansi -c $<

ReussiteR7.e: ${LIB}/libmachine_trace.a $(OBJ) R7.o InteractionR7.o ReussiteR7.c
	gcc $(CFLAGS) -o ReussiteR7.e ReussiteR7.c ${LIB}/graphlib_w.o InteractionR7.o R7.o $(OBJ) $(LDFLAGS)

ReussiteC4.e: ${LIB}/libmachine_trace.a $(OBJ) C4.o InteractionC4.o ReussiteC4.c
	gcc $(CFLAGS) -o ReussiteC4.e ReussiteC4.c ${LIB}/graphlib_w.o InteractionC4.o C4.o $(OBJ) $(LDFLAGS)

ReussiteQLL.e: ${LIB}/libmachine_trace.a $(OBJ) QLL.o InteractionQLL.o ReussiteQLL.c
	gcc $(CFLAGS) -o ReussiteQLL.e ReussiteQLL.c ${LIB}/graphlib_w.o InteractionQLL.o QLL.o $(OBJ) $(LDFLAGS)

Reussites.e: ${LIB}/libmachine_trace.a $(OBJ) R7.o C4.o QLL.o InteractionToutes.o Reussites.c
	gcc $(CFLAGS) -o Reussites.e Reussites.c ${LIB}/graphlib_w.o InteractionToutes.o QLL.o C4.o R7.o $(OBJ) $(LDFLAGS)

lib:
	make -C ${SRC}
	make install -C ${SRC}

clean:
	make -C ${SRC} clean
	rm -f AfficherTas.o Alea.o InteractionR7.o R7.o

mrproper:
	rm -rf *.e
