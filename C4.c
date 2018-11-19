
/* Les 4 couleurs */

#include <stdio.h>

#include "C4.h"

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

  LocTalonC4.NC = 1;//placer le talon dans la premiere case du tableau
  LocTalonC4.NL = 1;

  for (i=PremiereCouleur; i<=DerniereCouleur; i++)
  {
    LocSeriesC4[i].NC = 2*i+2;//placer la série de 4 tas
    LocSeriesC4[i].NL = 1;
  }
}

void CreerTableauInitialC4()//creer les le talon + les tas
{
  Couleur Co;
  SaisirLocTasC4();//placer les 4 tas 
  
  /* Cr�ation du talon avec un jeu de 32 cartes*/
  CreerJeuNeuf(32, LocTalonC4, &TalonC4);
  BattreTas(&TalonC4);
  /* Cr�ation des s�ries vides de chaque couleur  */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
  {
    CreerTasVide(LocSeriesC4[Co], etale, &(LigneC4[Co]));//creer des emplacements de tas vides
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

/* Visualisation des �tats du jeu */

void AfficherC4()
{
  Couleur Co;

  EffacerGraphique();
  AfficherTas(TalonC4, "Talon");

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
  AfficherTas(LigneC4[Co], TexteCouleurC4[Co]);

  AttendreCliquer();
}

/* Jouer les 4 couleurs */

void JouerTasC4(Tas *T)
{
  Couleur Co;
  RetournerCarteSur(*T);
  Co=LaCouleur(CarteSur(*T));  
  DeplacerHautSous(T, &(LigneC4[Co]));

}

void JouerC4(ModeTrace MT)
{
  if (MT == AvecTrace)
  AfficherC4();
  Couleur Co;int i;
 
  for(Co=PremiereCouleur; Co<=DerniereCouleur; Co++){ 
  for(i=0;i<=8;i++){//mettre 8 cartes dans chaque tas (distribution)
  DeplacerHautSous(&TalonC4, &(LigneC4[Co]));}}
  AfficherC4();
  do
    RetournerCarteSur(&TalonC4);
    JouerTasC4(&TalonC4, &OK);
    if (!OK)
    DeplacerHautSur(&TalonC4, &RebutC4);
    if (MT == AvecTrace)
    AfficherC4();
    while (OK && !TasVide(RebutC4))	{
      /* On a jou� le talon ou le rebut. Le rebut n'est pas vide: on joue le rebut */
      JouerTasC4(&RebutC4, &OK);
      if (OK && (MT == AvecTrace))
      AfficherC4();
    }
  }
  while (!TasVide(TalonC4));
}

void JouerUneC4(ModeTrace MT)
{
  JouerUnTourC4(MT);
  /* Jeu d'au plus NMaxT tours */

  while (!(TasVide(RebutC4)) && (NumTourC4 < NMaxT))
  {
    RetournerTas(&RebutC4);
    PoserTasSurTas(&RebutC4, &TalonC4);
    JouerUnTourC4(MT);
    NumTourC4 = NumTourC4 + 1;
  }
  if (TasVide(RebutC4))
  {
    printf("Vous avez gagn� en %d tours !\n",NumTourC4);
  }
  else
  {
    printf("Vous avez perdu !\n");
  }
}

void ObserverC4(int NP, int NMaxT)
{
  int i;

  CreerTableauInitialC4();
  JouerUneC4(NMaxT, AvecTrace);
  for (i = 1; i <= NP-1; i++)
  {
    ReformerTableauInitialC4();
    JouerUneC4(NMaxT, AvecTrace);
  }
}

void AnalyserC4(int NP, int NMaxT)
{
  int i;

  CreerTableauInitialC4();
  JouerUneC4(NMaxT, SansTrace);
  for (i = 1; i <= NP-1; i++)
  {
    ReformerTableauInitialC4();
    JouerUneC4(NMaxT, SansTrace);
  }
}
