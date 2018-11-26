/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
d'apres les algorithmes de Pierre-Claude Scholl
modifie par F. Carrier, juillet 2012
--> types enumeres : Couleur, Rang
--> tas representes par des listes chainees
----------------------------------------------------------------*/

#include "Tas.h"
#include "Alea.h"
#include <stdio.h>

/*-----------------------------------*/
/* Specifications des objets de base */
/*-----------------------------------*/

/* Couleurs et rangs */

/* Couleurs
Ordre croissant sur les couleurs: trefle, carreau, coeur, pique
typedef enum {VideC, Trefle, Carreau, Coeur, Pique} Couleur;
*/
Couleur CouleurSuivante(Couleur C) {
  if (C < DerniereCouleur) {
    C = (Couleur)((int)C + 1);
  }
  else {
    C = PremiereCouleur;
  }

  return C;
}

/* Rangs
Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as
typedef enum {VideR0, VideR1, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix,
Valet, Dame, Roi, As} Rang;
*/
Rang RangSuivant(Rang R) {
  if (R < DernierRang) {
    R = (Rang)((int)R + 1);
  }
  else {
    R = PremierRang;
  }

  return R;
}

/*--------------------------------------------------------------------*/
/* Representation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Representation des cartes */

/* Testeurs et selecteurs */

/*
typedef struct {
Couleur CC;
Rang RC;
Visibilite VC;
} ValeurCarte;
typedef ValeurCarte Carte;
*/

Rang LeRang(Carte C) {
  return C.RC;
}

Couleur LaCouleur(Carte C) {
  return C.CC;
}

Visibilite EstCachee(Carte C) {
  return C.VC == Cachee;
}

Visibilite EstDecouverte(Carte C) {
  return C.VC == Decouverte;
}

/* Comparaison de cartes */

booleen RangInferieur(Carte C1, Carte C2) {
  return LeRang(C1) < LeRang(C2);
}

booleen MemeRang(Carte C1, Carte C2) {
  return LeRang(C1) == LeRang(C2);
}

booleen CouleurInferieure(Carte C1, Carte C2) {
  return LaCouleur(C1) < LaCouleur(C2);
}

booleen MemeCouleur(Carte C1, Carte C2) {
  return LaCouleur(C1) == LaCouleur(C2);
}

booleen EstCarteAvant(Carte C1, Carte C2) {
  return CouleurInferieure(C1, C2) || (MemeCouleur(C1, C2) && RangInferieur(C1, C2));
}

/* compare deux tas de même hauteur */
booleen MemeTas (Tas *T1, Tas *T2)
{
  int nbCardsEq = 0, hi, hT = LaHauteur(*T1);

  if (hT != LaHauteur(*T2))
  {
    printf("\'T1\' and \'T2\' must have the same height.");
    exit(1);
  }
  /* test the current deck with other */
  for (hi = 1; hi <= hT; hi++)
  {
    nbCardsEq += MemeRang(CarteSous(*T1), CarteSous(*T2)) && MemeCouleur(CarteSous(*T1), CarteSous(*T2));
    DeplacerBasSur(T1, T1);
    DeplacerBasSur(T2, T2);
  }

  return nbCardsEq == hT;
}

/* Representation des tas */

/* Testeurs et selecteurs */

booleen TasActif(Tas T) {
  return T.RT == actif;
}

booleen TasVide(Tas T) {
  return T.HT == 0  && T.tete == NULL && T.queue == NULL;
}

booleen TasEmpile(Tas T) {
  return T.MT == empile;
}

booleen TasEtale(Tas T) {
  return T.MT == etale;
}

int LaHauteur(Tas T) {
  return T.HT;
}

Localisation LaPlace(Tas T) {
  /*
  Localisation l;
  l.NL = (T.LT).NL;
  l.NC = (T.LT).NC;
  return l;
  */
  return T.LT;
}

/* Constructeurs */

