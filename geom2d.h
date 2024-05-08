#ifndef _GEOM_2D_H_
#define _GEOM_2D_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct Vecteur_{
    double x,y;            /*coordonnees*/
}Vecteur;

typedef struct Point_{
    double x,y;     /*coordonnees*/
}Point;


// definition du type courbe bezier de degre 2 (definit comme 3 points)
typedef struct Bezier2{
    Point C0, C1, C2;
}Bezier2;

//definition du type courbe bezier de degre 3
typedef struct Bezier3{
    Point C0, C1, C2, C3;
} Bezier3;

// cree le point de coordonnées(x,y)
Point set_point(double x, double y);

//somme P1+P2
Point add_point(Point P1,Point P2);

//vecteur correspondant au bipoint−→AB
Vecteur vect_bipoint(Point A,Point B);

//retourne la norme du vecteur V
double norme_vect(Vecteur V);

//retourne le vecteur multiplier par le scalaire a 
Vecteur mult_scalaire (Vecteur V, double a);

// retoutne la distance entre les 2 points A et B
double distance_points(Point A, Point B);

Point mult_scalaire_point(Point A, double k);

double produit_scalaire(Vecteur V1, Vecteur V2);

bool est_egal_points(Point A, Point B);

double distance_point_segment(Point P, Point A, Point B);

Point Bezier_degre_2(Bezier2 B, double t);

Point Bezier_degre_3(Bezier3 B,double t);

double distance_point_bezier2(Point A, Bezier2 B, double t);

double distance_point_bezier3(Point A, Bezier3 B, double t);

Bezier3 conversion_en_bezier_3(Bezier2 B2);

#endif
