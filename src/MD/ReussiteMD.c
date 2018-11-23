
#include <stdio.h>

/* Programme principal */

#include "MD.h"
#include "Interaction.h"
#include "Alea.h"

/* -------------------------------------------------------------------
*      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
* -------------------------------------------------------------------
*/
#define TexteBienvenue "Bienvenue \n"
#define TexteNbASimuler "Choisissez le nombre de parties a simuler : "
#define TexteNbAAnalyser "Choisissez le nombre de parties a analyser : "
#define TexteAuRevoir "Au revoir \n"

int main(void)
{
  //suppression de NBTOURS
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
        OuvrirGraphique("MD");
        ObserverMD(nbparties);
        FermerGraphique();
        break ;

      case ANALYSE :
        printf(TexteNbAAnalyser);
        scanf("%d",&nbparties);
        AnalyserMD(nbparties);
        break;

      default:
        break;
    }
    SaisirCommande (&Commande) ;

  }
  printf (TexteAuRevoir) ;
}
