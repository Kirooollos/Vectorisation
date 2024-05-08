#include <stdio.h>
#include <stdlib.h>
#include "geom2d.h"

int main(int argc , char **  argv){
    // Point A,B,C;
    // Vecteur X, Y,Z;
    // A=set_point(2.0,-2.0);
    // B=set_point(3.0,1.0);

    
    // C = add_point(A, B);
    // afficher_point(C);

    // X=vect_bipoint(C,A);
    // afficher_vecteur(X);

    // double n=norme_vect(X);

    // Y = mult_scalaire(X, 12.37);
    // afficher_vecteur(Y);
    // double d = distance_points(A,B);
    // printf("d = %f\n", Y.y, d);

    // Z= somme_deux_vecteurs(X, Y);
    // afficher_vecteur(Z);

    // double ps= produit_scalaire(X, Y);
    // printf("le produit scalaire est : %f\n", ps);




    //test de la fonction distance_point_segment
    double P_x, P_y, B_x, B_y, A_x, A_y;
    Point P,A,B;
    printf("Entrer la coordonnée x de P : \n");
    scanf(" %lf", &P_x);
    printf("Entrer la coordonnée y de P : \n");
    scanf(" %lf", &P_y);
    printf("Entrer la coordonnée x de A : \n");
    scanf(" %lf", &A_x);
    printf("Entrer la coordonnée y de A : \n");
    scanf(" %lf", &A_y);
    printf("Entrer la coordonnée x de B : \n");
    scanf(" %lf", &B_x);
    printf("Entrer la coordonnée y de B : \n");
    scanf(" %lf", &B_y);
    P = set_point(P_x,P_y);
    A = set_point(A_x, A_y);
    B = set_point(B_x, B_y);
    
    double d = distance_point_segment(P,A,B);
    printf("La distance entre P et AB est : %f\n", d);
    return 0;
}