/* *************************************************************
void CreerTasVide(Localisation L, Mode M, Tas *T)
associe à T un tas vide actif placé en L et de mode d'étalement M.
Pré-condition : l'emplacement L est disponible
**************************************************************** */
void CreerTasVide(Localisation L, Mode M, Tas *T) {
  T->LT = L;
  T->RT = actif;
  T->MT = M;
  T->HT = 0;
  T->tete = NULL;
  T->queue = NULL;
}

/* *************************************************************
void SupprimerTasVide(Tas *T)
rend le tas vide inactif. En particulier, la place qu'il occupait
devient libre pour un autre tas.
Pré-condition : le tas T est vide et actif
**************************************************************** */
void SupprimerTasVide(Tas *T) {
  if (TasVide(*T) && TasActif(*T)) {
    T->LT.NL = -1;
    T->LT.NC = -1;
    T->RT = inactif;
  }
}

/* *************************************************************
void CreerJeuNeuf(int N, Localisation L, Tas *T)
forme en L le tas empilé T avec l'ensemble des N cartes du jeu dans
l'ordre des cartes et faces cachées.
Donne leur valeur aux variables globales NbCartes et PremierRang.
Pré-condition : l'emplacement L est libre
N==52 ou N==32
**************************************************************** */
void CreerJeuNeuf(int N, Localisation L, Tas *T) {
  pAdCarte newCarte = NULL;
  Couleur couleurCourante = PremiereCouleur;
  Rang rangCourant;

  if (N != 52 && N != 32) {
    printf("A deck of cards must have 52 or 32 cards...\n");
    exit(1);
  } else {
    // initialisation de la variable globale PremierRang
    switch (N) {
      case 52:
      PremierRang = Deux;
      break;
      case 32:
      PremierRang = Sept;
      break;
    }
  }
  rangCourant = PremierRang;
  CreerTasVide(L, empile, T);
  NbCartes = N; // init variable globale NbCartes

  // remplissage du paquet de carte par ajout en queue
  while (LaHauteur(*T) < NbCartes) {
    newCarte = (pAdCarte)malloc(sizeof(adCarte));
    if (newCarte == NULL) {
      printf("Memory full...");
      exit(1);
    } else {
      newCarte->elt.CC = couleurCourante;
      newCarte->elt.RC = rangCourant;
      newCarte->elt.VC = Cachee;
      AjouterCarteSurTas(newCarte, T);

      rangCourant = RangSuivant(rangCourant);
      if (rangCourant == PremierRang) {
        // changement de couleur
        couleurCourante = CouleurSuivante(couleurCourante);
      }
    }
  }
}

/* destructeur (pour les tests) */
void LibererTasPlein(Tas *T)
{
  pAdCarte currentCard = T->tete;
  if (!TasVide(*T))
  {
    while (currentCard != NULL)
    {
      SupprimerCarteSous(T);
      free(currentCard);
      currentCard = T->tete;
    }

    SupprimerTasVide(T);
  }
}

/* Consultation des cartes d'un tas: ne deplace pas la carte */

/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T) {
  return T.queue->elt;
}

/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T) {
  return T.tete->elt;
}

pAdCarte pIemeCarte(Tas T, int i) {
  pAdCarte currentCell = T.tete;
  int cardI = 1;

  if (i == 1) {
    currentCell = T.tete;
  } else if (i == LaHauteur(T)) {
    currentCell = T.queue;
  } else if (i > LaHauteur(T) || i < 1) {
    printf("i must be upper than 1 and lower than \"LaHauteur(T)\".");
    exit(1);
  } else {
    while (cardI < i)
    {
      currentCell = currentCell->suiv;
      cardI++;
    }
  }

  return currentCell;
}

/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Précondition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i) {
  return pIemeCarte(T, i)->elt;
}

/* Retournement d'une carte sur un tas */

/* *************************************************************
void RetournerCarteSur(Tas *T)
retourne la carte située au dessus du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSur(Tas *T) {
  if (T != NULL)
  {
    T->queue->elt.VC = !T->queue->elt.VC;
  }
}

/* *************************************************************
void RetournerCarteSous(Tas *T)
retourne la carte située au dessous du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSous(Tas *T) {
  if (T != NULL)
  {
    T->tete->elt.VC = !T->tete->elt.VC;
  }
}

/* Modification d'un tas */

