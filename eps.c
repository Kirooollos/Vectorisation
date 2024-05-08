#include "eps.h"
#include "liste_points.h"
#include "liste_contour.h"
#include <stdio.h>

void ecrire_fichier_eps(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin)
{
    FILE *f = fopen(nom_fichier, "w");
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);
    fprintf(f, "0 setlinewidth\n");
    fprintf(f, "0 0 0 setrgbcolor\n");
    fprintf(f, "newpath\n");
    Cellule_Liste_contour *cellule_C_actuelle = LC.first;
    

    while (cellule_C_actuelle !=  NULL){

        Liste_Point LP = cellule_C_actuelle->data;
        Cellule_Liste_Point *CLP = LP.first;
        fprintf(f, "%f %f moveto\n", LP.first->data.x, hauteur - LP.first->data.y);

        for (int i = 0; i < LP.taille; i++)
        {
            fprintf(f, "%f %f lineto\n", CLP->data.x, hauteur - CLP->data.y);
            CLP = CLP->suiv;
        }
        cellule_C_actuelle = cellule_C_actuelle->suiv;
    }

    if (type_dessin==STROKE)
    {
        fprintf(f, "stroke\n");
    }
    else
    {
        fprintf(f, "fill\n");
    }
    fprintf(f, "showpage\n");
    fclose(f);
}
