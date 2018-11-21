/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>

/* Programme principal */

#include "R7.h"
#include "Interaction.h"
#include "Alea.h"

/* -------------------------------------------------------------------
*      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
* -------------------------------------------------------------------
*/
#define TexteBienvenue "Bienvenue \n"
#define TexteNbASimuler "Choisissez le nombre de parties a simuler : "
#define TexteNbAAnalyser "Choisissez le nombre de parties a analyser : "
#define TexteNbPioche "Choisissez le nombre maximum de tour de pioche (défaut %d) : "
#define TexteAuRevoir "Au revoir \n"

int main(void)
{
  int NBMAXT = 3;

  CodeCommande Commande ;
  int nbparties ;

  InitAlea();

  printf (TexteBienvenue) ;
  SaisirCommande (&Commande) ;
  while (Commande != FIN) {
    switch  (Commande) {
      case SIMUL :
        printf(TexteNbASimuler);
        scanf("%d",&nbparties);
        printf(TexteNbPioche, NBMAXT);
        scanf("%d", &NBMAXT);
        OuvrirGraphique("R7");
        ObserverR7(nbparties, NBMAXT);
        FermerGraphique();
        break ;

      case ANALYSE :
        printf(TexteNbAAnalyser);
        scanf("%d",&nbparties);
        printf(TexteNbPioche, NBMAXT);
        scanf("%d", &NBMAXT);
        AnalyserR7(nbparties,NBMAXT);
        break;

      default:
        break;
    }
    SaisirCommande (&Commande) ;

  }
  printf (TexteAuRevoir) ;
}
