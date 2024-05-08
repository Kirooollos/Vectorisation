#include "eps.h"
#include "contour.h"
#include "image.h"
#include <string.h>

int main(int argc, char **argv)
{
    Image I = lire_fichier_image(argv[1]);
    Liste_Contour LC = calculer_contour_s(I);

    char nom_fichier_eps[strlen(argv[1])+7];
    strcpy(nom_fichier_eps, argv[1]);
    nom_fichier_eps[strlen(argv[1]) - 4] = '\0';
    Type_dessin type_dessin = STROKE;
    if (strcmp(argv[2], "fill") == 0)
    {
        type_dessin = FILL;
        strcat(nom_fichier_eps, "_fill");
    }
    else if (strcmp(argv[2], "stroke")==0)
    {
        type_dessin = STROKE;
        strcat(nom_fichier_eps, "_stroke");
    }
    ecrire_fichier_eps(LC, largeur_image(I), hauteur_image(I), strcat(nom_fichier_eps, ".eps"), type_dessin);
}
