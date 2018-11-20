/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include "InteractionC4.h"

/* Interaction avec l'utilisateur */



void LireCar (char *c)
{
	int l ;
	while (isspace (l=getchar ())) ;  
	*c = l ;
}

int EstTexteCommande (char c)
{
  return
    ((c == TexteSimulationC4) ||
     (c == TexteAnalyseC4) ||
     (c == TexteFin)) ;
}

void EcrireMenu ()
{
  printf ("Tapez \n") ;
  printf ("%c pour Simulation graphique de la reussite C4, \n",TexteSimulationC4) ;
  printf (" %c pour Analyse d une serie de reussites C4 (sans affichage graphique), \n",TexteAnalyseC4);
  printf (" %c pour Fin, \n",TexteFin);
  printf (" %c pour Aide.\n",TexteAide);
}

void SaisirCommande (CodeCommande *CC)
{
  char C  ;
  int  NbEssais ;

  printf (Invite) ; LireCar (&C) ;
  NbEssais = 0 ;
  while ((NbEssais < NbMaxEssais) && (! EstTexteCommande (C)))
    {
      if (C == TexteAide)
	{
	  EcrireMenu ()  ;
	  LireCar (&C) ;
	}
      else
	{
	  printf ("Commande incorrecte.");
	  NbEssais++ ;
	  if (NbEssais < NbMaxEssais)
	    {
	      printf (Invite) ;
	      LireCar (&C) ;
	    }
	}
    }
  if (NbEssais == NbMaxEssais)
    *CC = FIN  ;
  else switch (C)
    {
    case TexteSimulationC4 : *CC = SIMULC4 ; break ;
    case TexteAnalyseC4 :    *CC = ANALYSEC4 ; break ;
    case TexteFin :          *CC = FIN ; break ;
    }
}
