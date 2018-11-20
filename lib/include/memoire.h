#ifndef _MEMOIRE_H
#define _MEMOIRE_H

#include <stdlib.h>

#define Allouer(p,T) *p=(T *)malloc(sizeof(T))

void Liberer(void *);

#endif
