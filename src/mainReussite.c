
#include <stdio.h>

#include "R7.h"
#include "C4.h"
#include "Interaction.h"
#include "Alea.h"

/* -------------------------------------------------------------------
*      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
* -------------------------------------------------------------------
*/

int main(void)
{
  int game;

  InitAlea();

  printf ("\t\tBienvenue dans le jeu des reussites !\n\n") ;

  printf("Choisissez une réussite entre 1 pour R7 et 2 pour C4 : ");
  scanf("%d",&game);
  printf("\n");

  switch (game)
  {
    case 1:
      runReussiteR7();
      break;

    case 2:
      runReussiteC4();
      break;
    }

    return 0;
}
