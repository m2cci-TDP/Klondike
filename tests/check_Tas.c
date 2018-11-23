#include "Tas.h"
#include "check_klondike.h"

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

START_TEST (test_deck_bool)
{
  Tas T;
  Localisation L = {1, 1};

  CreerTasVide(L, empile, &T);
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
  LibererTasPlein(&T);
  ck_assert_msg(TasVide(T),
  "Echec de la création du tas (vide après création)");
}
END_TEST

Suite* Tas_suite()
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tas.c");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_set_timeout(tc_core, (double)4);

  tcase_add_test(tc_core, test_card_bool);
  tcase_add_test(tc_core, test_deck_bool);
  suite_add_tcase(s, tc_core);

  return s;
}
