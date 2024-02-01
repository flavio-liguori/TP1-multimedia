// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <iomanip> // Pour utiliser std::setw()
#include <fstream> // Pour utiliser std::ofstream


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S,S2;

    if (argc != 5)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%d",&S);
    sscanf (argv[4],"%d",&S2);
    

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

    float range[] = {0, 256}; // Plage des niveaux de gris


    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
        {
            for (int z=0; z < 256; z++){
                if (ImgIn[i*nW+j]==z){
                    range[z] = range[z] +1;
                }
                

            }

            if ( ImgIn[i*nW+j] < S) ImgOut[i*nW+j]=0; 

            else if (ImgIn[i*nW+j] < S2) ImgOut[i*nW+j]=128;

            else ImgOut[i*nW+j]=255;
            

        }



    
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);
    std::cout << "Histogramme :\n";
    std::cout << std::setw(15) << "Niveau de gris" << std::setw(15) << "Occurrences" << "\n";
    
    for (int z = 0; z < 256; z++) {
        std::cout << std::setw(15) << z << std::setw(15) << range[z] << "\n";
    }
    std::ofstream outputFile("histogramme.txt");
    
    if (outputFile.is_open()) {
        outputFile << "Niveau de gris" << std::setw(15) << "Occurrences" << "\n";

        for (int z = 0; z < 256; z++) {
            outputFile << std::setw(15) << z << std::setw(15) << range[z] << "\n";
        }

        outputFile.close();
        std::cout << "Les données ont été enregistrées dans le fichier 'histogramme.txt'." << std::endl;
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier de sortie." << std::endl;
        return -1;
    }

    return 1;
}