/* *************************************************************
void EmpilerTas(Tas *T)
void EtalerTas(Tas *T)
modification du mode d'etalement d'un tas
**************************************************************** */
void EmpilerTas(Tas *T) {
  T->MT = empile;
}

void EtalerTas(Tas *T) {
  T->MT = etale;
}

void AjouterCarteApres (pAdCarte adC, pAdCarte adAvC, Tas *T) {
  if (adAvC == NULL) { // ajout en tete
    AjouterCarteSousTas(adC, T);
  } else if (adAvC->suiv == NULL) { // ajout en queue
    AjouterCarteSurTas(adC, T);
  } else { // ajout au milieu
    adC->suiv = adAvC->suiv;
    adC->prec = adAvC;
    adAvC->suiv->prec = adC;
    adAvC->suiv = adC;

    T->HT++;
  }
}

/* *************************************************************
void EchangerCartes(int i, int j, Tas *T)
echange les cartes i et j du tas T
Precondition : les deux cartes existent i,j <= LaHauteur(T)
**************************************************************** */
void EchangerCartes(int i, int j, Tas *T) {
  pAdCarte adI = NULL, adJ = NULL, adAvJ = NULL, adAvI = NULL;

  if (i != j)
  {
    adI = pIemeCarte(*T, i);
    adJ = pIemeCarte(*T, j);

    /* sauvegarde des adresses avant i et j */
    adAvJ = adJ->prec;
    adAvI = adI->prec;

    /* déconnection de j et de i */
    SupprimerCarte(adJ, T);
    SupprimerCarte(adI, T);

    /* reconnection de i et de j */
    if (i == j - 1) {
      AjouterCarteApres(adJ, adAvI, T);
      AjouterCarteApres(adI, adJ, T);
    } else if (j == i - 1) {
      AjouterCarteApres(adI, adAvJ, T);
      AjouterCarteApres(adJ, adI, T);
    } else {
      AjouterCarteApres(adI, adAvJ, T);
      AjouterCarteApres(adJ, adAvI, T);
    }
  }
}

/* *************************************************************
void BattreTas(Tas *T)
bas le tas T
based on the Fisher-Yates algorithm (1938)
https://fr.wikipedia.org/wiki/M%C3%A9lange_de_Fisher-Yates
**************************************************************** */
void BattreTas(Tas *T) {
  /* InitAlea(); // déjà fait dans le main */
  int i = LaHauteur(*T) - 1, nbAlea;

  while (i > 0)
  {
    nbAlea = UnEntier(i);
    EchangerCartes(nbAlea, i, T);

    i--;
  }
}

/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T) {
  int i = 1;
  pAdCarte oldTail = NULL, head = NULL;

  /* retournement des cartes */
  while (i <= LaHauteur(*T))
  {
    RetournerCarteSous(T);
    DeplacerBasSur(T, T);
    i++;
  }
  /* retournement du tas */
  oldTail = T->queue;
  while (oldTail != T->tete) {
    head = T->tete;
    SupprimerCarteSous(T);
    AjouterCarteApres(head, oldTail, T);
  }
}

/* fix bug retournement lors du test de la réussite
Met à visible toutes les cartes d'un tas */
void DecouvrirCartesTas(Tas *T) {
  int i;
  for (i = 1; i <= LaHauteur(*T); i++)
  {
    if (EstCachee(CarteSous(*T))) {
      RetournerCarteSous(T);
    }
    DeplacerBasSur(T, T);
  }
}

/* Deplacements de cartes d'un tas sur un autre */

void AjouterCarteSurTasVide (pAdCarte ac, Tas *T) {
  ac->suiv = T->queue;
  ac->prec = T->tete;
  T->tete = ac;
  T->queue = ac; // tete=queue

  T->HT++;
}

