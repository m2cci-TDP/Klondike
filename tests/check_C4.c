#include "C4.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

typedef Tas SerieCouleurC4;
SerieCouleurC4 LigneC4[DerniereCouleur+1];
Tas TalonC4;
/* localisation des tas */
Localisation LocSeriesC4[DerniereCouleur+1];
Localisation LocTalonC4;


START_TEST (test_C4)
{
  Couleur Co;
  booleen Trouve = faux;
  int i = 0;

  OuvrirGraphique("test_C4");

  /*placer les 4 tas */
  SaisirLocTasC4();
  /* Création du talon avec un jeu de 32 cartes*/
  CreerJeuNeuf(32, LocTalonC4, &TalonC4);

  /* Création des séries vides de chaque couleur  */
  for (Co = DerniereCouleur; Co >= PremiereCouleur; Co--)
  {
    /*creer des emplacements de tas vides*/
    CreerTasVide(LocSeriesC4[Co], etale, &LigneC4[Co]);
    for (i = 0; i < NbCartes/4; i++) /* mettre 8 cartes dans chaque tas (distribution) */
    {
      DeplacerHautSous(&TalonC4, &LigneC4[Co]);
    }
  }

  /* test vrai lorsqu'on ne bat pas le talon */
  ck_assert_msg(reussirC4(AvecTrace) == vrai,
    "Sans battre le tas, un placement correct est attendu.");
  //ck_assert_int_eq(reussirC4(AvecTrace), vrai);
  /* test faux si une carte est déplacée */
  DeplacerHautSur(&LigneC4[PremiereCouleur], &LigneC4[DerniereCouleur]);
  ck_assert_msg(reussirC4(AvecTrace) == faux,
    "En Déplaçant une carte d'un tas sur un autre, un placement incorrect est attendu.");
  //ck_assert_int_eq(reussirC4(AvecTrace), faux);

  FermerGraphique();
}
END_TEST

Suite* C4_suite()
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("C4");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_set_timeout(tc_core, (double)0); /* turn off the timeout functionality CK_DEFAULT_TIMEOUT = 4' */

  tcase_add_test(tc_core, test_C4);
  suite_add_tcase(s, tc_core);

  return s;
}

int main()
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = C4_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
