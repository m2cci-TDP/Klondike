/* Les 4 couleurs */

#include <stdio.h>

#include "C4.h"
#include "stats.h"

char TexteCouleurC4[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

/* Tableau de jeu */


typedef Tas SerieCouleurC4;
SerieCouleurC4 LigneC4[DerniereCouleur+1];
Tas TalonC4;
/* localisation des tas */
Localisation LocSeriesC4[DerniereCouleur+1];
Localisation LocTalonC4;

/* Formation du tableau de jeu initial */

void SaisirLocTasC4()
{
  int i;

  LocTalonC4.NC = 1; /* placer le talon dans la premiere case du tableau */
  LocTalonC4.NL = 1;

  for (i=PremiereCouleur; i<=DerniereCouleur; i++)
  {
    LocSeriesC4[i].NC = 2*i+2; /* placer la série de 4 tas */
    LocSeriesC4[i].NL = 1;
  }
}

void CreerTableauInitialC4() /*creer les le talon + les tas*/
{
  Couleur Co;
  SaisirLocTasC4(); /*placer les 4 tas */

  /* Création du talon avec un jeu de 32 cartes*/
  CreerJeuNeuf(32, LocTalonC4, &TalonC4);
  BattreTas(&TalonC4);
  /* Création des séries vides de chaque couleur  */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
  {
    CreerTasVide(LocSeriesC4[Co], etale, &(LigneC4[Co])); /*creer des emplacements de tas vides*/
  }
}

void ReformerTableauInitialC4()
{
  Couleur Co;

  /* On reforme le talon, en empilant les cartes de la ligne */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
  {
    EmpilerTas(&(LigneC4[Co]));
    PoserTasSurTas(&(LigneC4[Co]), &TalonC4);
    EtalerTas(&(LigneC4[Co]));
  }
  RetournerTas(&TalonC4);
  BattreTas(&TalonC4);
}
/* Visualisation des états du jeu */

void RetournerSiPasRetourner(Tas *T) { //Retourne les cartes non retournées d'un tas - Utilisée en fin de partie
    int i;
    for (i = LaHauteur(*T); i >= 1; i--) {
        if (EstCachee(IemeCarte(*T, i))){
            EchangerCartes(i, LaHauteur(*T), T);
            RetournerCarteSur(T);
            EchangerCartes(i, LaHauteur(*T), T);
        }
    }
}
void AfficherC4()
{
  Couleur Co;

  EffacerGraphique();
  AfficherTas(TalonC4, "Talon");

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++) {
    AfficherTas(LigneC4[Co], TexteCouleurC4[Co]);
  }

  AttendreCliquer();
}


void JouerTasC4(Tas *T, Couleur *Co)
{
  RetournerCarteSur(T);
  *Co=LaCouleur(CarteSur(*T));
  DeplacerHautSous(T, &LigneC4[*Co]);
  RetournerCarteSous(&LigneC4[*Co]);
}

booleen reussirC4(ModeTrace MT) {
    Couleur Co = PremiereCouleur;
    int i = 1;
    int j;

    while (LaCouleur(IemeCarte(LigneC4[Co], i)) == Co && !((Co == DerniereCouleur) && (i == 8))) { //Trouver l'intrus dans la couleur, si non trouvé = gagné

        if (i == LaHauteur(LigneC4[Co])) {
            i = 0;
            Co = CouleurSuivante(Co);
        } else {
            i++;
        }
    }
    for (j = 1; j < 5; j++) { //Retourner toutes les cartes non retournées en fin de partie
        if (MT == AvecTrace) {
            RetournerSiPasRetourner(&LigneC4[j]);

        }
        
    }
    if (MT == AvecTrace) AfficherC4();
    return (Co == DerniereCouleur) && (i == NbCartes / 4);
}

void JouerC4(ModeTrace MT)
{
  if (MT == AvecTrace)
  {
    AfficherC4();
  }
  Couleur Co2 = PremiereCouleur;
  Couleur Co;
  int i;

  for(Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
  {
    for(i=0; i<NbCartes/4; i++) /* mettre 8 cartes dans chaque tas (distribution) */
    {
      DeplacerHautSous(&TalonC4, &(LigneC4[Co]));
    }
  }
  if (MT == AvecTrace)
  {
    AfficherC4();
  }
  do
  {
    RetournerCarteSur(&LigneC4[Co2]);
    if (MT == AvecTrace)
    {
      AfficherC4();
    }
    JouerTasC4(&LigneC4[Co2], &Co); /* jouer le tas courant */
    Co2 = Co;/* se placer dans le tas de destination */
    if (MT == AvecTrace)
    {
      AfficherC4();
    }
  } while (!EstDecouverte(CarteSur(LigneC4[Co2])));
}

booleen JouerUneC4(ModeTrace MT)
{
  JouerC4(MT);

  return reussirC4(MT);
}

void ObserverC4(int NP)
{
  int i = 0;

  CreerTableauInitialC4();
  while (i < NP) {
    if (JouerUneC4(AvecTrace))
    {
      printf("Vous avez gagné !\n");
    }
    else
    {
      printf("Vous avez perdu !\n");
    }
    ReformerTableauInitialC4();
    i++;
  }
}

void AnalyserC4(int NP)
{
  int i = 0;
  pStatsKlondike stats = initStats();

  CreerTableauInitialC4();
  while (i < NP) {
    addStats(&stats, JouerUneC4(SansTrace));
    ReformerTableauInitialC4();
    i++;
  }

  pctStats(stats);
  freeStats(&stats);
}
