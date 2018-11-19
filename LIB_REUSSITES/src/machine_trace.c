/* ============================================================================

IMPLEMENTATION de la MACHINE TRACE

machine_trace.c

Modif. P.Habraken 23/05/2005 :
- utilisation de graphlib_w
- utilisation constante Posix M_PI (a la place de PI)
============================================================================ */

/* =========================================================================
Machine de trace  de dessins
=========================================================================
SPECIFICATIONS  :
L'etat de la machine est caracterise par l'etat de deux composants :
l'ecran et la plume de trace.
L'etat de la plume est defini par:
- position courante de la plume dans le plan (notee pp)
definie par des coordonnees cartesiennes ds le repere utilisateur:
origine au centre, x vers la droite, y vers le haut
- direction courante (notee cap)
definie par un angle en degres par rapport a l'axe Ox,
dans le sens trigo
- position d'ecriture (notee pe) : basse ou haute


Les primitives de la machine :

Vider    efface l'ecran et place la plume au centre,
position haute, cap Ouest-Est
Effacer  efface l'ecran sans modifier l'etat de la plume.
Placer   fixe la position de la plume, en coordonnees absolues
Orienter fixe la direction de la plume, par rapport a l'axe des x
Avancer  Avance dans la direction courante
Reculer  Recule dans la direction courante
TournerGauche  Tourne a gauche
TournerDroite  Tourne a droite
Lever    Leve la plume
Baisser  Baisse la plume

Primitives "pascal" :

Initialiser initialisation de l'environnement graphique,
necessaire avant toute utilisation de la machine de trace
Terminer    fin de l'utilisation du mode graphique
Attendre    attente d'une touche au clavier


REALISATION :

L'etat de l'ecran (points allumes) n'est pas gere ici.
L'etat de la plume est represente par les donnees suivantes :
- 2 reels xa, ya : coordonnees cartesiennes du point courant,
dans le repere machine (origine en haut a gauche, y croissant
vers le bas)
- 1 reel da : direction courante : angle par rapport a l'axe des
x, dans le sens trigo, en radians.
- 1 valeur de type PosEcr = (Haute, Basse)  pour la position
d'ecriture

DegresVersRadians : la fonction : un reel -> un reel
conversion degres vers radians

=========================================================================  */

#include <stdio.h>
#include <math.h>
#include "machine_trace.h"
#include "graphlib_w.h"

static void flush() ;

typedef enum { Haute, Basse } PosEcr ;
/*  valeurs possibles de la position d'ecriture  */

static int XFen, YFen;  /* dimensions de la fenetre */
PosEcr PositionEcr;     /*  Position d'ecriture  */
double xa, ya;          /*  position (en absolu) de la plume  */
double da;  /* direction (angle / axe des x, en radians) de la plume  */
Couleur CouleurEcr ;    /* Couleur d'ecriture de la plume */
Couleur DerniereCouleur = Noir;
Couleur PremiereCouleur = Rouge;

Fenetre mywindow1, mywindow2;
int XCorner, YCorner;


/*  ___________________________________________ */
double DegresVersRadians (double d )
/*  Si d est la valeur de l'angle A en degres, DegresVersRadians (d) est
la valeur de l'angle A en radians
*/
{
  return  d * 2 * M_PI / 360 ;
}

/*  _____________________ */
void  Initialiser (int x, int y)
/*  e.i. : indifferent
e.f. : le mode graphique est initialise (la machine trace est
utilisable).
*/
{
  if ((x<0)||(x>XSize))
  XFen = XSize;
  else
  XFen = x;
  if ((y<0)||(y>XSize))
  YFen = YSize;
  else
  YFen = y;
  XCorner = 10;
  YCorner = 10;
  gr_inits_2(&mywindow1, XCorner, YCorner, XFen, YFen);
  XCorner += XFen + 20;
  gr_inits_w(&mywindow2, XCorner, YCorner, 200, 120, "Plume");
  write_gr(mywindow2, 10, 30, "pe      = (0,0)");
  write_gr(mywindow2, 10, 50, "cap     = 0");
  write_gr(mywindow2, 10, 70, "pp      = Haute");
  write_gr(mywindow2, 10, 90, "couleur = Noir");
  flush();
}


/*  _________________ */
void  Terminer ()
/*  e.i. :
e.f. : le mode graphique n'est plus utilisable
*/
{
  gr_close(&mywindow1);
  /*   gr_close(&mywindow2); */
}

/* ________________ */
void  Vider ()
/*  e.i. : le mode graphique est initialise
e.f. : - pp  = origine du repere (centre de l'ecran)
- cap = Ouest Est
- pe  = Haute
- etat de l'ecran : vide
*/
{
  xa = XFen / 2 ;
  ya = YFen / 2 ;
  da = 0 ;
  PositionEcr = Haute ;
  clear_screen(mywindow1);
  write_gr(mywindow2, 10, 30, "pe      = (0,0)");
  write_gr(mywindow2, 10, 50, "cap     = 0");
  write_gr(mywindow2, 10, 70, "pp      = Haute");
  write_gr(mywindow2, 10, 90, "couleur = Noir");
  flush ();
}

/* __________________ */
void  Effacer ()
/*  e.i. : le mode graphique est initialise
e.f. : l'ecran est vide. (pp, cap et pe inchanges)
*/
{
  clear_screen (mywindow1) ;
  flush ();
}

