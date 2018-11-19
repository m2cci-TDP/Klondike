/*********************************************************************/
/* Bibliotheque graphique graphlib pour l'enseignement universitaire */
/* D'apres les idees de Francoise et Jean-Paul Bertrandias sur Atari */
/* Implementation sous X Windows: Michel Bonin et Xavier Girod       */
/* UFR IMA - Universite Joseph Fourier (Grenoble)                    */
/* Centre Joseph Fourier Drome-Ardeche (Valence)                     */
/* email: Michel.Bonin@ujf-grenoble.fr                               */
/*                                                                   */
/* 11/05/2005 (P. Habraken) :                                        */
/* Remise a plat et simplification...                                */
/*********************************************************************/

#ifndef GRAPHLIB_W2_H
#define GRAPHLIB_W2_H

#include <X11/Xlib.h>

#define XSize  999
#define YSize  749

#define NB_MAX_FENETRES 256

typedef void *Fenetre;

typedef enum {
   BLANC = 0, ROUGE, BLEU_FONCE, SAUMON_FONCE, JAUNE, BEIGE, BLEU_CLAIR,
   ORANGE, MAGENTA, CYAN_FONCE, BLEU_VERT, NOIR, BLEU, VERT
} Couleur_glw2;

/**********************************************************************/
/* gr_inits : initialisation de l'e'cran graphique                    */
void gr_inits(Fenetre *f, int xcorner, int ycorner);

/**********************************************************************/
/* gr_inits_2 : initialisation de l'e'cran graphique                  */
/* cree une fenetre X-Window de taille larg X haut                    */

void gr_inits_2(Fenetre *f, int xcorner, int ycorner,
                            int larg, int haut);

/**********************************************************************/
/* gr_inits_w : initialisation de l'e'cran graphique                  */
/* cree une fenetre X-Window de taille larg x haut avec un titre      */

void gr_inits_w(Fenetre *f, int xcorner, int ycorner,
                            int larg, int haut,
                            char titre[]);

/**********************************************************************/
/* gr_close : fermeture de l'e'cran graphique                         */

void gr_close(Fenetre *f);

/**********************************************************************/
/* set_blue : changement de couleur                                   */

void set_blue(Fenetre f);

/**********************************************************************/
/* set_red : changement de couleur                                    */

void set_red(Fenetre f);

/**********************************************************************/
/* set_green : changement de couleur                                  */

void set_green(Fenetre f);

/**********************************************************************/
/* set_yellow : changement de couleur                                 */

void set_yellow(Fenetre f);

/**********************************************************************/
/* set_black : changement de couleur                                  */

void set_black(Fenetre f);

/**********************************************************************/
/* set_white : changement de couleur                                  */

void set_white(Fenetre f);

/**********************************************************************/
/* set_color : changement de couleur                                  */

void set_color(Fenetre f, Couleur_glw2 c);

/**********************************************************************/
/* ecriture de texte en blanc sur fond noir                           */

void video_inv(Fenetre f);

/**********************************************************************/
/* dessin en blanc sur fond noir                                      */

void graph_inv(Fenetre f);

/**********************************************************************/
/* ecriture de texte en noir sur fond blanc                           */

void video_nor(Fenetre f);

/**********************************************************************/
/* dessin en noir sur fond blanc                                      */

void graph_nor(Fenetre f);

/**********************************************************************/
/* clear_screen : effacement de l'e'cran                              */

void clear_screen(Fenetre f);

/**********************************************************************/
/* line : trace une ligne                                             */

void line(Fenetre f, int x1, int y1, int x2, int y2);

/**********************************************************************/
/* line_off : efface une ligne                                        */

void line_off(Fenetre f, int x1, int y1, int x2, int y2);

/**********************************************************************/
/* point :  affichage du point (x,y)                                  */

void point(Fenetre f, int x, int y);

/**********************************************************************/
/* point_off : effacement du point (x,y)                              */

void point_off(Fenetre f, int x, int y);

/**********************************************************************/
/* fill_triangle: remplit un triangle                                 */

void fill_triangle(Fenetre f, int x1, int y1, int x2, int y2,
                              int x3, int y3);

/**********************************************************************/
/* circle : trace un cercle                                           */

void circle(Fenetre f, int x, int y, int R);

/**********************************************************************/
/* fill_circle : remplit un cercle                                    */

void fill_circle(Fenetre f, int x, int y, int R);

/**********************************************************************/
/* circle_off : efface un cercle                                      */

void circle_off(Fenetre f, int x, int y, int R);

/**********************************************************************/
/* trace d'un rectangle dont les extremites de la diagonale sont      */
/* (x1, y1) et (x2, y2)                                               */

void rectangle(Fenetre f, int x1, int y1, int x2, int y2);

/**********************************************************************/
/* remplit un rectangle dont les extremites de la diagonale sont      */
/* (x1, y1) et (x2, y2)                                               */

void fill_rectangle(Fenetre f, int x1, int y1, int x2, int y2);

/**********************************************************************/
/* effacement d'un rectangle dont les extremites de la diagonale sont */
/* (x1, y1) et (x2, y2)                                               */

void rectangle_off(Fenetre f, int x1, int y1, int x2, int y2);

/**********************************************************************/
/* ellipse : trace une ellipse de centre (x,y) et de rayons rx et ry  */

void ellipse(Fenetre f, int x, int y, int rx, int ry);

/**********************************************************************/
/* fill_ellipse : remplit une ellipse de centre (x,y) et de rayons rx */
/* et ry                                                              */

void fill_ellipse(Fenetre f, int x, int y, int rx, int ry);

/**********************************************************************/
/* ellipse_off : efface l'ellipse de centre (x,y) et de rayons rx et  */
/* ry                                                                 */

void ellipse_off(Fenetre f, int x, int y, int rx, int ry);

