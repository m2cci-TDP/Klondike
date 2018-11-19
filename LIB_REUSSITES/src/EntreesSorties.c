#include <stdio.h>
#include <ctype.h>

static void	 ESErreur (char *m)
{
	printf("Erreur d'entree/sortie - on attendait %s\n", m) ;
	exit (1) ;
}

void	LireEntier (int		*e) 
{	int	r = scanf (" %d", e) ; 
	if ((r == EOF) || (r == 0))
		ESErreur ("un entier") ;
}

void	LireReel   (double	*d) 
{ int r =  scanf (" %lf", d) ; 
  if ((r == EOF) || (r == 0)) ESErreur ("un reel etendu (double)") ;
}

void	LireCar (char	*c)
{	int l ;
	while (isspace ( l=getchar ())) ;  *c = l ; 
}

void LireMot(char p[], int n)
{
  char L_strFormat[255] ;
  int l ;
  
  /* Build Format string : "%%" -> "%" */
  sprintf(L_strFormat," %%%ds", n) ;
  scanf (L_strFormat, p) ; 
  while (( l=getchar ()) != '\n') ;
}

void    LireLigne  (char    t[])
{ short i = 0 ;
  int c ;
  while (isspace ( c=getchar ())) ; 
  while  ( c != '\n') { t[i++] = c ; c = getchar () ;}
  t[i] = 0 ;
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

void	EcrireEntier (int e)
{ printf("%d", e) ; }


void	EcrireReel  (double d)
{ printf("%lf", d) ; }

void	EcrireMot  (char *t)
{	printf(t) ; }

void	EcrireLigne  (char *t)
{	printf("%s\n",t) ; }

void	EcrireTexte  (char *t)
{	printf(t) ; }

void	EcrireCar (char c)
{ putchar (c) ; }

void	ALaLigne () 
{ putchar ('\n') ; }

void	Tabuler () 
{ putchar ('\t') ; }

void TracerEntier (int e)
{ EcrireEntier(e); ALaLigne(); }

void TracerReel (double d)
{ EcrireReel(d); ALaLigne(); }

void TracerCar (char c)
{ EcrireCar(c); ALaLigne(); }

void TracerTexte (char *t)
{ EcrireTexte(t); ALaLigne(); }


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
