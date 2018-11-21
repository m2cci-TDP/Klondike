/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#ifndef _AFFICHER_TAS_H
#define _AFFICHER_TAS_H

#include "graphlib_w.h"
#include "Tas.h"

#include "cards.bm"
#include "back.bm"
#include "vide.bm"

#define EspX 50
#define EspY 70
#define DecY 20

void CreerImage(int, int, char*, XImage*);
void OuvrirGraphique(char*);
void FermerGraphique();
void EffacerGraphique();
void AttendreCliquer();
void AfficherCarte(Carte, int, int);
void AfficherTasVide(Localisation);
void AfficherTas(Tas, char*);

#endif
