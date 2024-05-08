#ifndef LISTE_POINT_H
#define LISTE_POINT_H

#include "geom2d.h"
 
/*---- le   type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
    Point data;                        /* donn�e de l'�l�ment de liste */
    struct Cellule_Liste_Point_ *suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Point;
  
/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
    unsigned int taille;        /* nombre d'�l�ments dans la liste */
    Cellule_Liste_Point *first; /* pointeur sur le premier �l�ment de la liste */
    Cellule_Liste_Point *last;  /* pointeur sur le dernier �l�ment de la liste */
                                /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
    unsigned int taille; /* nombre d'�l�ments dans le tableau */
    Point *tab;          /* (pointeur vers) le tableau des �l�ments */
} Tableau_Point;

Cellule_Liste_Point *creer_element_liste_Point(Point v);

Liste_Point creer_liste_Point_vide();

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

void ecrire_contour(Liste_Point L);

void ecrire_contour_fichier(Liste_Point L, char *nom_fichier);

#endif
