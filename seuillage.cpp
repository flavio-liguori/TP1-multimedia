// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <iomanip> // Pour utiliser std::setw()
#include <fstream> // Pour utiliser std::ofstream
#include <string.h>


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250],choix[256];
    int nH, nW, nTaille,numero;

    if (argc != 3)
    {
        printf("Usage: ImageIn.pgm choix numero \n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%d",&numero);
    

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    //   for (int i=0; i < nTaille; i++)
    // {
    //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
    //  }

    


    for (int y=0; y < nW; y++){
        std::cout << ImgIn[numero*nW+y] << std::endl;

                
            
        
    }    

    

    
}