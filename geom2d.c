
#include "geom2d.h"
#include <stdbool.h>
#include "math.h"

Point set_point(double x,double y){
    Point P={x,y};
    return P;
}

Point add_point(Point P1,Point P2){
    return set_point(P1.x + P2.x, P1.y + P2.y);
}

Vecteur vect_bipoint(Point A,Point B){           
    Vecteur V = {B.x - A.x, B.y - A.y};
    return V;

}

double norme_vect(Vecteur V){
    return sqrt(V.x*V.x + V.y*V.y);
}

Vecteur mult_scalaire (Vecteur V, double a)
{
    V.x = V.x * a;
    V.y = V.y * a;
    return V;
}

double distance_points(Point A, Point B)
{
    return norme_vect(vect_bipoint(A,B));
}

double produit_scalaire(Vecteur V1, Vecteur V2){
    return V1.x * V2.x + V1.y * V2.y;
}

bool est_egal_points(Point A, Point B)
{
    return (A.x == B.x && A.y == B.y);
}

Point mult_scalaire_point (Point A, double k)
{
    A.x = A.x * k;
    A.y = A.y * k;
    return A;
}

double distance_point_segment(Point P,Point A, Point B){
    if (est_egal_points(A, B))
    {
        return distance_points(P, A);
    }
    Vecteur AB = vect_bipoint(A, B);
    Vecteur AP = vect_bipoint(A, P);

    double l = (produit_scalaire(AB, AP)) / produit_scalaire(AB, AB);
    if (l < 0)
    {
        return distance_points(P, A);
    }
    else if (l > 1)
    {
        return distance_points(P, B);
    }
    else
    {
        Point Q = add_point(A, mult_scalaire_point(add_point(B, mult_scalaire_point(A, -1)), l));
        return distance_points(P, Q);
    }

}

//Calculer et renvoie le point de la courbe de Bezier de degre 2 
Point Bezier_degre_2(Bezier2 B, double t){
    Point P = add_point(mult_scalaire_point(B.C0, pow(1 - t, 2)), mult_scalaire_point(B.C1, 2 * t * (1 - t)));
    P = add_point(P, mult_scalaire_point(B.C2, pow(t, 2)));
    return P;
}

//Calculer et renvoie le point de la courbe de Bezier de degre 3 
Point Bezier_degre_3(Bezier3 B,double t){
    Point P = add_point(mult_scalaire_point(B.C0, pow(1-t, 3)), mult_scalaire_point(B.C1, 3*t*pow(1-t, 2)));
    P = add_point(P, mult_scalaire_point(B.C2, 3*pow(t, 2)*(1-t)));
    P = add_point(P, mult_scalaire_point(B.C3, pow(t, 3)));
    return P;
}

//calculer la distance entre un point et la courbe de bezier de degre 2
double distance_point_bezier2(Point A, Bezier2 B, double t){
    return distance_points(A,Bezier_degre_2(B,t));
}

//calculer la distance entre un point et la courbe de bezier de degre 2
double distance_point_bezier3(Point A, Bezier3 B , double t){
    return distance_points(A,Bezier_degre_3(B,t));
}


//Elevation de degre : exprimer une courbe de bezier de degre 2 comme courbe de bezier de degre 3
Bezier3 conversion_en_bezier_3(Bezier2 B2){
    Bezier3 B3;
    B3.C0= B2.C0;
    double k1= 1. /3.;
    double k2 =2. /3. ;

    B3.C1 = add_point(mult_scalaire_point(B2.C0, k1), mult_scalaire_point(B2.C1, k2));
    B3.C2 = add_point(mult_scalaire_point(B2.C2, k1) , mult_scalaire_point(B2.C1, k2));
    B3.C3 = B2.C2;
    return B3;
    
}
