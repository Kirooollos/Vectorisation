#ifndef LISTE_CONTOUR_H
#define LISTE_CONTOUR_H
#include "liste_points.h"


/*---- le type cellule de liste de contour ----*/
typedef struct Cellule_Liste_contour_
{
	Contour data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_contour;


/*---- le type liste de point ----*/
typedef struct Liste_Contour_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_contour *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_contour *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour;

/*---- le type tableau de contours ----*/
typedef struct Tableau_Contour_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Contour *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Contour;

Cellule_Liste_contour *creer_element_liste_Contour(Liste_Point v);

Liste_Contour creer_liste_Contour(void);

Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Liste_Point v);

Liste_Contour supprimer_liste_Contour(Liste_Contour L);

Liste_Contour concatener_liste_Contour(Liste_Contour L1, Liste_Contour L2);

Tableau_Contour sequence_contours_liste_vers_tableau(Liste_Contour L);

void ecrire_contours_fichier(Liste_Contour L, char *nom_fichier);


#endif