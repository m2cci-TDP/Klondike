/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include "Interaction.h"

/* Interaction avec l'utilisateur */

void LireCar(char	*c)
{
	int l ;
	while (isspace (l=getchar ())) ;
	*c = l ;
}

int EstTexteCommande (char c)
{
	return (c == TexteSimulation) || (c == TexteAnalyse) || (c == TexteFin);
}

void EcrireMenu ()
{
	printf ("Tapez \n") ;
	printf (" %c pour Simulation graphique de la reussite, \n",TexteSimulation) ;
	printf (" %c pour Analyse d une serie de reussites (sans affichage graphique), \n",TexteAnalyse);
	printf (" %c pour Fin, \n",TexteFin);
	printf (" %c pour Aide.\n",TexteAide);
}

void SaisirCommande (CodeCommande *CC)
{
	char C  ;
	int NbEssais ;

	printf (Invite) ;
	LireCar (&C) ;
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
	if (NbEssais == NbMaxEssais) {
		*CC = FIN  ;
	}
	else switch (C)
	{
		case TexteSimulation :
			*CC = SIMUL ;
			break ;
		case TexteAnalyse :
			*CC = ANALYSE ;
			break ;
		case TexteFin :
			*CC = FIN ;
			break ;
	}
}
