/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/


/* Interaction avec l'utilisateur */

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULR7, ANALYSER7, FIN]
 * -------------------------------------------------------------------
*/

#ifndef _INTERACTION_H
#define _INTERACTION_H

#include "TypesConst.h"

/* ----------------------------------------------------------
* CONSTANTES
* ----------------------------------------------------------
*/
#define NbMaxEssais 5
#define Invite "Votre Choix (? pour liste des commandes) : "
#define TexteSimulation '1'
#define TexteAnalyse '2'
#define TexteFin 'F'
#define TexteAide '?'

/* -------------------------------------------------------------------
*      INTERACTION
*
*      EstTexteCommande : un caract�re ---> un bool�en
*      EcrireMenu       : une action
*      SaisirCommande   : une action (le r�sultat : un CodeCommande)
* -------------------------------------------------------------------
*/
void LireCar(char*);
int EstTexteCommande (char);
void EcrireMenu ();
void SaisirCommande (CodeCommande*);

#endif
