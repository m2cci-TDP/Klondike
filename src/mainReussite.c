
#include <stdio.h>

#include "R7.h"
#include "C4.h"
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
  CodeCommande Commande ;
  int game;
  int nbparties ;
  const int NBMAXT = 3;

  InitAlea();
  printf (TexteBienvenue) ;

  printf("Choisissez une réussite entre 1 pour R7 et 2 pour C4 : ");
  scanf("%d",&game);

  switch (game)
  {
    case 1:
      SaisirCommande (&Commande) ;

      while (Commande != FIN) {
        switch  (Commande) {
          case SIMUL :
            printf(TexteNbASimuler);
            scanf("%d",&nbparties);
            OuvrirGraphique("R7");
            ObserverR7(nbparties, NBMAXT);
            FermerGraphique();
            break ;

          case ANALYSE :
            printf(TexteNbAAnalyser);
            scanf("%d",&nbparties);
            AnalyserR7(nbparties,NBMAXT);
            break;
        }
        SaisirCommande (&Commande) ;
      }
      break;

    case 2:
      SaisirCommande (&Commande) ;

      while (Commande != FIN) {
        switch  (Commande) {
          case SIMUL :
            printf(TexteNbASimuler);
            scanf("%d",&nbparties);
            OuvrirGraphique("C4");
            ObserverC4(nbparties);
            FermerGraphique();
            break ;

          case ANALYSE :
            printf(TexteNbAAnalyser);
            scanf("%d",&nbparties);
            AnalyserC4(nbparties);
            break;
        }
        SaisirCommande (&Commande) ;
      }
      break;
    }

    printf (TexteAuRevoir) ;
}
