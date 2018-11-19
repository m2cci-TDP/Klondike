/*--------------------------------------------------------------*/
/* R�ussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apr�s les algorithmes de Pierre-Claude Scholl              
   modifie par F. Carrier, juillet 2012
   --> types enumeres : Couleur, Rang
   --> tas representes par des listes chainees
----------------------------------------------------------------*/

/*-----------------------------------------*/
/* D�finitions des constantes et des types */
/*-----------------------------------------*/

typedef int booleen;

#define vrai 1
#define faux 0

/* Couleurs */
/* Ordre croissant sur les couleurs: tr�fle, carreau, coeur, pique */

typedef enum {VideC, Trefle, Carreau, Coeur, Pique} Couleur;

#define PremiereCouleur Trefle
#define DerniereCouleur Pique

/* Rangs */
/* Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as */

typedef enum {VideR0, VideR1, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix,
               Valet, Dame, Roi, As} Rang;

Rang PremierRang;	
/* Deux pour un jeu de 52 cartes, Sept pour un jeu de 32 cartes 
   A intialiser suivant la reussite */
#define DernierRang As

/* Tas de cartes */

typedef enum {actif, inactif} Role;
  /* un tas actif joue un role, il a un mode d'empilement et une localisation */
  /* un tas inactif n'est pas visualise */

typedef enum {empile, etale} Mode;

typedef struct {
  int NL;  /* ligne */
  int NC;  /* colonne */
} Localisation;
	
int NbCartes;	/* entier �gal � 32 ou 52 */
#define HmTas 52

/*--------------------------------------------------------------------*/
/* Repr�sentation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Repr�sentation des cartes */

typedef booleen Visibilite;
#define Cachee faux
#define Decouverte vrai

typedef struct {
  Couleur CC;
  Rang RC;
  Visibilite VC;
} ValeurCarte;

typedef ValeurCarte Carte;

/* Repr�sentation des tas */

/* Type struct adCarte pour representer une liste de Cartes doublement chainee */
struct adCarte {
   Carte elt;
   struct adCarte *suiv;
   struct adCarte *prec;
};

typedef struct {
  Localisation LT;
  Role RT;
  Mode MT;
  /* modif F. Carrier : juillet 2012 */
  /* liste de cartes */
  int HT;	          /* hauteur du tas, entier entre 0 et HmTas */
  struct adCarte *tete; /* Liste Cartes */
  struct adCarte *queue; /* Liste Cartes */
    /* la premiere carte (tete) est celle du dessous, la derniere (queue) celle du dessus */
} Tas;

/* Mode de Trace des Reussites */

typedef enum {SansTrace, AvecTrace} ModeTrace;

