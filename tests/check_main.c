#include "check_klondike.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int number_failed;
  SRunner *sr;

  sr = srunner_create(C4_suite());
  srunner_add_suite (sr, Tas_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
