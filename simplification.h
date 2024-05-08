#ifndef __SIMPLIFICATION_H__
#define __SIMPLIFICATION_H__

#include "liste_points.h"
#include "geom2d.h"
#include "liste_contour.h"
#include "image.h"
#include "contour.h"


Contour simplification_douglas_peucker_segments(Contour Cont, int j1, int j2, double  d);

Liste_Contour simplification_contours(Image I, double d);

#endif
