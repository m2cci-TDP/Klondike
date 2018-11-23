/* C4 */

#ifndef _MD_H
#define _MD_H

#include "AfficherTas.h"

void SaisirLocTasMD() ;
void CreerTableauInitialMD();
void ReformerTableauInitialMD() ;
void Monter(Tas*) ;
booleen Descendre(Tas*);
void AfficherMD() ;
booleen MonteStock() ;
booleen JouerUneMD(ModeTrace);
void ObserverMD(int);
void AnalyserMD(int);
void runReussiteMD();

#endif
