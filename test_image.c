#include <stdio.h>
#include <stdlib.h>
#include "image.h"


int main(int argc , char ** argv){
    
    Image I, Ineg;
   
    
  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }
  
    I=lire_fichier_image(argv[1]);

    ecrire_image(I);

    printf("\n l'image negatif : \n");

    Ineg = negatif_image(I);

    ecrire_image(Ineg);
}