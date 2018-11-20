/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/


/* Interaction avec l'utilisateur */

#ifndef _INTERACTION_C4_H
#define _INTERACTION_C4_H

/* ----------------------------------------------------------
 * CONSTANTES
 * ----------------------------------------------------------
*/

#define         NbMaxEssais              5
#define         Invite                   "Votre Choix (? pour liste des commandes) : "
#define         TexteSimulationC4        '1'
#define         TexteAnalyseC4           '2'
#define         TexteFin                 'F'
#define         TexteAide                '?'

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULC4, ANALYSEC4, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMULC4, ANALYSEC4, FIN}     CodeCommande ;

/* -------------------------------------------------------------------
 *      INTERACTION
 *
 *      EstTexteCommande : un caract�re ---> un bool�en
 *      EcrireMenu       : une action
 *      SaisirCommande   : une action (le r�sultat : un CodeCommande)
 * -------------------------------------------------------------------
*/

void LireCar (char*);
int EstTexteCommande (char);
void EcrireMenu ();
void SaisirCommande (CodeCommande *);

#endif