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
/* Ajout buffer de rafraichissement                                  */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include "graphlib_w.h"

typedef struct {
   Window win;
   Pixmap buffer;
   unsigned int largeur, hauteur;
   GC gc;
   Colormap colormap;
   Bool drawing;
   unsigned long background, foreground;
} StructFenetre;

Display *Moniteur = NULL;
int Ecran;

StructFenetre *fenetres[NB_MAX_FENETRES];
unsigned int derniereFenetre;

char *nomsCouleurs[] = {
   "white", "red", "DarkSlateBlue", "DarkSalmon", "yellow", "beige",
   "LightSlateBlue", "orange", "magenta", "DarkCyan", "CadetBlue",
   "black", "blue", "green"
};

static StructFenetre *quelleFenetre(Window win);
static void setColor(char *nom, StructFenetre *fenetre);
static void rafraichirFenetre(StructFenetre *fenetre);
static void open_w(Fenetre *f, int abs, int ord, int larg, int haut,
                   char titre[]);
static void close_w(Fenetre *f);
static char traduction(XKeyEvent *xkey);

/**********************************************************************/
/* gr_inits : initialisation de l'e'cran graphique                    */

void gr_inits(Fenetre *f, int xcorner, int ycorner) {

   gr_inits_2(f, xcorner, ycorner, XSize, YSize);
}

/**********************************************************************/
/* gr_inits_2 : initialisation de l'e'cran graphique                  */
/* cree une fenetre X-Window de taille larg X haut                    */

void gr_inits_2(Fenetre *f, int xcorner, int ycorner,
                            int larg, int haut) {
   char message[] = "Fenetre graphique";

   gr_inits_w(f, xcorner, ycorner, larg, haut, message);
}

/**********************************************************************/
/* gr_inits_w(larg,haut,titre) : initialisation de l'ecran graphique  */
/* cree une fenetre par defaut X-Window de taille larg X haut avec un */
/* titre                                                              */

void gr_inits_w(Fenetre *f, int xcorner, int ycorner,
                            int larg, int haut,
                            char titre[]) {

   open_w(f, xcorner, ycorner, larg, haut, titre);
}

/**********************************************************************/
/* gr_close : fermeture de l'e'cran graphique                         */

void gr_close(Fenetre *f) {

   close_w(f);
   XCloseDisplay(Moniteur);
   Moniteur = NULL;
}

/**********************************************************************/
/* set_blue : changement de couleur                                   */

void set_blue(Fenetre f) {

   setColor("blue", (StructFenetre *)f);
}

/**********************************************************************/
/* set_red : changement de couleur                                    */

void set_red(Fenetre f) {

   setColor("red", (StructFenetre *)f);
}

/**********************************************************************/
/* set_green : changement de couleur                                  */

void set_green(Fenetre f) {

   setColor("green", (StructFenetre *)f);
}

/**********************************************************************/
/* set_yellow : changement de couleur                                 */

void set_yellow(Fenetre f) {

   setColor("yellow", (StructFenetre *)f);
}

/**********************************************************************/
/* set_black : changement de couleur                                  */

void set_black(Fenetre f) {

   setColor("black", (StructFenetre *)f);
}

/**********************************************************************/
/* set_white : changement de couleur                                  */

void set_white(Fenetre f) {

   setColor("white", (StructFenetre *)f);
}

/**********************************************************************/
/* set_color : changement de couleur                                  */

void set_color(Fenetre f, Couleur_glw2 c) {
   
   setColor(nomsCouleurs[c], (StructFenetre *)f);
}

/**********************************************************************/
/* ecriture de texte en blanc sur fond noir                           */

void video_inv(Fenetre f) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XSetBackground(Moniteur, fenetre->gc, BlackPixel(Moniteur, Ecran));
   XSetForeground(Moniteur, fenetre->gc, WhitePixel(Moniteur, Ecran));
}

/**********************************************************************/
/* dessin en blanc sur fond noir                                      */

void graph_inv(Fenetre f) {

   StructFenetre *fenetre = (StructFenetre *)f;

   video_inv(f);
   fenetre->background = BlackPixel(Moniteur, Ecran);
}

