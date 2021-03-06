#include "Tas.h"
#include "check_klondike.h"
#include <stdio.h>

START_TEST (test_card_bool)
{
  NbCartes = 32;

  Carte card = {Trefle, As, Cachee};
  Carte cardTest = card;

  ck_assert_msg(LeRang(card) == As,
  "Rang différent d'attendu");
  ck_assert_msg(LaCouleur(card) == Trefle,
  "Couleur différente d'attendue");
  ck_assert_msg(EstCachee(card),
  "Etat non caché");
  ck_assert_msg(!EstDecouverte(card),
  "Etat non caché");

  ck_assert_msg(MemeCouleur(cardTest, card),
  "Echec de la copie de la carte");
  card.CC = CouleurSuivante(card.CC);
  ck_assert_msg(CouleurInferieure(cardTest, card),
  "Incrémentation de la couleur fausse");
  ck_assert_msg(MemeRang(cardTest, card),
  "Echec de la copie de la carte");
  card.RC = RangSuivant(card.RC); // 7
  ck_assert_msg(!RangInferieur(cardTest, card),
  "Incrémentation du rang faux");
  ck_assert_msg(EstCarteAvant(cardTest, card),
  "Incrémentation du rang et de la couleur faux");
  cardTest.CC = CouleurSuivante(cardTest.CC);
  ck_assert_msg(!EstCarteAvant(cardTest, card),
  "Incrémentation du rang et de la couleur faux");
}
END_TEST

/* global deck for tests */
Tas T;
Localisation L = {1, 1};

void setup(void)
{
  CreerTasVide(L, empile, &T);
}

void teardown(void)
{
  LibererTasPlein(&T);
/*
  START_TEST (test_free)
  {
    ck_assert_msg(TasVide(T),
    "Echec de la création du tas (vide après création)");
    printf("%d==%d tete=%p\n", inactif, T.RT, T.tete);
    ck_assert_msg(!TasActif(T),
    "Echec de la création du tas (inactif après création)");
  }
  END_TEST
  */
}

START_TEST (test_exit_fail)
{
  fclose(stdout);
  CreerJeuNeuf(10, (Localisation){1,1}, &T);
}
END_TEST

START_TEST (test_deck_bool)
{
  ck_assert_msg(TasActif(T),
  "Echec de la création du tas (inactif)");
  ck_assert_msg(LaPlace(T).NC == L.NC && LaPlace(T).NL == L.NL,
  "Echec de la création du tas (localisation)");
  ck_assert_msg(LaHauteur(T) == 0,
  "Echec de la création du tas (hauteur)");
  ck_assert_msg(TasVide(T),
  "Echec de la création du tas (vide)");
  ck_assert_msg(TasEmpile(T),
  "Echec de la création du tas (empilé)");
  ck_assert_msg(!TasEtale(T),
  "Echec de la création du tas (non étalé)");

  CreerJeuNeuf(32, L, &T);
  ck_assert_int_eq(LaHauteur(T), 32);
}
END_TEST

/* Test if NB_DECK are different after shuffle */
Tas tableT[NB_DECK];
const int nbCards = 32;
const int alpha = 0.05; /* hypothèse de première espèce */
int nbDecksEq = 0;
void setupShuffle (void)
{
  int i;
  /* create decks */
  for (i = 0; i < NB_DECK; i++)
  {
    CreerTasVide((Localisation){1,1}, empile, tableT+i);
    CreerJeuNeuf(nbCards, (Localisation){1,1}, tableT+i);
    BattreTas(tableT+i);
  }
}
void teardownShuffle (void)
{
  int i;
  /* free decks */
  for (i = 0; i < NB_DECK; i++)
  {
    LibererTasPlein(tableT+i);
  }
}
START_TEST (test_shuffled_deck)
{
  int i;
  /* compare decks */
  for (i = 0; i < NB_DECK; i++)
  {
    /* looping test */
    if (i != _i && MemeTas (tableT+i, tableT+_i))
    {
      ck_abort_msg ("Echec entre %d et %d.", i, _i);
      nbDecksEq++;
    }
  }
}
END_TEST
START_TEST (test_all_shuffled_deck)
{
  ck_assert_msg(nbDecksEq / NB_DECK <= alpha,
    "Le mélange aléatoire des jeux de cartes ne respecte pas l'hypothèse de 5%% égaux.");
}
END_TEST

Suite* Tas_suite()
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tas.c");

  /* Card */
  tc_core = tcase_create("Cards");
  tcase_add_test(tc_core, test_card_bool);
  suite_add_tcase(s, tc_core);

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_exit_test(tc_core, test_exit_fail, 1);
  tcase_add_test(tc_core, test_deck_bool);
  suite_add_tcase(s, tc_core);

  /* Test shuffle */
  tc_core = tcase_create("Shuffle");
  tcase_add_checked_fixture(tc_core, setupShuffle, teardownShuffle);
  tcase_set_timeout(tc_core, (double)0); /* turn off the timeout functionality CK_DEFAULT_TIMEOUT = 4' */
  tcase_add_loop_test (tc_core, test_shuffled_deck, 0, NB_DECK);
  tcase_add_test(tc_core, test_all_shuffled_deck);
  suite_add_tcase(s, tc_core);

  return s;
}
