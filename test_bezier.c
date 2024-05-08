#include "simplification.h"
#include "eps.h"
#include "contour.h"
#include "liste_contour.h"
#include "liste_points.h"
#include "image.h"
#include "bezier.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Vérification du nombre d'arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <image.pbm> <distance d> <degre courbe de Bezier>\n", argv[0]);
        return 1;
    }

    //Arguments
    Image I = lire_fichier_image(argv[1]);
    double d = atof(argv[2]);
    int deg = atoi(argv[3]);

    Liste_Contour L_C = calculer_contour_s(I);
    Liste_Contour L_C_simplifie = creer_liste_Contour();
    Cellule_Liste_contour *Cell = L_C.first;
    while(Cell !=  NULL){
        Contour C = Cell->data;
        Contour C_simplifie;

        // Verification des degres
        if (deg==1){
            C_simplifie = simplification_douglas_peucker_segments(C, 0, C.taille - 1, d);
        }
        else if (deg==2){
            C_simplifie = simplification_douglas_peucker_bezier2(C, 0, C.taille - 1, d);
        }
        else if(deg==3){
            C_simplifie = simplification_douglas_peucker_bezier3(C, 0, C.taille - 1, d);
        }
        L_C_simplifie = ajouter_element_liste_Contour(L_C_simplifie, C_simplifie);
        Cell = Cell->suiv;
    }

    //creation fichier contour
    char nom_fichier[300];              //nom du fichier
    strcpy(nom_fichier, argv[1]);
    nom_fichier[strlen(argv[1]) - 4] = '\0';  // enelever l'extension.pbm
    char suffixe_a_ajouter[100];
    // ajouter un suffixe selon le type de simplification
    if (deg == 1)
    {
        strcpy(suffixe_a_ajouter, "_segments_d=");
    }
    else if (deg == 2)
    {
        strcpy(suffixe_a_ajouter, "_beziers2_d=");
    }
    else if (deg == 3)
    {
        strcpy(suffixe_a_ajouter, "_beziers3_d=");
    }
    strcat(nom_fichier, suffixe_a_ajouter);
    strcat(nom_fichier, argv[2]);       //ajouter distance-seuil d
    ecrire_contours_fichier(L_C_simplifie, strcat(nom_fichier, ".contours"));
    Type_dessin type = FILL;
    ecrire_fichier_eps(L_C_simplifie, largeur_image(I), hauteur_image(I), strcat(nom_fichier, ".eps"), type);

    //Affichage nombre de contours et nombre total de segments
    
    printf("Nombre de contours : %d\n", L_C_simplifie.taille);

    if (deg == 1)
    {
        int nb_segments = 0;
        Cell = L_C_simplifie.first;
        while (Cell != NULL)
        {
            Contour C = Cell->data;
            nb_segments += ((C.taille - 1) / 2) + 1;
            Cell = Cell->suiv;
        }
        printf("Nombre de segments : %d\n", nb_segments);
    }
    else if (deg == 2)
    {
        int nb_courbes = 0;
        Cell = L_C_simplifie.first;
        while (Cell != NULL)
        {
            Contour C = Cell->data;
            nb_courbes += ((C.taille - 1) / 3) + 1;
            Cell = Cell->suiv;
        }
        printf("Nombre de courbes : %d\n", nb_courbes);
    }
    else if (deg == 3)
    {
        int nb_courbes = 0;
        Cell = L_C_simplifie.first;
        while (Cell != NULL)
        {
            Contour C = Cell->data;
            nb_courbes += ((C.taille - 1) / 4) + 1;
            Cell = Cell->suiv;
        }
        printf("Nombre de courbes : %d\n", nb_courbes);
    }
    return 0;
}