/**********************************************************************/
/* ecriture de texte en noir sur fond blanc                           */

void video_nor(Fenetre f) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XSetBackground(Moniteur, fenetre->gc, WhitePixel(Moniteur, Ecran));
   XSetForeground(Moniteur, fenetre->gc, BlackPixel(Moniteur, Ecran));
}

/**********************************************************************/
/* dessin en noir sur fond blanc                                      */

void graph_nor(Fenetre f) {

   StructFenetre *fenetre = (StructFenetre *)f;

   video_nor(f);
   fenetre->background = BlackPixel(Moniteur, Ecran);
}

/**********************************************************************/
/* clear_screen : effacement de l'e'cran                              */

void clear_screen(Fenetre f) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XSetForeground(Moniteur, fenetre->gc, fenetre->background);
   XFillRectangle(Moniteur, (Drawable)(fenetre->buffer), fenetre->gc,
                  0, 0, fenetre->largeur, fenetre->hauteur);
   XSetForeground(Moniteur, fenetre->gc, fenetre->foreground);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* line : trace une ligne                                             */

void line(Fenetre f, int x1, int y1, int x2, int y2) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XDrawLine(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
             x1, y1, x2, y2);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* line_off : efface une ligne                                        */

void line_off(Fenetre f, int x1, int y1, int x2, int y2) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XSetForeground(Moniteur, fenetre->gc, fenetre->background);
   XDrawLine(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
             x1, y1, x2, y2);
   XSetForeground(Moniteur, fenetre->gc, fenetre->foreground);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* point :  affichage du point (x,y)                                  */

void point(Fenetre f, int x, int y) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XDrawPoint(Moniteur, (Drawable)fenetre->buffer, fenetre->gc, x, y);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* point_off : effacement du point (x,y)                              */

void point_off(Fenetre f, int x, int y) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XSetForeground(Moniteur, fenetre->gc, fenetre->background);
   XDrawPoint(Moniteur, (Drawable)fenetre->buffer, fenetre->gc, x, y);
   XSetForeground(Moniteur, fenetre->gc, fenetre->foreground);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* fill_triangle: remplit un triangle                                 */

