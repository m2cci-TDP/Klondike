#include "stats.h"

pStatsKlondike initStats()
{
  pStatsKlondike stats;
  stats.nbPart = 0;
  stats.head = NULL;
  stats.tail = NULL;
  return stats;
}

/* ajout en queue */
void addStats(pStatsKlondike *stats, int result)
{
  StatsKlondike* newCell = (StatsKlondike*)malloc(sizeof(StatsKlondike));

  if (newCell == NULL)
  {
    printf("Memory full...\n");
    exit(1);
  }
  else
  {
    newCell->nbRestart = result;
    newCell->next = NULL;
    if (stats->head == NULL)
    {
      /* initialisation de la tête */
      stats->head = newCell;
    }
    else
    {
      /* changement de la queue */
      stats->tail->next = newCell;
    }
    stats->tail = newCell;
    stats->nbPart++;
  }
}

void freeStats(pStatsKlondike *stats)
{
  StatsKlondike* currentCell = stats->head;
  StatsKlondike* previousCell = NULL;
  while (currentCell != NULL)
  {
    previousCell = currentCell;
    currentCell = currentCell->next;
    free(previousCell);
  }
  *stats = initStats();
}

void printStats(pStatsKlondike stats)
{
  StatsKlondike* currentCell = stats.head;
  printf("Nombre de relance en %d parties :\n", stats.nbPart);
  while (currentCell != NULL)
  {
    printf("%d ", currentCell->nbRestart);
    currentCell = currentCell->next;
  }
  printf("\n");
}

void pctStats(pStatsKlondike stats)
{
  StatsKlondike* currentCell = stats.head;
  pRestart head = initRestart();
  int nbLose = 0, nbWin = 0;

  while (currentCell != NULL)
  {
    switch (currentCell->nbRestart)
    {
      case 0:
        break;
      default:
        /* recherche */
        findRestart(&head, currentCell->nbRestart);

        nbWin++;
        break;
    }
    currentCell = currentCell->next;
  }

  /* affichage */
  nbLose = stats.nbPart - nbWin;
  printf("\n");
  printf("\t\t==== STATS ====\n");
  printf("Nombre de parties gagnées : %d (%d%%)\n", nbWin, 100*nbWin/stats.nbPart);
  printNbRestart(head, nbWin);
  printf("Nombre de parties perdues : %d (%d%%)\n", nbLose, 100*nbLose/stats.nbPart);
  printf("\t\t===============\n\n");

  freeRestart(&head);
}

pRestart initRestart()
{
    pRestart head = (pRestart)malloc(sizeof(Restart));
    /* init head */
    if (head == NULL)
    {
      printf("Memory full...\n");
      exit(1);
    }
    head->nbForWin = 0;
    head->number = -1;
    head->next = head;
    return head;
}

void findRestart(pRestart *head, int nbRestart)
{
  pRestart currentCell = (*head)->next;

  (*head)->nbForWin = nbRestart;
  while (currentCell->nbForWin != nbRestart) {
    currentCell = currentCell->next;
  }
  if (currentCell == *head)
  {
    /* not find
    * ajout */
    currentCell = (pRestart)malloc(sizeof(Restart));
    currentCell->nbForWin = nbRestart;
    currentCell->number = 1;
    currentCell->next = (*head)->next;
    (*head)->next = currentCell;
  }
  else {
    /* find
    * incrementation */
    currentCell->number++;
  }
}

void printNbRestart(pRestart head, int nbWin)
{
  pRestart currentCell = head->next;
  while (currentCell != head)
  {
    printf("\t%d (%d%%) parties gagnées en %d tours\n", currentCell->number, 100*currentCell->number/nbWin, currentCell->nbForWin);
    currentCell = currentCell->next;
  }
}

void freeRestart(pRestart *head)
{
  pRestart currentCell = NULL;
  /* libération */
  while(*head != (*head)->next)
  {
    currentCell = (*head)->next;
    (*head)->next = currentCell->next;
    free(currentCell);
  }
  free(*head);
}
