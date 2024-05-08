#include "bezier.h"
#include "liste_contour.h"
#include "geom2d.h"
#include "contour.h"
#include "simplification.h"

double alpha_2(double n){
    return (3. * n) / (n * n - 1.);
}

double beta_2(double n){
    return (1. - 2. * n) / (2. * (n + 1.));
}


//Approximation d’un Contour par une courbe de Bezier de degre 2
Bezier2 approx_bezier_2(Contour C){
    Bezier2 B;
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    // DEFINIR LES POINT DE CONTROLE

    B.C0=T.tab[0];                  //premier point de controle
    B.C2 = T.tab[T.taille - 1];     // dernier point de controle

    //Calcul du dernier point de Controle
    int n= T.taille -1;
    if(n==1){
        B.C1 = mult_scalaire_point(add_point(B.C0, B.C2), 0.5);
    }
    else{
        double a = alpha_2((double)n);
        double b = beta_2((double)n);
        Point S = {0, 0};

        for (int i = 1; i < n; i++)
        {
            S = add_point(S, T.tab[i]);
        }

        B.C1 = add_point(mult_scalaire_point(S, a), mult_scalaire_point(add_point(B.C0, B.C2), b));
    }
    return B;
}

//simplifier la partie du contour CONT comprise entre les indices j1 et j2 avec la distance-seuil d

/* 
   j1: indice du premier point du contour à simplifier
   j2: indice du dernier point du contour à simplifier
*/

//fonction pour renvoyer la partie du contour comprise entre l'indice j1 et j2 
Contour partie_contour(Contour CONT, int j1, int j2)
{
    Contour L = creer_liste_Point_vide();
    int i = 0;
    Cellule_Liste_Point *C = CONT.first;
    while (C != NULL && i <= j2)
    {
        if (i >= j1 && i <= j2)
        {
            L = ajouter_element_liste_Point(L, C->data);
        }
        C = C->suiv;
        i++;
    }
    return L;
}


// retourne le contour simplifie par bezier degre 2
Contour simplification_douglas_peucker_bezier2(Contour C,int j1, int j2, double d){
    int n = j2 - j1;
    Contour LS = creer_liste_Point_vide();
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    Bezier2 B = approx_bezier_2(partie_contour(C, j1, j2));

    double dmax=0;
    int k = j1;

    for (int j = j1 + 1; j < j2;j++){
        int i = j - j1;
        double ti = (double)i / (double)n;
        double dj = distance_point_bezier2(T.tab[j], B, ti);
        if(dmax<dj){
            dmax = dj;
            k = j;
        }
    }
    if (dmax <= d)
    {
        LS = ajouter_element_liste_Point(LS, B.C0);
        LS = ajouter_element_liste_Point(LS, B.C1);
        LS = ajouter_element_liste_Point(LS, B.C2);
    }
    else
    {
        Contour L1 = simplification_douglas_peucker_bezier2(C, j1, k, d);
        Contour L2 = simplification_douglas_peucker_bezier2(C, k, j2, d);
        LS = concatener_liste_Point(L1, L2);
    }
    return LS;
}


// simplification bezier degre 3

//Calcul des coefficients necessaires:
double alpha_3(int n)
{
    double N = (double)(n);
    return (-15. * pow(N, 3.) + 5. * pow(N, 2.) + 2. * N + 4.) / (3. * (N + 2.) * (3. * pow(N, 2.) + 1.));
}
double beta_3(int n)
{
    double N = (double)(n);
    return (10. * pow(N, 3.) - 15. * pow(N, 2.) + N + 2.) / (3. * (N + 2.) * (3. * pow(N, 2.) + 1.));
}
double lambda_3(int n)
{
    double N = (double)(n);
    return (70. * N) / (3. * (pow(N, 2.) - 1.) * (pow(N, 2.) - 4.) * (3. * pow(N, 2.) + 1.));
}
double gamma_3(int k, int n)
{
    double K = (double)(k);
    double N = (double)(n);
    return 6. * pow(K, 4.) - 8. * N * pow(K, 3.) + 6. * pow(K, 2.) - 4. * N * K + pow(N, 4.) - pow(N, 2.);
}

//Approximation d'un contour par une courbe de Bézier de degré 3
Bezier3 approx_bezier3(Contour C)
{
    Bezier3 B;
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    int n = T.taille - 1;
    if (n <= 2)
    {
        B = conversion_en_bezier_3(approx_bezier_2(C));
    }
    else
    {
        B.C0 = T.tab[0];            //premier point de controle
        B.C3 = T.tab[n];            // dernier point de controle
        double a = alpha_3(n);
        double b = beta_3(n);
        double l = lambda_3(n);
        Point somme;

        // Calcul de C1: deuxime point de controle
        somme = set_point(0, 0);
        for (int i = 1; i <= n - 1; i++)
        {
            somme = add_point(somme, mult_scalaire_point(T.tab[i], gamma_3(i, n)));
        }
        B.C1 = add_point(mult_scalaire_point(B.C0, a), add_point(mult_scalaire_point(somme, l), mult_scalaire_point(B.C3, b)));
        
        // Calcul de C2 : troisieme point de controle
        somme = set_point(0, 0);
        for (int i = 1; i <= n - 1; i++)
        {
            somme = add_point(somme, mult_scalaire_point(T.tab[i], gamma_3(n - i, n)));
        }
        B.C2 = add_point(mult_scalaire_point(B.C0, b), add_point(mult_scalaire_point(somme, l), mult_scalaire_point(B.C3, a)));
    }
    return B;
}


//Simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
//retourne: le contour simplifie
Contour simplification_douglas_peucker_bezier3(Contour C, int j1, int j2, double d)
{
    int n = j2 - j1;
    Contour LS = creer_liste_Point_vide();
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    Bezier3 B = approx_bezier3(partie_contour(C, j1, j2));
    double dmax = 0;
    int k = j1;
    for (int j = j1 + 1; j < j2; j++)
    {
        double ti = (double)(j - j1) / (double)n;
        double dj = distance_point_bezier3(T.tab[j], B, ti);
        if (dj > dmax)
        {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d)
    {
        LS = ajouter_element_liste_Point(LS, B.C0);
        LS = ajouter_element_liste_Point(LS, B.C1);
        LS = ajouter_element_liste_Point(LS, B.C2);
        LS = ajouter_element_liste_Point(LS, B.C3);
    }
    else
    {
        Contour L1 = simplification_douglas_peucker_bezier3(C, j1, k, d);
        Contour L2 = simplification_douglas_peucker_bezier3(C, k, j2, d);
        LS = concatener_liste_Point(L1, L2);
    }
    return LS;
}
