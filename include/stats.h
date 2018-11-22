/****
* fichiers de calcul des statistiques pour toutes les réussites
****/

#ifndef _STATS_H
#define _STATS_H

#include <stdio.h>
#include <stdlib.h>

/* tableau dynamique des parties */
typedef struct StatsKlondike {
  int nbRestart;
  struct StatsKlondike *next;
} StatsKlondike;
typedef struct {
  int nbPart;
  StatsKlondike* head;
  StatsKlondike* tail;
} pStatsKlondike;

/* tableau dynamique des stats */
/* liste chainée circulaire avec fictif */
typedef struct Restart {
  int nbForWin;
  int number;
  struct Restart *next;
} Restart;
typedef Restart* pRestart;

/* constructeur */
pStatsKlondike initStats();
/* destructeur */
void freeStats(pStatsKlondike*);
/* ajout en queue du résultat
* 0 pas de partie jouées (échec de la partie)
* 1 et plus, nombre de relance du talon (réussite de la partie)
*/
void addStats(pStatsKlondike*, int);
/* visualisateur */
void printStats(pStatsKlondike);
/* affichage du pourcentage echec/reussite */
void pctStats(pStatsKlondike);
/* constructeur restart */
pRestart initRestart();
/* recherche de la partie */
void findRestart(pRestart*, int);
/* affichage */
void printNbRestart(pRestart, int);
/* destructeur Restart */
void freeRestart(pRestart*);
/* trie de la liste Restart */
void sort(pRestart *head);

#endif
