#include <stdlib.h>

#define Allouer(p,T) *p=(T *)malloc(sizeof(T))

void Liberer(void *);
