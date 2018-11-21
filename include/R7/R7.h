/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Le relais des 7 */

#ifndef _R7_H
#define _R7_H

#include "AfficherTas.h"

void SaisirLocTasR7();
void CreerTableauInitialR7();
void ReformerTableauInitialR7();
void AfficherR7();
void JouerTasR7(Tas*, booleen*);
void JouerUnTourR7(ModeTrace);
void JouerUneR7(int, ModeTrace);
void ObserverR7(int, int);
void AnalyserR7(int, int);

#endif
