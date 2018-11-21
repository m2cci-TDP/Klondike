# définition des cibles particulières
.PHONY: clean

# désactivation des règles implicites
.SUFFIXES:

all: stats

%.o: %.c
	gcc -Wall -I../include -c $<

stats: stats.o mainStats.o
	gcc -I../include -o $@ $^

clean:
	rm -f *.o stats
