/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/


/* Interaction avec l'utilisateur */

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULR7, ANALYSER7, FIN]
 * -------------------------------------------------------------------
*/

#ifndef _INTERACTION_R7_H
#define _INTERACTION_R7_H

/* ----------------------------------------------------------
* CONSTANTES
* ----------------------------------------------------------
*/
#define NbMaxEssais 5
#define Invite "Votre Choix (? pour liste des commandes) : "
#define TexteSimulationR7 '1'
#define TexteAnalyseR7 '2'
#define TexteFin 'F'
#define TexteAide '?'

/* -------------------------------------------------------------------
* CodeCommande   : le type [SIMULR7, ANALYSER7, FIN]
* -------------------------------------------------------------------
*/
typedef enum {SIMULR7, ANALYSER7, FIN}     CodeCommande ;

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
