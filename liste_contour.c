#include <stdio.h>
#include <stdlib.h>
#include "liste_contour.h"



/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_contour *creer_element_liste_Contour(Liste_Point v){
    Cellule_Liste_contour *el;
	el = (Cellule_Liste_contour *)malloc(sizeof(Cellule_Liste_contour));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_contour : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* creer une liste vide */
Liste_Contour creer_liste_Contour()
{
	Liste_Contour L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Liste_Point v){
    Cellule_Liste_contour *el;
	
	el = creer_element_liste_Contour(v);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Contour supprimer_liste_Contour(Liste_Contour L){
    Cellule_Liste_contour *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_contour *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Contour concatener_liste_Contour(Liste_Contour L1, Liste_Contour L2){
    /* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}



/* creer une sequence de contours sous forme d'un tableau de contours 
   a partir de la liste de contours L */
Tableau_Contour sequence_contours_liste_vers_tableau(Liste_Contour L){
    Tableau_Contour T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_contours_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_contour *el = L.first; /* pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}

int nb_contours(Liste_Contour L){
    return L.taille;
}

void ecrire_contours_fichier(Liste_Contour L, char *nom_fichier){
    int taille = nb_contours(L);
    FILE *f = fopen(nom_fichier, "w");
    Cellule_Liste_contour *clc =L.first ;
    fprintf(f,"nombre de contours= %d\n", taille);
    int segments = 0;
    for (int i = 0; i < taille; i++)
    {

        Tableau_Point TP = sequence_points_liste_vers_tableau(clc->data);
	    int nP = TP.taille;
        if(f!=NULL){
            segments += nP;
            fprintf(f, "Contour avec %d segments\n[", nP - 1);
            for (int k = 0; k < nP; k++)
	        {	
		    Point P = TP.tab[k]; /* recuperer le point d'indice k */
		    fprintf(f," (%5.1f,%5.1f)", P.x, P.y);
            }
            fprintf(f,"]\n");
        
        }else{
            printf("Impossible d'ouvrir le fichier %s\n", nom_fichier);
        }
         clc = clc->suiv;
    }
	segments = segments - taille;
	fprintf(f, "Nombre total de segments:%d\n", segments);
	fclose(f);
}