# sudo apt-get install check valgrind

# définition des cibles particulières
.PHONY: clean, compilation

# désactivation des règles implicites
.SUFFIXES:
.SUFFIXES: .c .o

# constantes
CFLAGS = -g -no-pie -I../include -I../include/C4 -I../lib/include -I../img
LDFLAGS = -L../lib/bin -lmachine_trace -L/usr/X11R6/lib -lX11 -lm -lcheck -lsubunit -pthread \
 -pthread -lrt -lsubunit -lm

OBJ = check_Tas.o check_C4.o
EXEC = check.e

all: compilation $(EXEC)
	valgrind --leak-check=full -q --undef-value-errors=no ./$(EXEC)

%.o: %.c
	gcc -Wall $(CFLAGS) -c $<

$(EXEC): check_main.c $(OBJ) ../bin/*.o ../lib/bin/libmachine_trace.a
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

compilation:
	make -C ..

clean:
	rm -f *.o check.e
