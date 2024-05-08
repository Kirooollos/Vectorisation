#include "contour.h"


Point trouver_pixel_depart(Image I)
{
    Point P = {0, 0};
    for (int j = 1; j <= hauteur_image(I); j++)
    {
        for (int i = 1; i <= largeur_image(I); i++)
        {
            if (get_pixel_image(I,i,j) == 1 && get_pixel_image(I,i,j-1)==0)
            {
                P.x = i;
                P.y = j;
                return P;
            }
        }
    }
    return P;
}


Image masque(Image I){
    Image I_masquee = creer_image(largeur_image(I), hauteur_image(I));
    for (int j = 1; j <= hauteur_image(I);j++){
        for (int i = 1; i <= largeur_image(I); i++)
        {
            if(get_pixel_image(I,i,j)==NOIR && get_pixel_image(I,i,j-1)==BLANC){
                set_pixel_image(I_masquee, i, j, NOIR);
            }
        }
    }
    return I_masquee;
}

void avancer(Point  *P, Orientation o){
    switch(o){
        case(NORD):
            P->y = P->y -1;
            break;
        case(EST):
            P->x = P->x +1;
            break;

        case (OUEST):
            P->x =P ->x -1 ;
            break; 
        case (SUD):
            P->y=P->y +1;
            break;
    }
}

Orientation tourner_gauche(Orientation o){
    switch(o){
        case(NORD):
            return OUEST;
            break;
        case(OUEST):
            return SUD;
            break;
        case (SUD):
            return EST;
            break;
        case (EST):
            return NORD;
            break;
        }
        return o;
}

Orientation tourner_droite(Orientation o){
    switch (o)
    {
    case(NORD):
        return EST;
        break;
    case (EST):
        return SUD;
        break;
    case (SUD):
        return OUEST;
        break;
    case (OUEST):
        return NORD;
        break;
    }
    return o;
}

Orientation nouvelle_orientation(Image I ,Point P ,Orientation o){
    Pixel gauche, droite;
    switch (o){
        case (NORD):
            gauche = get_pixel_image(I, P.x , P.y);
            droite = get_pixel_image(I, P.x + 1, P.y);
            break;
        case (EST):
            gauche = get_pixel_image(I, P.x +1, P.y);
            droite = get_pixel_image(I, P.x +1 , P.y +1);
            break;
        case (SUD):
            gauche = get_pixel_image(I, P.x+1 , P.y+1);
            droite = get_pixel_image(I, P.x, P.y+1);
            break;
        case (OUEST):
            gauche = get_pixel_image(I, P.x , P.y+1);
            droite = get_pixel_image(I, P.x , P.y);
            break;
        }
    if (gauche==NOIR){
        return tourner_gauche(o);
    }else if(droite==BLANC){
        return tourner_droite(o);
    }
    return o;
}

Liste_Point calculer_contour(Image I, Point p_depart){
    Liste_Point L = creer_liste_Point_vide();
    Point p = {p_depart.x - 1, p_depart.y - 1};
    Orientation o = EST;
    bool contour_complet = true;

    while (contour_complet){
        L = ajouter_element_liste_Point(L, p);
        avancer(&p, o);
        o =nouvelle_orientation(I, p, o);
        
        if (p.x == p_depart.x -1 && p.y==p_depart.y -1 && o==EST ){
            contour_complet =false;            
        }
    }
    L = ajouter_element_liste_Point(L, p);
    return L;
}

//On va creer un nouveau type Liste_contour pour calculer le nombre de contour


Liste_Contour calculer_contour_s(Image I){
    Image M = masque(I);
    Liste_Contour Lc = creer_liste_Contour();
    
    

    for (int j = 1; j <= hauteur_image(I);j++){
        for (int i = 1; i <= largeur_image(I);i++){
            //condition pour commencer a calculer le contour
            if(get_pixel_image(M,i,j)==NOIR){
                Point p_depart = set_point(i, j);
                Liste_Point L = creer_liste_Point_vide();
                Point p = {p_depart.x - 1, p_depart.y - 1};
                Orientation o = EST;
                bool contour_complet = true;
                while (contour_complet){
                    L = ajouter_element_liste_Point(L, p);
                    avancer(&p, o);
                    o =nouvelle_orientation(I, p, o);
                    
                    // on modifie l'image masque en le (re)mettant a blanc
                    if(o==EST){
                        set_pixel_image(M, p.x + 1, p.y + 1, BLANC);
                    }
                    if (p.x == p_depart.x -1 && p.y==p_depart.y -1 && o==EST ){
                        contour_complet =false;            
                    }
                }
            L = ajouter_element_liste_Point(L, p);
            Lc = ajouter_element_liste_Contour(Lc, L);
            }
        }
    }
    return Lc;
}
