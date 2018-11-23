/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005,
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#ifndef _TAS_H
#define _TAS_H

#include "TypesConst.h"

#define NB_BAT 1000

/*-----------------------------------*/
/* Specifications des objets de base */
/*-----------------------------------*/

/* Couleurs */
/* Ordre croissant sur les couleurs: trefle, carreau, coeur, pique */

Couleur CouleurSuivante(Couleur C);

/* Rangs */
/* Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as */

Rang RangSuivant(Rang R);

/*--------------------------------------------------------------------*/
/* Representation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Representation des cartes */

	/* Testeurs et selecteurs */

Rang LeRang(Carte C);

Couleur LaCouleur(Carte C);

Visibilite EstCachee(Carte C);

Visibilite EstDecouverte(Carte C);

	/* Comparaison de cartes */

booleen RangInferieur(Carte C1, Carte C2);

booleen MemeRang(Carte C1, Carte C2);

booleen CouleurInferieure(Carte C1, Carte C2);

booleen MemeCouleur(Carte C1, Carte C2);

booleen EstCarteAvant(Carte C1, Carte C2);

/* Representation des tas */

	/* Testeurs et selecteurs */

booleen TasActif(Tas T);

booleen TasVide(Tas T);

booleen TasEmpile(Tas T);

booleen TasEtale(Tas T);

int LaHauteur(Tas T);

Localisation LaPlace(Tas T);

	/* Constructeurs */

void CreerTasVide(Localisation L, Mode M, Tas *T);

void SupprimerTasVide(Tas *T);

void CreerJeuNeuf(int N, Localisation L, Tas *T);

void LibererTasPlein(Tas*);

	/* Consultation des cartes d'un tas: ne deplace pas la carte */

Carte CarteSur(Tas T);

Carte CarteSous(Tas T);

Carte IemeCarte(Tas T, int i);

	/* Retournement d'une carte sur un tas */

void RetournerCarteSur(Tas *T);

void RetournerCarteSous(Tas *T);

	/* Modification d'un tas */

void EmpilerTas(Tas *T);

void EtalerTas(Tas *T);

void EchangerCartes(int i, int j, Tas *T);

void BattreTas(Tas *T);

void RetournerTas(Tas *T);

	/* Deplacements de cartes d'un tas sur un autre */

void AjouterCarteSurTas (pAdCarte ac, Tas *T);

void AjouterCarteSousTas (pAdCarte ac, Tas *T);

void DeplacerHautSur(Tas *T1, Tas *T2);

void DeplacerHautSous(Tas *T1, Tas *T2);

void DeplacerBasSur(Tas *T1, Tas *T2);

void DeplacerBasSous(Tas *T1, Tas *T2);

void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2);

void PoserTasSurTas(Tas *T1, Tas *T2);

/* fonctions additionnelles */
void SupprimerCarte(pAdCarte, Tas*);
void SupprimerCarteSous (Tas*);
void SupprimerCarteSur (Tas*);
void DecouvrirCartesTas(Tas*);
void AjouterCarteSurTasVide (pAdCarte, Tas*);
pAdCarte pIemeCarte(Tas, int);
void AjouterCarteApres (pAdCarte, pAdCarte, Tas*);

#endif
