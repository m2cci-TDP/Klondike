/* Montée Descente */

#include <stdio.h>

#include "MD.h"
#include "stats.h"

char TexteCouleurMD[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

/* Tableau de jeu : Tas de jeu + Talon + Tas de stockage*/


typedef Tas SerieCouleurMD;
SerieCouleurMD LigneMD[DerniereCouleur + 1];
Tas Tastock[DerniereCouleur + 1];
Tas TalonMD;
/* localisation des tas */
Localisation LocSeriesMD[DerniereCouleur + 1];
Localisation LocSeriesTS[DerniereCouleur + 1];
Localisation LocTalonMD;

/* Formation ducolor tableau de jeu initial */

void SaisirLocTasMD() {
    int i;

    LocTalonMD.NC = 1; /* placer le talon dans la premiere case du tableau */
    LocTalonMD.NL = 1;

    for (i = PremiereCouleur; i <= DerniereCouleur; i++) {
        LocSeriesMD[i].NC = 2 * i + 2; /* placer la série de 4 tas */
        LocSeriesMD[i].NL = 1;
        LocSeriesTS[i].NC = 2 * i + 2; /* placer la série de 4 tas */
        LocSeriesTS[i].NL = 3;
    }
}

void CreerTableauInitialMD() /*creer les le talon + les tas*/ {
    Couleur Co;
    SaisirLocTasMD(); /*placer les 4 tas */

    /* Création du talon avec un jeu de 32 cartes*/
    CreerJeuNeuf(32, LocTalonMD, &TalonMD);
    BattreTas(&TalonMD);
    /* Création des séries vides de chaque couleur  */

    for (Co = PremiereCouleur; Co <= DerniereCouleur; Co++) {
        CreerTasVide(LocSeriesMD[Co], empile, &(LigneMD[Co])); /*creer des emplacements de tas vides*/
        CreerTasVide(LocSeriesTS[Co], empile, &(Tastock[Co])); //Creation des emplacements de tas de stock
    }
}

void ReformerTableauInitialMD() {
    Couleur Co;

    /* On reforme le talon, en empilant les cartes de la ligne et des tas de stockage*/
    if (!TasVide(TalonMD) && EstDecouverte(CarteSur(TalonMD))) {
        RetournerCarteSur(&TalonMD);
    }
    for (Co = PremiereCouleur; Co <= DerniereCouleur; Co++) {
        while (LaHauteur(LigneMD[Co]) != 0) {
            if (EstDecouverte(CarteSur(LigneMD[Co]))) {
                RetournerCarteSur(&LigneMD[Co]);
            }
            DeplacerHautSur(&LigneMD[Co], &TalonMD);

        }
        while (LaHauteur(Tastock[Co]) != 0) {
            if (EstDecouverte(CarteSur(Tastock[Co]))) {
                RetournerCarteSur(&Tastock[Co]);
            }
            DeplacerHautSur(&Tastock[Co], &TalonMD);
        }
    }
    /* RetournerTas(&TalonC4); */
    BattreTas(&TalonMD);
}

/* Visualisation des états du jeu */

void Monter(Tas *T) {
    Couleur Co = LaCouleur(CarteSur(*T));
    DeplacerHautSur(T, &LigneMD[Co]);
}

booleen Descendre(Tas *T) {
    Rang R;
    R = LeRang(CarteSur(*T));
    int i, j;
    j = 0;
    int X;
    int tempo[4];
    for (i = 1; i < 5; i++) {
        if (!TasVide(Tastock[i])) {
            tempo[i - 1] = LeRang(CarteSur(Tastock[i])) - R;
            if (tempo[i - 1] < 0) tempo[i - 1] = 100;
        } else {
            tempo[i - 1] = 10;
        }
    }
    X = tempo[0];
    for (i = 1; i < 4; i++) {
        if (tempo[i] < X) {
            X = tempo[i];
            j = i;
        }
    }
    if (X != 100) {
        DeplacerHautSur(T, &Tastock[j + 1]);
    }
    return X != 100;
}

void AfficherMD() {
    Couleur Co;

    EffacerGraphique();
    AfficherTas(TalonMD, "Talon");

    for (Co = PremiereCouleur; Co <= DerniereCouleur; Co++) {
        AfficherTas(LigneMD[Co], TexteCouleurMD[Co]);
        AfficherTas(Tastock[Co], "");

    }

    AttendreCliquer();
}

booleen MonteStock() {
    int i = 1;
    Couleur Co;
    booleen OK = faux;
    while (i < 5 && !OK) {
        if (TasVide(Tastock[i])) {
            i++;
        } else {
            Co = LaCouleur(CarteSur(Tastock[i]));
            if (TasVide(LigneMD[Co]) || (RangSuivant(LeRang(CarteSur(LigneMD[Co]))) != LeRang(CarteSur(Tastock[i])))) {
                i++;
            } else {
                OK = vrai;
                Monter(&Tastock[i]);
            }
        }
    }
    return OK;


}

booleen JouerUneMD(ModeTrace MT) {
    Couleur Co;
    booleen OK;
    booleen OK2 = vrai;
    if (MT == AvecTrace) {
        AfficherMD();
    }
    while (!TasVide(TalonMD) && OK2) {
        OK = vrai;
        RetournerCarteSur(&TalonMD);
        if (MT == AvecTrace) {
            AfficherMD();
        }
        Co = LaCouleur(CarteSur(TalonMD));
        if ((LeRang(CarteSur(TalonMD)) == PremierRang) || (!TasVide(LigneMD[Co]) && RangSuivant(LeRang(CarteSur(LigneMD[Co]))) == LeRang(CarteSur(TalonMD)))) {
            Monter(&TalonMD);
            if (MT == AvecTrace) {
                AfficherMD();
            }
            while (OK && OK2) {
                OK = MonteStock();
                if (MT == AvecTrace && OK) {
                    AfficherMD();
                }
            }
        } else {
            OK2 = Descendre(&TalonMD);
            if (MT == AvecTrace) {
                AfficherMD();
            }
            while (OK && OK2) {
                OK = MonteStock();
                if (MT == AvecTrace && OK) {
                    AfficherMD();
                }
            }


        }
    }
    if (TasVide(TalonMD)) {
        return vrai;
    } else return faux;
}



void ObserverMD(int NP) {
    int i = 0;

    CreerTableauInitialMD();
    while (i < NP) {
        if (JouerUneMD(AvecTrace)) {
            printf("Vous avez gagné !\n");
        } else {
            printf("Vous avez perdu !\n");
        }
        ReformerTableauInitialMD();
        i++;
    }
}

void AnalyserMD(int NP) {
    int i = 0;
    pStatsKlondike stats = initStats();

    CreerTableauInitialMD();
    while (i < NP) {
        addStats(&stats, JouerUneMD(SansTrace));
        ReformerTableauInitialMD();
        i++;
    }

    pctStats(stats);
    freeStats(&stats);
}
