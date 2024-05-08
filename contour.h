#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"
#include "geom2d.h"
#include "liste_points.h"
#include "liste_contour.h"


// type orientation du robot
typedef enum
{
    NORD,
    EST,
    OUEST,
    SUD
} Orientation;

Point trouver_pixel_depart(Image I);

void avancer(Point *P, Orientation o);

Orientation tourner_gauche(Orientation o);

Orientation tourner_droite(Orientation o);

Orientation nouvelle_orientation(Image I, Point P, Orientation o);

Liste_Point calculer_contour(Image I, Point p_depart);

Liste_Contour calculer_contour_s(Image I);

#endif