void fill_triangle(Fenetre f, int x1, int y1, int x2, int y2,
                              int x3, int y3) {

   StructFenetre *fenetre = (StructFenetre *)f;
   XPoint triangle[3];

   triangle[0].x = x1;
   triangle[0].y = y1;
   triangle[1].x = x2;
   triangle[1].y = y2;
   triangle[2].x = x3;
   triangle[2].y = y3;
   XFillPolygon(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
                triangle, 3, Convex, CoordModeOrigin);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* circle : trace un cercle                                           */

void circle(Fenetre f, int x, int y, int R) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XDrawArc(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
            x - R, y - R, 2 * R, 2 * R, 0, 23040);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* fill_circle : remplit un cercle                                    */

void fill_circle(Fenetre f, int x, int y, int R) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XFillArc(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
            x - R, y - R, 2 * R, 2 * R, 0, 23040);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* circle_off : efface un cercle                                      */

void circle_off(Fenetre f, int x, int y, int R) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XSetForeground(Moniteur, fenetre->gc, fenetre->background);
   XDrawArc(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
            x - R, y - R, 2 * R, 2 * R, 0, 23040);
   XSetForeground(Moniteur, fenetre->gc, fenetre->foreground);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* trace d'un rectangle dont les extremites de la diagonale sont      */
/* (x1, y1) et (x2, y2)                                               */

void rectangle(Fenetre f, int x1, int y1, int x2, int y2) {

   StructFenetre *fenetre = (StructFenetre *)f;
   int x0, y0, dx, dy;

   if (x2 >= x1 && y2 >= y1) {
      x0 = x1; y0 = y1; dx = x2 - x1; dy = y2 - y1;
   }
   else if (x2 >= x1 && y2 < y1) {
      x0 = x1; y0 = y2; dx = x2 - x1; dy = y1 - y2;
   }
   else if (x2 < x1 && y2 < y1) {
      x0 = x2; y0 = y2; dx = x1 - x2; dy = y1 - y2;
   }
   else {
      x0 = x2; y0 = y1; dx = x1 - x2; dy = y2 - y1;
   }

   XDrawRectangle(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
                  x0, y0, dx, dy);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* remplit un rectangle dont les extremites de la diagonale sont      */
/* (x1, y1) et (x2, y2)                                               */

void fill_rectangle(Fenetre f, int x1, int y1, int x2, int y2) {

   StructFenetre *fenetre = (StructFenetre *)f;
   int x0, y0, dx, dy;

   if (x2 >= x1 && y2 >= y1) {
      x0 = x1; y0 = y1; dx = x2 - x1; dy = y2 - y1;
   }
   else if (x2 >= x1 && y2 < y1) {
      x0 = x1; y0 = y2; dx = x2 - x1; dy = y1 - y2;
   }
   else if (x2 < x1 && y2 < y1) {
      x0 = x2; y0 = y2; dx = x1 - x2; dy = y1 - y2;
   }
   else {
      x0 = x2; y0 = y1; dx = x1 - x2; dy = y2 - y1;
   }

   XFillRectangle(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
                  x0, y0, dx, dy);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* effacement d'un rectangle dont les extremites de la diagonale sont */
/* (x1, y1) et (x2, y2)                                               */

void rectangle_off(Fenetre f, int x1, int y1, int x2, int y2) {

   StructFenetre *fenetre = (StructFenetre *)f;
   int x0, y0, dx, dy;

   if (x2 >= x1 && y2 >= y1) {
      x0 = x1; y0 = y1; dx = x2 - x1; dy = y2 - y1;
   }
   else if (x2 >= x1 && y2 < y1) {
      x0 = x1; y0 = y2; dx = x2 - x1; dy = y1 - y2;
   }
   else if (x2 < x1 && y2 < y1) {
      x0 = x2; y0 = y2; dx = x1 - x2; dy = y1 - y2;
   }
   else {
      x0 = x2; y0 = y1; dx = x1 - x2; dy = y2 - y1;
   }

   XSetForeground(Moniteur, fenetre->gc, fenetre->background);
   XDrawRectangle(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
                  x0, y0, dx, dy);
   XSetForeground(Moniteur, fenetre->gc, fenetre->foreground);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* ellipse : trace une ellipse de centre (x,y) et de rayons rx et ry  */

void ellipse(Fenetre f, int x, int y, int rx, int ry) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XDrawArc(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
            x - rx, y - ry, 2 * rx, 2 * ry, 0, 23040);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* fill_ellipse : remplit une ellipse de centre (x,y) et de rayons rx */
/* et ry                                                              */

void fill_ellipse(Fenetre f, int x, int y, int rx, int ry) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XFillArc(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
            x - rx, y - ry, 2 * rx, 2 * ry, 0, 23040);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* ellipse_off : efface l'ellipse de centre (x,y) et de rayons rx et  */
/* ry                                                                 */

void ellipse_off(Fenetre f, int x, int y, int rx, int ry) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XSetForeground(Moniteur, fenetre->gc, fenetre->background);
   XDrawArc(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
            x - rx, y - ry, 2 * rx, 2 * ry, 0, 23040);
   XSetForeground(Moniteur, fenetre->gc, fenetre->foreground);
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* write_gr : ecriture sur l'ecran graphique en superposition         */

void write_gr(Fenetre f, int x, int y, char str[]) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XDrawString(Moniteur, (Drawable)fenetre->buffer, fenetre->gc, x, y,
               str, strlen(str));
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* overwrite_gr : e'criture sur l'e'cran graphique avec effacement    */

void overwrite_gr(Fenetre f, int x, int y, char str[]) {

   StructFenetre *fenetre = (StructFenetre *)f;

   XDrawImageString(Moniteur, (Drawable)fenetre->buffer, fenetre->gc,
                    x, y, str, strlen(str));
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* draw_begin : debut d'une sequence de traces graphiques             */

void draw_begin(Fenetre f) {

   StructFenetre *fenetre = (StructFenetre *)f;

   fenetre->drawing = False;
}

/**********************************************************************/
/* draw_end : debut d'une sequence de traces graphiques               */

void draw_end(Fenetre f) {

   StructFenetre *fenetre = (StructFenetre *)f;

   fenetre->drawing = True;
   rafraichirFenetre(fenetre);
}

/**********************************************************************/
/* cliquer : Suspend l'execution du programme jusqu'a un clic de la   */
/* souris                                                             */

void cliquer(Fenetre f) {

   int x, y;

   cliquer_xy(f, &x, &y);
}

/**********************************************************************/
/* cliquer_dans : Suspend l'execution du programme jusqu'a un clic de */
/* la souris                                                          */

void cliquer_dans(Fenetre *f) {

   int x, y;

   cliquer_xy_dans(f, &x, &y);
}

/**********************************************************************/
/* lacher : Suspend l'execution du programme jusqu'a un relachement   */
/* de la souris                                                       */

void lacher(Fenetre f) {

   int x, y;

   lacher_xy(f, &x, &y);
}

/**********************************************************************/
/* lacher_dans : Suspend l'execution du programme jusqu'a un          */
/* relachement de la souris                                           */

void lacher_dans(Fenetre *f) {

   int x, y;

   lacher_xy_dans(f, &x, &y);
}

/**********************************************************************/
/* cliquer_xy : Met a jour les coordonnees x et y avec les            */
/* coordonnees du dernier clic souris                                 */

void cliquer_xy(Fenetre f, int *x, int *y) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != ButtonPress
            || f != (Fenetre)quelleFenetre(evt.xbutton.window));

   *x = evt.xbutton.x ;
   *y = evt.xbutton.y;
}

/**********************************************************************/
/* cliquer_xy_dans : Met a jour les coordonnees x et y avec les       */
/* coordonnees du dernier clic souris                                 */

void cliquer_xy_dans(Fenetre *f, int *x, int *y) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != ButtonPress);

   *f = (Fenetre)quelleFenetre(evt.xbutton.window);
   *x = evt.xbutton.x ;
   *y = evt.xbutton.y;
}

/**********************************************************************/
/* lacher_xy : Met a jour les coordonnees x et y avec les             */
/* coordonnees du dernier relachement souris                          */

void lacher_xy(Fenetre f, int *x, int *y) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != ButtonRelease
            || f != (Fenetre)quelleFenetre(evt.xbutton.window));

   *x = evt.xbutton.x ;
   *y = evt.xbutton.y;
}

