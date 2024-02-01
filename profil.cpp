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

    if (argc != 4)
    {
        printf("Usage: ImageIn.pgm choix numero \n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",choix);
    sscanf (argv[3],"%d",&numero);
    

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

    float range[] = {0, 10000};
    char copie[256];
    strcpy(copie,choix);
    char copie2[256];
    strcpy(copie2,choix);
    


    if (strcmp(choix, "ligne") == 0){
        for (int y=0; y < nW; y++){
            for (int z=0; z < 256; z++){
                if (ImgIn[numero*nW+y]==z){
                    range[y] = z;
                }
            } 
        }    

    }
    if (strcmp(choix, "colonne") == 0){
        for (int v=0; v < nH; v++){
            for (int z=0; z < 256; z++){
                if (ImgIn[v*nW+numero]==z){
                    range[v] = z;
                }
            }
        }     

    }

    std::cout << "Histogramme :\n";

    if (strcmp(copie, "ligne") == 0){
        std::cout << "test" << std::endl;
        for (int z = 0; z < nW; z++) {
            std::cout << std::setw(15) << z << std::setw(15) << range[z] << "\n";
        }
    }
    if (strcmp(copie, "colonne") == 0){
        for (int z = 0; z < nH; z++) {
            std::cout << std::setw(15) << z << std::setw(15) << range[z] << "\n";
        }
    }
    std::ofstream outputFile("histogramme.dat");
    
    if (outputFile.is_open()) {
       

        if (strcmp(copie2, "ligne") == 0){
            for (int z = 0; z < nW; z++) {
                outputFile << std::setw(15) << z << std::setw(15) << range[z] << "\n";            }
        }

        if (strcmp(copie2, "colonne") == 0){
            for (int z = 0; z < nH; z++) {
                outputFile << std::setw(15) << z << std::setw(15) << range[z] << "\n";            }
        }

        outputFile.close();
        std::cout << "Les données ont été enregistrées dans le fichier 'histogramme.txt'." << std::endl;
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier de sortie." << std::endl;
        return -1;
    }

    return 1;
}