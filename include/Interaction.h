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
/* -------------------------------------------------------------------
* CodeCommande   : le type [SIMUL, ANALYSE, FIN]
* -------------------------------------------------------------------
*/
typedef enum {SIMUL, ANALYSE, FIN} CodeCommande ;

typedef enum {R7, C4, MD, finGame} codeGame;
#define TexteR7 '1'
#define TexteC4 '2'
#define TexteMD '3'
#define TexteFinGame 'F'

#define Invite "\nVotre Choix (? pour liste des commandes) : "
#define TexteSimulation '1'
#define TexteAnalyse '2'
#define TexteFin 'F'
#define TexteAide '?'

#define TexteBienvenue "\n\n\t==== Bienvenue dans la réussite %s ====\n"
#define TexteNbASimuler "Choisissez le nombre de parties a simuler : "
#define TexteNbAAnalyser "Choisissez le nombre de parties a analyser : "
/* for R7 */
#define TexteNbPioche "Choisissez le nombre maximum de tour de pioche (défaut %d) : "
#define TexteAuRevoir "\nAu revoir \n"
#define TexteAuRevoirGame "\n\t==== Vous quittez la réussite %s ====\n"

/* -------------------------------------------------------------------
*      INTERACTION
*
*      EstTexteCommande : un caractère ---> un booléen
*      EcrireMenu       : une action
*      SaisirCommande   : une action (le résultat : un CodeCommande)
* -------------------------------------------------------------------
*/
void LireCar(char*);
int EstTexteCommande (char);
void EcrireMenu ();
void SaisirCommande (CodeCommande*);
/* use getchar to output default value if simply enter input */
void defaultScanf (char*, char);
void cleanBuffer();

/* for games */
int isGame(char);
void printGame(void);
void chooseGame (codeGame*);

#endif
