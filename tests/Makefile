# sudo apt-get install check

# définition des cibles particulières
.PHONY: clean compilation

# désactivation des règles implicites
.SUFFIXES:
.SUFFIXES: .c .o

# constantes
CFLAGS = -g -no-pie -I../include -I../include/C4 -I../lib/include -I../img
LDFLAGS = -L../lib/bin -lmachine_trace -L/usr/X11R6/lib -lX11 -lm -lcheck -lsubunit -pthread \
 -pthread -lrt -lsubunit -lm

all: compilation check.e

#%.o: %.c
#	gcc -Wall $(CFLAGS) -c $<

check.e: check_C4.c ../bin/*.o ../lib/bin/libmachine_trace.a
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

compilation:
	make -i -C ..

clean:
	rm -f *.o check.e
