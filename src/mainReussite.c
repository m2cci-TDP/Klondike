
#include <stdio.h>

#include "R7.h"
#include "C4.h"
#include "MD.h"
#include "Interaction.h"
#include "Alea.h"

/* -------------------------------------------------------------------
*      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
* -------------------------------------------------------------------
*/

int main(void)
{
  codeGame cG;

  InitAlea();

  printf ("\n\n\t\tKLONDIKE\n\n") ;

  do
  {
    chooseGame(&cG);

    switch (cG) {
      case R7:
      runReussiteR7();
      break;

      case C4:
      runReussiteC4();
      break;

      case MD:
      runReussiteMD();
      break;

      default:
      break;
    }
  } while (cG != finGame);
  
  printf (TexteAuRevoir) ;

  return 0;
}
