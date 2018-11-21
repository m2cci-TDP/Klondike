#include "stats.h"

int main()
{
  pStatsKlondike stats = initStats();

  addStats(&stats, 0);
  addStats(&stats, 3);
  addStats(&stats, 1);
  addStats(&stats, 0);
  addStats(&stats, 2);
  addStats(&stats, 1);
  addStats(&stats, 0);
  addStats(&stats, 1);
  addStats(&stats, 2);

  printStats(stats);

  pctStats(stats);

  freeStats(&stats);

  return 0;
}
