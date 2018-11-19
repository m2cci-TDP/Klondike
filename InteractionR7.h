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

typedef enum {SIMULR7, ANALYSER7, FIN}     CodeCommande ;

void SaisirCommande (CodeCommande *);

#endif
