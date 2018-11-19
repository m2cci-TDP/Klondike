#include <stdio.h>

static void	 ESErreur (char *m)
{
	printf("Erreur d'entree/sortie - on attendait %s\n", m) ;
	exit (1) ;
}

void LireFichierEntier (FILE *f, int *e)
{
  int r = fscanf(f, "%d\n", e) ;
  if ((r == EOF) || (r == 0))
		ESErreur ("un entier") ;
}

void LireFichierReel (FILE *f, double *d)
{
  int r = fscanf(f, "%lf\n", d) ;
  if ((r == EOF) || (r == 0)) ESErreur ("un reel etendu (double)") ;
}

void LireFichierTexte (FILE *f, char l[])
{
  short i = 0 ;
  int c = fgetc(f);
  while  ( c != '\n') { l[i++] = c ; c = fgetc (f) ;}
  l[i] = 0 ;
}

char *LireFichierLigne (FILE *f, char l[])
{
  return fgets(l, 256, f) ;
}

void EcrireFichierEntier (FILE *f, int e)
{
  fprintf(f,"%d\n",e) ;
}

void EcrireFichierReel (FILE *f, double d)
{
  fprintf(f,"%lf\n",d) ;
}

void EcrireFichierTexte (FILE *f, char s[])
{
  fprintf(f,"%s\n",s) ;
}

FILE *OuvrirFichierLecture (char n[])
{
  FILE *f ;

  f = fopen(n, "r") ;

  return f ;
}

FILE *OuvrirFichierEcriture (char n[])
{
  FILE *f ;

  f = fopen(n, "w") ;

  return f ;
}

void FermerFichier (FILE *f)
{
  fclose(f) ;
}

int FichierInexistant (FILE *f)
{
  return (f == NULL) ;
}

int FinFichier (char t[])
{
  return (t == NULL) ;
}