/**********************************************************************/
/* lacher_xy_dans : Met a jour les coordonnees x et y avec les        */
/* coordonnees du dernier relachement souris                          */

void lacher_xy_dans(Fenetre *f, int *x, int *y) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != ButtonRelease);

   *f = (Fenetre)quelleFenetre(evt.xbutton.window);
   *x = evt.xbutton.x ;
   *y = evt.xbutton.y;
}

/**********************************************************************/
/* glisser_xy : Met a jour les coordonnees x et y avec les dernieres  */
/* coordonnees de la souris                                           */

void glisser_xy(Fenetre f, int *x, int *y) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != MotionNotify
            || f != (Fenetre)quelleFenetre(evt.xmotion.window));

   *x = evt.xmotion.x ;
   *y = evt.xmotion.y;
}

/**********************************************************************/
/* glisser_xy_dans : Met a jour les coordonnees x et y avec les       */
/* dernieres coordonnees de la souris                                 */

void glisser_xy_dans(Fenetre *f, int *x, int *y) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != MotionNotify);

   *f = (Fenetre)quelleFenetre(evt.xmotion.window);
   *x = evt.xmotion.x ;
   *y = evt.xmotion.y;
}

/**********************************************************************/
/* pour la compatibilite avec Atari                                   */

void wait_kbd(Fenetre f) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != KeyPress
            || f != (Fenetre)quelleFenetre(evt.xkey.window));
}

/**********************************************************************/
/* pour la compatibilite avec Atari                                   */

void wait_kbd_dans(Fenetre *f) {

   XEvent evt;

   do {
      XNextEvent(Moniteur, &evt);
      if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   } while (evt.type != KeyPress);

   *f = (Fenetre)quelleFenetre(evt.xkey.window);
}

/**********************************************************************/
/* cstat teste l'enfoncement d'une touche du clavier                  */

