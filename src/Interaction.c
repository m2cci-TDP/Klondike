/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005,
d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
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

int isGame(char c)
{
	return (c == TexteR7) || (c == TexteC4) || (c == TexteMD) || (c == TexteFinGame);
}

void EcrireMenu ()
{
	printf ("\nAide :\n") ;
	printf (" %c pour un simulation graphique de la reussite, \n",TexteSimulation) ;
	printf (" %c pour une analyse d'une serie de reussites (sans affichage graphique), \n",TexteAnalyse);
	printf (" %c pour Fin, \n",TexteFin);
	printf (" %c pour Aide.\n",TexteAide);
}

void printGame(void)
{
	printf ("\nAide :\n") ;
	printf (" %c pour jouer au relais des 7, \n", TexteR7) ;
	printf (" %c pour jouer aux quatre couleurs, \n", TexteC4);
	printf (" %c pour jouer à la Montée-Descente, \n", TexteMD);
	printf (" %c pour Fin, \n",TexteFinGame);
	printf (" %c pour Aide.\n",TexteAide);
}

void SaisirCommande (CodeCommande *CC)
{
	char C  ;

	do
	{
		printf (Invite) ;
		LireCar (&C) ;

		switch (C)
		{
			case TexteAide:
			EcrireMenu ()  ;
			break;

			case TexteSimulation :
			*CC = SIMUL ;
			break ;

			case TexteAnalyse :
			*CC = ANALYSE ;
			break ;

			case TexteFin :
			*CC = FIN ;
			break ;

			default:
			printf ("Commande incorrecte.\n");
			printf("Essayez %c.\n", TexteAide);
			break;
		}
	} while (!EstTexteCommande (C));
}

void chooseGame (codeGame *cG)
{
	char C  ;

	do
	{
		printf (Invite) ;
		LireCar (&C) ;

		switch (C)
		{
			case TexteAide:
			printGame ()  ;
			break;

			case TexteR7 :
			*cG = R7 ;
			break ;

			case TexteC4 :
			*cG = C4 ;
			break ;

			case TexteMD :
			*cG = MD ;
			break ;

			case TexteFinGame :
			*cG = finGame ;
			break ;

			default:
			printf ("Commande incorrecte.\n");
			printf("Essayez %c.\n", TexteAide);
			break;
		}
	} while (!isGame (C));
}

void defaultScanf (int *value, int defaultValue)
{
	char trash;

	*value = getchar();

	/* set the default value */
	if (*value == '\n') {
		*value = defaultValue;
	}

	/* clean the buffer */
	do trash = getchar();
	while (trash != '\n' && trash != EOF);
}
