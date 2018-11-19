#DIR=/u/c/carrierf/LIB_REUSSITES/
#DIR=/home/theo/Documents/M2CCI/Klondike/LIB_REUSSITES/
DIR=..
LIB=${DIR}/lib
INCL=${DIR}/include

.%.o: %.c
	gcc -I${INCL} -c -g $<
#	chgrp dsu-ens *.o
#	chmod g+w *.o

%.o: %.c ${INCL}/%.h
	gcc -I${INCL} -c -g $<
#	chgrp dsu-ens *.o
#	chmod g+w *.o

libmachine_trace.a: machine_trace.o graphlib_w.o memoire.o Fichiers.o
	ar rc libmachine_trace.a machine_trace.o graphlib_w.o memoire.o Fichiers.o
#	chgrp dsu-ens libmachine_trace.a
#	chmod g+w libmachine_trace.a

clean:
	rm -f $(LIB)/*.a $(LIB)/*.o $(LIN)/*~
	rm -f *.a *.o *~

install:
	mkdir -p $(LIB)
	mv *.o *.a ${LIB}/
