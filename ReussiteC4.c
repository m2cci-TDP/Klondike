
#include <stdio.h>

/* Programme principal */

#include "C4.h"
#include "InteractionC4.h"
#include "Alea.h"

/* -------------------------------------------------------------------
 *      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
 * -------------------------------------------------------------------
 */
#define         TexteBienvenue           "Bienvenue \n"
#define         TexteNbASimuler          "Choisissez le nombre de parties a simuler : "
#define         TexteNbAAnalyser         "Choisissez le nombre de parties a analyser : "
#define         TexteAuRevoir            "Au revoir \n"

int main(void)
{
//suppression de NBTOURS
  CodeCommande    Commande ;
  int nbparties ;

  InitAlea();

  printf (TexteBienvenue) ;
  SaisirCommande (&Commande) ;
  while (Commande != FIN) {
    switch  (Commande) {
    case SIMULRC4 :
      printf(TexteNbASimuler);
      scanf("%d",&nbparties);
      OuvrirGraphique("C4");
      ObserverC4(nbparties);
      FermerGraphique();
      break ;

    case ANALYSERC4 :
      printf(TexteNbAAnalyser);
      scanf("%d",&nbparties);
      AnalyserC4(nbparties);
      break;
    }
    SaisirCommande (&Commande) ;

  }
  printf (TexteAuRevoir) ;
}