/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (pAdCarte ac, Tas *T) {
  if (TasVide(*T)) {
    AjouterCarteSurTasVide(ac, T);
  } else {
    ac->suiv = T->queue->suiv;
    ac->prec = T->queue;
    T->queue->suiv = ac;
    T->queue = ac;

    T->HT++;
  }
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (pAdCarte ac, Tas *T) {
  if (TasVide(*T)) {
    AjouterCarteSurTasVide(ac, T);
  } else {
    ac->suiv = T->tete;
    ac->prec = T->tete->prec;
    T->tete->prec = ac;
    T->tete = ac;

    T->HT++;
  }
}

void SupprimerCarteSur (Tas *T) {
  T->queue = T->queue->prec;
  if (T->queue == NULL) {
    T->tete = T->queue;
  } else {
    T->queue->suiv = NULL;
  }

  T->HT--;
}

void SupprimerCarteSous (Tas *T) {
  T->tete = T->tete->suiv;
  if (T->tete == NULL) {
    T->queue = T->tete;
  } else {
    T->tete->prec = NULL;
  }

  T->HT--;
}

/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enlève la carte située au dessus de T1 et la place au dessus de T2
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2) {
  pAdCarte adC = T1->queue;
  SupprimerCarteSur(T1);
  AjouterCarteSurTas(adC, T2);
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enlève la carte située au dessus de T1 et la place au dessous de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2) {
  pAdCarte adC = T1->queue;
  SupprimerCarteSur(T1);
  AjouterCarteSousTas(adC, T2);
}

/* *************************************************DeplacerHautSous*****************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enlève la carte située au dessous de T1 et la place au dessus de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2) {
  pAdCarte adC = T1->tete;
  SupprimerCarteSous(T1);
  AjouterCarteSurTas(adC, T2);
}

/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enlève la carte située au dessous de T1 et la place au dessous de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2) {
  pAdCarte adC = T1->tete;
  SupprimerCarteSous(T1);
  AjouterCarteSousTas(adC, T2);
}

void SupprimerCarte(pAdCarte adC, Tas* T) {
  if (adC->prec == NULL) { // adC == tete
    SupprimerCarteSous(T);
  } else if (adC->suiv == NULL) { // adC == queue
    SupprimerCarteSur(T);
  } else {
    adC->prec->suiv = adC->suiv;
    adC->suiv->prec = adC->prec;
    T->HT--;
  }
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enlève du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pré-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2) {
  pAdCarte adC = T1->tete;

  while (adC != NULL && (LaCouleur(adC->elt) != C || LeRang(adC->elt) != R))
  {
    adC = adC->suiv;
  }

  if (adC == NULL)
  {
    printf("The deck \"T1\" doesn't contain the card.");
    exit(1);
  }

  SupprimerCarte(adC, T1);
  AjouterCarteSurTas(adC, T2);
}

/* ******************************************************************************
void PoserTasSurTas(Tas *T1, Tas *T2)
pose le tas T1 sur le tas T2.
Les deux tas doivent avoir le même mode d'étalement.
A l'état final, le tas T1 est vide mais toujours actif, et le tas T2 comporte (de bas en
haut) toutes les cartes qu'il avait au départ puis toutes les cartes de T1 dans l'ordre
qu'elles avaient au départ dans chacun des tas.
Cette opération ne modifie ni la visibilité des cartes, ni la localisation des tas T1 et T2,
ni leur mode d'étalement.
********************************************************************************* */
void PoserTasSurTas(Tas *T1, Tas *T2) {
  if (TasEtale(*T1) != TasEtale(*T2)) {
    printf("Decks must have the same spreading mode.");
    exit(1);
  }
  /* connection des tas */
  if (TasVide(*T2)) {
    T2->tete = T1->tete;
    T2->queue = T1->queue;
  } else {
    T2->queue->suiv = T1->tete;
    T1->tete->prec = T2->queue;
    T2->queue = T1->queue;
  }

  /* vidange de T1 */
  T1->tete = NULL;
  T1->queue = NULL;

  T2->HT += T1->HT;
  T1->HT = 0;
}