int cstat(Fenetre f) {

   return consilent(f) != '\0';
}

/**********************************************************************/
/* cstat_dans teste l'enfoncement d'une touche du clavier             */

int cstat_dans(Fenetre *f) {

   return consilent_dans(f) != '\0';
}

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

char consilent(Fenetre f) {

   XEvent evt;
		
   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == KeyPress 
          && f == (Fenetre)quelleFenetre(evt.xkey.window)) {
         return traduction(&(evt.xkey));
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return '\0';
}

/**********************************************************************/
/* consilent_dans fournit le caractere present s'il y en a un, le     */
/* caractere nul sinon                                                */
/* (voir consilent)                                                   */

char consilent_dans(Fenetre *f) {

   XEvent evt;
		
   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == KeyPress) {
         *f = (Fenetre)quelleFenetre(evt.xkey.window);
         return traduction(&(evt.xkey));
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return '\0';
}

/**********************************************************************/	
/* bouton fournit le numero de bouton si un bouton de la souris a ete */
/* enfonce, 0 sinon                                                   */

int bouton(Fenetre f) {

   XEvent evt;

   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == ButtonPress
          && f == quelleFenetre(evt.xbutton.window)) {
         return evt.xbutton.button;
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return 0;
}

/**********************************************************************/	
/* bouton_dans fournit le numero de bouton si un bouton de la souris  */
/* a ete enfonce, 0 sinon                                             */

int bouton_dans(Fenetre *f) {

   XEvent evt;

   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == ButtonPress) {
         *f = (Fenetre)quelleFenetre(evt.xbutton.window);
         return evt.xbutton.button;
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return 0;
}

/**********************************************************************/
/* bouton_relache fournit le numero de bouton si un bouton de la      */
/* souris a ete relache, 0 sinon                                      */

int bouton_relache(Fenetre f) {

   XEvent evt;

   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == ButtonRelease
          && f == quelleFenetre(evt.xbutton.window)) {
         return evt.xbutton.button;
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return 0;
}

/**********************************************************************/
/* bouton_relache_dans fournit le numero de bouton si un bouton de la */
/* souris a ete relache, 0 sinon                                      */

int bouton_relache_dans(Fenetre *f) {

   XEvent evt;

   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == ButtonRelease) {
         *f = (Fenetre)quelleFenetre(evt.xbutton.window);
         return evt.xbutton.button;
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return 0;
}

/**********************************************************************/
/* bouton_glisse retourne un numero de bouton (1, 2 ou 3) si la       */
/* souris a ete deplacee l'un des boutons etant appuye, 0 sinon       */

int bouton_glisse(Fenetre f) {
	
   XEvent evt;

   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == MotionNotify
          && f == quelleFenetre(evt.xmotion.window)) {
         if (evt.xmotion.state & Button1Mask) return 1;
         else if (evt.xmotion.state & Button2Mask) return 2;
         else if (evt.xmotion.state & Button3Mask) return 3;
         else if (evt.xmotion.state & Button4Mask) return 4;
         else if (evt.xmotion.state & Button5Mask) return 5;
         else ;
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return 0;
}

/**********************************************************************/
/* bouton_glisse_dans retourne un numero de bouton (1, 2 ou 3) si la  */
/* souris a ete deplacee l'un des boutons etant appuye, 0 sinon       */

int bouton_glisse_dans(Fenetre *f) {
	
   XEvent evt;

   while (XEventsQueued(Moniteur, QueuedAfterFlush) != 0) {
      XNextEvent(Moniteur, &evt);
      if (evt.type == MotionNotify) {
         switch (evt.xmotion.state) {
            case Button1Mask:
               *f = (Fenetre)quelleFenetre(evt.xbutton.window);
               return 1;
            case Button2Mask:
               *f = (Fenetre)quelleFenetre(evt.xbutton.window);
               return 2;
            case Button3Mask: 
               *f = (Fenetre)quelleFenetre(evt.xbutton.window);
               return 3;
            case Button4Mask: 
               *f = (Fenetre)quelleFenetre(evt.xbutton.window);
               return 4;
            case Button5Mask: 
               *f = (Fenetre)quelleFenetre(evt.xbutton.window);
               return 5;
            default:
               break;
         }
      }
      else if (evt.type == Expose) {
         StructFenetre *fenetre = quelleFenetre(evt.xexpose.window);
         rafraichirFenetre(fenetre);
      }
   }
   return 0;
}

