/*======================================================================

    INTERFACE DE LA MACHINE_TRACE

    machine_trace.h


    mettre la directive #include "machine_trace.h"
    apres l'entete de programme dans le programme l'utilisant

   Modif. P.Habraken 23/05/2005 :
   - mise en forme cosmetique
   - suppression macro Reculer
======================================================================*/

/*======================================================================
  Machine de trace  de dessins
========================================================================
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

    Vider        efface l'ecran et place la plume au centre,
                  position haute, cap Ouest-Est
    Effacer      efface l'ecran sans modifier l'etat de la plume.
    Placer       fixe la position de la plume, en coordonnees absolues
    Orienter     fixe la direction de la plume, par rapport a l'axe des x
    Avancer      Avance dans la direction courante
    Reculer      Recule dans la direction courante
    TournerGauche    Tourne a gauche
    TournerDroite    Tourne a droite
    Lever        Leve la plume
    Baisser      Baisse la plume

  Primitives "C" :

    Initialiser    initialisation de l'environnement graphique,
                   necessaire avant toute utilisation de la machine de trace
    Terminer       fin de l'utilisation du mode graphique
    Attendre       attente d'une touche au clavier


REALISATION :

    L'etat de l'ecran (points allumes) n'est pas gere ici.
    L'etat de la plume est represente par les donnees suivantes :
            - 2 reels xa,ya : coordonnees cartesiennes du point courant,
            dans le repere machine (origine en haut a gauche, y croissant
            vers le bas)
            - 1 reel da : direction courante : angle par rapport a l'axe des
            x, dans le sens trigo, en radians.
            - 1 valeur de type PosEcr = (Haute, Basse)  pour la position
            d'ecriture

    DegresVersRadians : la fonction : un reel -> un reel
    conversion degres vers radians

======================================================================*/

#ifndef _MACHINE_TRACE_H
#define _MACHINE_TRACE_H

typedef enum {Rouge, Vert, Bleu, Jaune, Noir} Couleur ;
/* couleurs de base */

extern    void    Initialiser ()     ;
/*  e.i. : indifferent
    e.f  : le mode graphique est initialise (la machine trace est
           utilisable).
 */

extern    void    Terminer ()     ;
/*  e.i. :
    e.f. : le mode graphique n'est plus utilisable
 */

extern    void    Vider ()     ;
/*  e.i. : le mode graphique est initialise
    e.f. : - pp     = origine du repere (centre de l'ecran)
           - cap   = Ouest Est
           - pe = Haute
           - etat de l'ecran : vide
 */

extern    void    Effacer ()     ;
/*  e.i. : le mode graphique est initialise
    e.f. : l'ecran est vide. (pp, cap et pe inchanges)
 */

extern    void    Placer (double x, double y )     ;
/*  (x,y) sont les coordonnees d'un point P dans le repere utilisateur :
    origine au centre et y vers le haut
    e.i. : pp = P0, pe = pe0, cap = d0
    e.f. : pp = P1 = (x, y), pe = pe0, cap = d0
           si pe0 = Basse, le segment [P0,P1] est trace
 */

extern    void    Orienter (double a)    ;
/*  a est une valeur d'angle en degres
    e.i. : indifferent
    e.f. : cap = a
 */

extern    void    Colorier (Couleur c) ;
/*  c est une couleur dans {Bleu, Vert, Rouge, Jaune, Noir}
    e.i. : indifferent
    e.f. : CouleurEcr = c
 */

extern    void    AvancerCouleur () ;

extern    Couleur CouleurSuivante(Couleur c) ;

extern    void    Avancer (double L)     ;
/*  e.i. : pp = (x0, y0), cap = d0, pe = pe0
    e.f. : on a avance de L dans la direction d0, cad :
           - pp = (x1, y1)
           - cap = do (inchange)
           - pe = pe0 (inchange)
           - si pe0 = Basse, le segment [(x0,y0), (x1,y1)] est trace
 */

extern    void     Reculer (double  L)     ;
/*  e.i. : pp = (x0, y0), cap = d0, pe = pe0
    e.f. : on a recule de L dans la direction d0, cad :
           - pp = (x1, y1)
           - cap = do (inchange)
           - pe = pe0 (inchange)
           - si pe0 = Basse, le segment [(x0,y0), (x1,y1)] est trace
 */

extern    void     TournerGauche (double a)     ;
/*  e.i. : cap = d0
    e.f. : cap = d0 + a
 */

extern    void     TournerDroite (double a)    ;
/*  e.i. : cap = d0
    e.f. : cap = d0 - a
 */

extern    void     Lever ()    ;
/*  e.i. : indifferent
    e.f. : pe = haute
 */

extern    void     Baisser ()    ;
/*  e.i. : indifferent
    e.f. : pe = Basse
 */

extern    void     Attendre ()    ;

/* Abreviations */

#define Plc(x,y)  Placer(x,y)
#define Ort(a)    Orienter(a)
#define Av(l)     Avancer(l)
#define Re(l)     Reculer(l)
#define TrG(a)    TournerGauche(a)
#define TrD(a)    TournerDroite(a)

#endif
