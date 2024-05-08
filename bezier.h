#ifndef __BEZIER_H__
#define __BEZIER_H__

#include "liste_points.h"
#include "geom2d.h"
#include "liste_contour.h"
#include "image.h"
#include "contour.h"
#include "simplification.h"

double alpha_2(double n);

double beta_2(double n);

Bezier2 approx_bezier_2(Contour C);

Contour partie_contour(Contour CONT, int j1, int j2);

Contour simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d);

double alpha_3(int n);
double beta_3(int n);
double lambda_3(int n);
double gamma_3(int k, int n);

Bezier3 approx_bezier3(Contour C);

Contour simplification_douglas_peucker_bezier3(Contour C, int j1, int j2, double d);


#endif 