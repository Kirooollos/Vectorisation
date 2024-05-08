#include <string.h>
#include "contour.h"
#include "liste_points.h"
#include "image.h"

int main(int argc, char **argv)
{
    if (argc < 2){
        printf("ERREUR");
        return 0;
    }
   
    Image I = lire_fichier_image(argv[1]);
    Liste_Contour LC = calculer_contour_s(I);
    // On enlève l'extension .pgm de argv[1] pour ajouter .
    // contour à la fin
    char nom_fichier_contour[strlen(argv[1]) - 4 + 8];
    strcpy(nom_fichier_contour, argv[1]);
    nom_fichier_contour[strlen(argv[1]) - 4] = '\0';
    printf("largeur: %d  , hauteur: %d\n", largeur_image(I),hauteur_image(I));

    ecrire_contours_fichier(LC, strcat(nom_fichier_contour, ".contours"));
    return 0;
}