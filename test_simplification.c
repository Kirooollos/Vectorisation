
#include "simplification.h"
#include "eps.h"
#include "contour.h"
#include "image.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <image.pbm> <distance d>\n", argv[0]);
        return 1;
    }
    Image I = lire_fichier_image(argv[1]);
    double d = atof(argv[2]);

  Liste_Contour LC_simplifiee = simplification_contours(I, d);
   
    // creation fichier contour
    char nom_fichier[300];
    strcpy(nom_fichier, argv[1]);
    nom_fichier[strlen(argv[1]) - 4] = '\0';
    strcat(nom_fichier, "_sdp_segments_d=");
    strcat(nom_fichier, argv[2]);
    ecrire_contours_fichier(LC_simplifiee, strcat(nom_fichier, ".contours"));

    //Creation fichier eps 
    char nom_fichier_eps[300];
    strcpy(nom_fichier_eps, argv[1]);
    nom_fichier_eps[strlen(argv[1]) - 4] = '\0';
    strcat(nom_fichier_eps, "_sdp_segments_d=");
    strcat(nom_fichier_eps, argv[2]);
    Type_dessin type = FILL;
    ecrire_fichier_eps(LC_simplifiee, largeur_image(I), hauteur_image(I), strcat(nom_fichier_eps, ".eps"), type);

    //Affichage nombre de contours et nombre total de segments
    printf("Nombre de contours : %d\n", LC_simplifiee.taille);
    int nb_segments = 0;
    Cellule_Liste_contour *Cell = LC_simplifiee.first;
    while (Cell != NULL)
    {
        Contour C = Cell->data;
        nb_segments += ((C.taille -1) / 2) + 1;
        Cell = Cell->suiv;
    }
    printf("Nombre de segments : %d\n", nb_segments);
    return 0;

}