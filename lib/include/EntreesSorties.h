#ifndef _ENTREES_SORTIES_H
#define _ENTREES_SORTIES_H

#include <stdio.h>

extern	void	LireEntier (int		*) ;
extern	void	LireReel   (double	*) ;
extern	void	LireCar	   (char	*) ;
extern	void	LireMot (char *, int) ;
extern	void	LireLigne (char *) ;
extern  char    *LireFichierLigne (FILE *f, char l[]) ;
extern  void    LireFichierEntier (FILE *f, int *) ;
extern  void    LireFichierReel (FILE *f, double *) ;
extern  void    LireFichierTexte (FILE *f, char l[]) ;
extern	void	EcrireEntier (int)	   ;
extern	void	EcrireReel  (double)   ;
extern	void	EcrireMot  (char *)  ;
extern	void	EcrireLigne  (char *)  ;
extern	void	EcrireTexte  (char *)  ;
extern	void	EcrireCar    (char)    ;
extern	void	ALaLigne () ;
extern	void	Tabuler () ;
extern  void    TracerEntier (int) ;
extern  void    TracerReel (double) ;
extern  void    TracerCar (char) ;
extern  void    TracerTexte (char *) ;
extern  void    EcrireFichierEntier (FILE *f, int e) ;
extern  void    EcrireFichierReel (FILE *f, double d) ;
extern  void    EcrireFichierTexte (FILE *f, char s[]) ;
extern  FILE    *OuvrirFichierLecture (char n[]) ;
extern  FILE    *OuvrirFichierEcriture (char n[]) ;
extern  void    FermerFichier (FILE *f) ;
extern  int     FichierInexistant (FILE *f) ;
extern  int     FinFichier (char t[]) ;

#endif