/**********************************************************************/
/* quelleFenetre : renvoie un pointeur sur la structure decrivant la  */
/*                 fenetre passee en argument (NULL si la fenetre     */
/*                 n'existe pas)                                      */

static StructFenetre *quelleFenetre(Window win) {
   unsigned int i;

   for (i = 0 ; i != derniereFenetre + 1 ; i++) {
      if (fenetres[i]->win == win) return fenetres[i];
   }
   return NULL;
}

/**********************************************************************/
/* rafraichirFenetre : recopie le contenu du buffer dans la fenetre   */

static void rafraichirFenetre(StructFenetre *fenetre) {

   if (fenetre->drawing) {
      XCopyArea(Moniteur, (Drawable)fenetre->buffer,
                (Drawable)fenetre->win, fenetre->gc,
                0, 0, fenetre->largeur, fenetre->hauteur, 0, 0);
      XFlush(Moniteur);
   }
}

/**********************************************************************/
/*  pour allouer des couleurs                                         */

static void setColor(char *nom, StructFenetre *fenetre) {
   
   XColor xc1, xc2;

   XAllocNamedColor(Moniteur, fenetre->colormap, nom, &xc1, &xc2);
   XSetForeground(Moniteur, fenetre->gc, xc1.pixel);
}

/**********************************************************************/
/* Ouverture d'une fenetre                                            */

static void open_w(Fenetre *f, int abs, int ord, int larg, int haut,
                   char titre[]) {

   StructFenetre *fenetre;
   Window win;
   Pixmap buffer;
   GC gc;
   Colormap colormap;
   unsigned long background, foreground;

   XSizeHints myhint;
   XEvent evt;

   if (Moniteur == NULL) {
      Moniteur = XOpenDisplay(NULL);
      if (Moniteur == NULL) {
         fprintf(stderr, "open_w : erreur XOpenDisplay\n");
         exit(1);
      }
      derniereFenetre = -1;

      Ecran = DefaultScreen(Moniteur);
   }

   if (derniereFenetre == NB_MAX_FENETRES - 1) {
      fprintf(stderr, "open_w : erreur trop de fenetres ouvertes\n");
      exit(1);
   }

   fenetre = (StructFenetre *)malloc(sizeof(StructFenetre));
   if (fenetre == NULL) {
      fprintf(stderr, "open_w : erreur malloc\n");
      exit(1);
   }

   win = XCreateSimpleWindow(Moniteur, RootWindow(Moniteur, Ecran),
	                          abs, ord, larg, haut, 5,
                             BlackPixel(Moniteur, Ecran),
                             WhitePixel(Moniteur, Ecran));

   colormap = DefaultColormap(Moniteur, Ecran);

   myhint.x = abs; myhint.y = ord;
   myhint.width = larg; myhint.height = haut;
   myhint.flags = PPosition | PSize;
   XSetStandardProperties(Moniteur, win, titre, titre, None, NULL, 0,
                          &myhint);

   /* Solicitation des e've'nements en entre'e. Indispensable */
   XSelectInput(Moniteur, win,
                ButtonPressMask | ButtonReleaseMask | KeyPressMask
                | ExposureMask | ButtonMotionMask | PointerMotionMask);

   /* Affichage sur l'e'cran */
   XMapWindow(Moniteur, win);

   do {
      XNextEvent(Moniteur, &evt);
   } while (evt.type != Expose || evt.xexpose.window != win);

   buffer = XCreatePixmap(Moniteur, (Drawable)win, larg, haut,
                          DefaultDepth(Moniteur, Ecran));

   gc = XCreateGC(Moniteur, RootWindow(Moniteur, Ecran), 0, NULL);

   background = WhitePixel(Moniteur, Ecran);
   foreground = BlackPixel(Moniteur, Ecran);

   XSetBackground(Moniteur, gc, background);

   XSetForeground(Moniteur, gc, background);
   XFillRectangle(Moniteur, (Drawable)buffer, gc, 0, 0, larg, haut);
   XSetForeground(Moniteur, gc, foreground);

   XCopyArea(Moniteur, (Drawable)buffer, (Drawable)win, gc, 0, 0,
                        larg, haut, 0, 0);
   XFlush(Moniteur);

   fenetre->win = win;
   fenetre->buffer = buffer;
   fenetre->largeur = larg;
   fenetre->hauteur = haut;
   fenetre->gc = gc;
   fenetre->colormap = colormap;
   fenetre->drawing = True;
   fenetre->background = background;
   fenetre->foreground = foreground;

   derniereFenetre = derniereFenetre + 1;
   fenetres[derniereFenetre] = fenetre;
   *f = (void *)fenetre;
}

