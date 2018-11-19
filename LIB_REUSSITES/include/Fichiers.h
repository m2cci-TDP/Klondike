#include <stdio.h>

extern  char    *LireFichierLigne (FILE *f, char l[]) ;
extern  void    LireFichierEntier (FILE *f, int *) ;
extern  void    LireFichierReel (FILE *f, double *) ;
extern  void    LireFichierTexte (FILE *f, char l[]) ;
extern  void    EcrireFichierEntier (FILE *f, int e) ;
extern  void    EcrireFichierReel (FILE *f, double d) ;
extern  void    EcrireFichierTexte (FILE *f, char s[]) ;
extern  FILE    *OuvrirFichierLecture (char n[]) ;
extern  FILE    *OuvrirFichierEcriture (char n[]) ;
extern  void    FermerFichier (FILE *f) ;
extern  int     FichierInexistant (FILE *f) ;
extern  int     FinFichier (char t[]) ;