/* ______________________________________ */
void  Placer (double x, double y )
/*  (x,y) sont les coordonnees d'un point P dans le repere utilisateur :
origine au centre et y vers le haut
e.i. : pp = P0, pe = pe0, cap = d0
e.f. : pp  = P1 = (x, y), pe = pe0, cap = d0
si pe0 = Basse, le segment [P0,P1] est trace
*/
{
  double  xf, yf ;
  char    s[20];

  xf = x + XFen / 2;              /*  changement de repere  */
  yf = YFen / 2 - y ;
  if (PositionEcr == Basse) {
    line(mywindow1, floor(xa), floor(ya), floor(xf), floor(yf)) ;
    flush ();
  }
  xa = xf ; ya = yf  ;
  sprintf(s,"pe = (%.0lf,%.0lf)",x,y);
  overwrite_gr(mywindow2, 10, 30, s);
  flush ();
}


/* ________________________________ */
void  Orienter (double a)
/*  a est une valeur d'angle en degres  */
/*  e.i. : indifferent
e.f. : cap = a
*/
{
  char    s[20];
  da = DegresVersRadians (a) ;
  sprintf(s,"cap     = %.0lf    ",a);
  overwrite_gr(mywindow2, 10, 50, s);
  flush ();
}

/* ________________________________ */
void  Colorier (Couleur c)
/*  c est une couleur dans {Bleu, Vert, Rouge, Jaune, Noir}  */
/*  e.i. : indifferent
e.f. : CouleurEcr = c
*/
{
  char    s[20];

  switch (c) {
    case Rouge :
    set_red(mywindow1);
    CouleurEcr = Rouge;
    sprintf(s,"couleur  = Rouge  ");
    break;
    case Bleu :
    set_blue(mywindow1) ;
    CouleurEcr = Bleu;
    sprintf(s,"couleur  = Bleu  ");
    break;
    case Vert :
    set_green(mywindow1) ;
    CouleurEcr = Vert;
    sprintf(s,"couleur  = Vert  ");
    break;
    case Jaune :
    set_yellow(mywindow1) ;
    CouleurEcr = Jaune;
    sprintf(s,"couleur  = Jaune  ");
    break;
    case Noir :
    set_black(mywindow1) ;
    CouleurEcr = Noir;
    sprintf(s,"couleur = Noir");
    break;
  }

  overwrite_gr(mywindow2, 10, 90, s);
  flush();
}

void AvancerCouleur ()
{
  char s[20];

  if (CouleurEcr < Noir)
  CouleurEcr++;
  else
  CouleurEcr = Rouge;
  Colorier(CouleurEcr);
  switch (CouleurEcr)
  {
    case Rouge :
    sprintf(s,"couleur = Rouge");
    break;
    case Bleu :
    sprintf(s,"couleur = Bleu");
    break;
    case Vert :
    sprintf(s,"couleur  = Vert  ");
    break;
    case Jaune :
    sprintf(s,"couleur  = Jaune  ");
    break;
    case Noir :
    sprintf(s,"couleur  = Noir  ");
    break;
  }
  overwrite_gr(mywindow2, 10, 90, s);
  flush();
}

Couleur CouleurSuivante(Couleur c)
{
  if (c==DerniereCouleur)
  return PremiereCouleur;
  else
  return c+1;
}

/* ________________________________ */
void  Avancer (double L)
/*  e.i. : pp = (x0, y0), cap = d0, pe = pe0
e.f. : on a avance de L dans la direction d0, cad :
- pp = (x1, y1)
- cap = do (inchange)
- pe = pe0 (inchange)
- si pe0 = Basse, le segment [(x0,y0), (x1,y1)] est trace
*/
{
  double xf, yf ;
  char s[20];

  xf = xa + L * cos(da) ; yf = ya - L * sin(da) ;
  if (PositionEcr==Basse ) {
    line(mywindow1, floor(xa), floor(ya), floor(xf), floor(yf));
    flush();
  }
  xa = xf ; ya = yf ;
  sprintf(s,"pe = (%.0lf,%.0lf)",xf-XFen/2,-1*(yf-YFen/2));
  overwrite_gr(mywindow2, 10, 30, s);
  flush();
}

/* ________________________________ */
void  Reculer (double  L)
/*  e.i. : pp = (x0, y0), cap = d0, pe = pe0
e.f. : on a recule de L dans la direction d0, cad :
- pp = (x1, y1)
- cap = do (inchange)
- pe = pe0 (inchange)
- si pe0 = Basse, le segment [(x0,y0), (x1,y1)] est trace
*/
{ Avancer (-L) ; }



/* ___________________________ */
void  TournerGauche (double a)
/*  e.i. : cap = d0
e.f. : cap = d0 + a
*/
{
  char s[20];

  da = da + DegresVersRadians (a) ;
  sprintf(s,"cap     = %d    ",((int) (da*360/(2*M_PI))) % 360);
  overwrite_gr(mywindow2, 10, 50, s);
  flush ();
}


/* ___________________________ */
void  TournerDroite (double a)
/*  e.i. : cap = d0
e.f. : cap = d0 - a
*/
{
  char s[20];

  da = da - DegresVersRadians(a) ;
  sprintf(s,"cap     = %d    ",((int) (da*360/(2*M_PI))) % 360);
  overwrite_gr(mywindow2, 10, 50, s);
  flush ();
}


/* ________________ */
void  Lever ()
/*  e.i. : indifferent
e.f. : pe = haute
*/
{
  PositionEcr = Haute ;
  overwrite_gr(mywindow2, 10, 70, "pp      = Haute");
  flush ();
}

/* __________________ */
void  Baisser ()
/*  e.i. : indifferent
e.f. : pe = Basse
*/
{
  PositionEcr = Basse ;
  overwrite_gr(mywindow2, 10, 70, "pp      = Basse");
  flush ();
}


/* ___________________ */
void  Attendre ()
{
  wait_kbd(mywindow1) ;
}


/* ____________________ */
static void flush ()
{
  line(mywindow1, 1, 1, XSize -1, 1);
  line(mywindow2, 1, 1, XSize -1, 1);
}