/**********************************************************************/
/* Fermeture d'une fenetre                                            */

static void close_w(Fenetre *f) {

   StructFenetre *fenetre = (StructFenetre *)(*f);
   unsigned int noFenetre = 0;

   while (noFenetre != derniereFenetre + 1
          && fenetres[noFenetre] != fenetre) {
      noFenetre++;
   }

   if (noFenetre == derniereFenetre + 1) {
      fprintf(stderr, "close_w : erreur fenetre inexistante\n");
      exit(1);
   }

   XDestroyWindow(Moniteur, fenetre->win);
   XFreePixmap(Moniteur, fenetre->buffer);
   XFreeGC(Moniteur, fenetre->gc);
   XFreeColormap(Moniteur, fenetre->colormap);
   XFlush(Moniteur);

   *f = NULL;
   free((void *)fenetre);

   fenetres[noFenetre] = fenetres[derniereFenetre];
   derniereFenetre = derniereFenetre - 1;
}

/**********************************************************************/
/* Recuperation caractere correspondant a touche frappee              */
/* return | entree -> ascii CR  (0x0D # '\r')                         */
/* backspace       -> ascii BS  (0x08 # '\b')                         */
/* tab             -> ascii HT  (0x09 # '\t')                         */
/* echap           -> ascii ESC (0x1B)                                */
/* suppr/del       -> ascii DEL (0x7F)                                */
/* defil. gauche   -> ascii SOH (0x01)                                */
/* defil. droite   -> ascii STX (0x02)                                */
/* defil. haut     -> ascii ETX (0x03)                                */
/* defil. bas      -> ascii EOT (0x04)                                */

static char traduction(XKeyEvent *xkey) {
   char buffer[1];
   unsigned int nbTraduits;
   KeySym keysym;
   XComposeStatus status;
         
   nbTraduits = XLookupString(xkey, buffer, 1, &keysym, &status);
   switch (keysym) {
      case XK_Left: return 0x01;
      case XK_Right: return 0x02;
      case XK_Up: return 0x03;
      case XK_Down: return 0x04;
      default:
         if (nbTraduits != 0)
            return buffer[0];
         else
            return '\0';
   }
}

/**********************************************************************/
/* Affichage d'une image fond noir dans une fenetre graphique         */

void ajout_image_noire(Fenetre f, XImage Image, int x, int y, int w, int h)
{
  StructFenetre *fenetre = (StructFenetre *)f;

  XPutImage(Moniteur, (Drawable)(fenetre->buffer), fenetre->gc, &Image, 0, 0, x, y, w, h);
}


/**********************************************************************/
/* Affichage d'une image fond rouge dans une fenetre graphique        */

void ajout_image_rouge(Fenetre f, XImage Image, int x, int y, int w, int h)
{
  XColor Rouge;
  GC ZRouge;

  StructFenetre *fenetre = (StructFenetre *)f;

  ZRouge = XCreateGC(Moniteur, (Drawable)(fenetre->buffer), 0, NULL);
  XAllocNamedColor(Moniteur, DefaultColormap(Moniteur, Ecran), "red", &Rouge, &Rouge);
  XSetForeground(Moniteur, ZRouge, Rouge.pixel);
  XSetBackground(Moniteur, ZRouge, WhitePixel(Moniteur, Ecran));

  XPutImage(Moniteur, (Drawable)(fenetre->buffer), ZRouge, &Image, 0, 0, x, y, w, h);
}