/**********************************************************************/
/* write_gr : ecriture sur l'ecran graphique en superposition         */

void write_gr(Fenetre f, int x, int y, char str[]);

/**********************************************************************/
/* overwrite_gr : e'criture sur l'e'cran graphique avec effacement    */

void overwrite_gr(Fenetre f, int x, int y, char str[]);

/**********************************************************************/
/* draw_begin : debut d'une sequence de traces graphiques             */

void draw_begin(Fenetre f);

/**********************************************************************/
/* draw_end : fin d'une sequence de traces graphiquesi                */

void draw_end(Fenetre f);

/**********************************************************************/
/* cliquer : Suspend l'execution du programme jusqu'a un clic de la   */
/* souris                                                             */
void cliquer(Fenetre f);

/**********************************************************************/
/* cliquer_dans : Suspend l'execution du programme jusqu'a un clic de */
/* la souris                                                          */

void cliquer_dans(Fenetre *f);

/**********************************************************************/
/* lacher : Suspend l'execution du programme jusqu'a un relachement   */
/* de la souris                                                       */

void lacher(Fenetre f);

/**********************************************************************/
/* lacher_dans : Suspend l'execution du programme jusqu'a un          */
/* relachement de la souris                                           */

void lacher_dans(Fenetre *f);

/**********************************************************************/
/* cliquer_xy : Met a jour les coordonnees x et y avec les            */
/* coordonnees du dernier clic souris                                 */

void cliquer_xy(Fenetre f, int *x, int *y);

/**********************************************************************/
/* cliquer_xy_dans : Met a jour les coordonnees x et y avec les       */
/* coordonnees du dernier clic souris                                 */

void cliquer_xy_dans(Fenetre *f, int *x, int *y);

/**********************************************************************/
/* lacher_xy : Met a jour les coordonnees x et y avec les             */
/* coordonnees du dernier relachement souris                          */

void lacher_xy(Fenetre f, int *x, int *y);

/**********************************************************************/
/* lacher_xy_dans : Met a jour les coordonnees x et y avec les        */
/* coordonnees du dernier relachement souris                          */

void lacher_xy_dans(Fenetre *f, int *x, int *y);

/**********************************************************************/
/* glisser_xy : Met a jour les coordonnees x et y avec les dernieres  */
/* coordonnees de la souris                                           */

void glisser_xy(Fenetre f, int *x, int *y);

/**********************************************************************/
/* glisser_xy_dans : Met a jour les coordonnees x et y avec les       */
/* dernieres coordonnees de la souris                                 */

void glisser_xy_dans(Fenetre *f, int *x, int *y);

/**********************************************************************/
/* pour la compatibilite avec Atari                                   */

void wait_kbd(Fenetre f);

/**********************************************************************/
/* pour la compatibilite avec Atari                                   */

void wait_kbd_dans(Fenetre *f);

/**********************************************************************/
/* cstat teste l'enfoncement d'une touche du clavier                  */

int cstat(Fenetre f);

/**********************************************************************/
/* cstat_dans teste l'enfoncement d'une touche du clavier             */

int cstat_dans(Fenetre *f);

/**********************************************************************/
/* consilent fournit le caractere present s'il y en a un, le          */
/* caractere nul sinon                                                */
/* return | entree -> ascii CR  (0x0D # '\r')                         */
/* backspace       -> ascii BS  (0x08 # '\b')                         */
/* tab             -> ascii HT  (0x09 # '\t')                         */
/* echap           -> ascii ESC (0x1B)                                */
/* suppr/del       -> ascii DEL (0x7F)                                */
/* defil. gauche   -> ascii SOH (0x01)                                */
/* defil. droite   -> ascii STX (0x02)                                */
/* defil. haut     -> ascii ETX (0x03)                                */
/* defil. bas      -> ascii EOT (0x04)                                */

char consilent(Fenetre f);

/**********************************************************************/
/* consilent_dans fournit le caractere present s'il y en a un, le     */
/* caractere nul sinon                                                */
/* (voir consilent)                                                   */

char consilent_dans(Fenetre *f);

/**********************************************************************/	
/* bouton fournit le numero de bouton si un bouton de la souris a ete */
/* enfonce, 0 sinon                                                   */

int bouton(Fenetre f);

/**********************************************************************/	
/* bouton_dans fournit le numero de bouton si un bouton de la souris  */
/* a ete enfonce, 0 sinon                                             */

int bouton_dans(Fenetre *f);

/**********************************************************************/
/* bouton_relache fournit le numero de bouton si un bouton de la      */
/* souris a ete relache, 0 sinon                                      */

int bouton_relache(Fenetre f);

/**********************************************************************/
/* bouton_relache_dans fournit le numero de bouton si un bouton de la */
/* souris a ete relache, 0 sinon                                      */

int bouton_relache_dans(Fenetre *f);

/**********************************************************************/
/* bouton_glisse retourne un numero de bouton (1, 2 ou 3) si la       */
/* souris a ete deplacee l'un des boutons etant appuye, 0 sinon       */

int bouton_glisse(Fenetre f);

/**********************************************************************/
/* bouton_glisse_dans retourne un numero de bouton (1, 2 ou 3) si la  */
/* souris a ete deplacee l'un des boutons etant appuye, 0 sinon       */

int bouton_glisse_dans(Fenetre *f);


/**********************************************************************/
/* Affichage d'une image fond noir dans une fenetre graphique         */

void ajout_image_noire(Fenetre f, XImage Image, int x, int y, int w, int h);

/**********************************************************************/
/* Affichage d'une image fond rouge dans une fenetre graphique        */

void ajout_image_rouge(Fenetre f, XImage Image, int x, int y, int w, int h);


#endif /* GRAPHLIB_W2_H */
