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
  Couleur c = C;
  if (c < DerniereCouleur) {
    c = (Couleur)((int)c + 1);
  }
  else {
    c = PremiereCouleur;
  }

  return c;
}

/* Rangs
Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as
typedef enum {VideR0, VideR1, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix,
Valet, Dame, Roi, As} Rang;
*/
Rang RangSuivant(Rang R) {
  Rang r = R;
  if (R < DernierRang) {
    r = (Rang)((int)r + 1);
  }
  else {
    r = PremierRang;
  }

  return r;
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
  return C1.RC < C2.RC;
}

booleen MemeRang(Carte C1, Carte C2) {
  return C1.RC == C2.RC;
}

booleen CouleurInferieure(Carte C1, Carte C2) {
  return C1.CC < C2.CC;
}

booleen MemeCouleur(Carte C1, Carte C2) {
  return C1.CC == C2.CC;
}

booleen EstCarteAvant(Carte C1, Carte C2) {
  return C1.RC == C2.RC - 1;
}

/* Representation des tas */

/* Testeurs et selecteurs */

booleen TasActif(Tas T) {
  return T.RT == actif;
}

booleen TasVide(Tas T) {
  return T.HT == 0;
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
  T->RT = inactif;
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
  if (T->HT == 0 && T->RT == actif && T->tete == NULL && T->queue == NULL) {
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
  T->LT = L;
  NbCartes = N; // init variable globale NbCartes

  // Création de la première cellule Carte
  newCarte = (pAdCarte)malloc(sizeof(adCarte));
  if (newCarte == NULL) {
    printf("Memory full...");
    exit(1);
  } else {
    T->tete = newCarte;
    T->tete->elt.CC = couleurCourante;
    T->tete->elt.RC = rangCourant;
    T->tete->elt.VC = Cachee;
    T->tete->suiv = NULL;
    T->tete->prec = NULL;
    T->queue = T->tete; // tete=queue
    T->HT++;
  }

  // remplissage du paquet de carte par ajout en queue
  while (T->HT < N) {
    newCarte = (pAdCarte)malloc(sizeof(adCarte));
    if (newCarte == NULL) {
      printf("Memory full...");
      exit(1);
    } else {
      rangCourant = RangSuivant(rangCourant);
      if (rangCourant == PremierRang) {
        // changement de couleur
        couleurCourante = CouleurSuivante(couleurCourante);
      }

      newCarte->elt.CC = couleurCourante;
      newCarte->elt.RC = rangCourant;
      newCarte->elt.VC = Cachee;
      newCarte->suiv = T->queue->suiv;
      newCarte->prec = T->queue;
      T->queue->suiv = newCarte;
      T->queue = newCarte;
      T->HT++;
    }
  }
}

/* Consultation des cartes d'un tas: ne deplace pas la carte */

/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T) {
}

/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T) {
}

/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Précondition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i) {
}

/* Retournement d'une carte sur un tas */

/* *************************************************************
void RetournerCarteSur(Tas *T)
retourne la carte situ�e au dessus du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSur(Tas *T) {
}

/* *************************************************************
void RetournerCarteSous(Tas *T)
retourne la carte située au dessous du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSous(Tas *T) {
}

/* Modification d'un tas */

/* *************************************************************
void EmpilerTas(Tas *T)
void EtalerTas(Tas *T)
modification du mode d'etalement d'un tas
**************************************************************** */
void EmpilerTas(Tas *T) {
}

void EtalerTas(Tas *T) {
}


/* *************************************************************
void EchangerCartes(int i, int j, Tas *T)
echange les cartes i et j du tas T
Precondition : les deux cartes existent i,j <= LaHauteur(T)
**************************************************************** */
void EchangerCartes(int i, int j, Tas *T) {
}

/* *************************************************************
void BattreTas(Tas *T)
bas le tas T
**************************************************************** */
void BattreTas(Tas *T) {
  InitAlea();


}

/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T) {
}

/* Deplacements de cartes d'un tas sur un autre */


/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (struct adCarte *ac, Tas *T) {
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (struct adCarte *ac, Tas *T) {
}

/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessus de T2
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2) {
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2) {
}

/* ******************************************************************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessous de T1 et la place au dessus de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2) {
}

/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enl�ve la carte situ�e au dessous de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2) {
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enl�ve du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pr�-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2) {
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
}
