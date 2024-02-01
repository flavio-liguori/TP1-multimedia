// histogramme_couleur.cpp : Calcul et visualisation des histogrammes des composantes couleur d'une image au format ppm

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <fstream> 
#include <iomanip> 

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 2)
    {
        printf("Usage: ImageIn.ppm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3; // Trois composantes couleur (Rouge, Vert, Bleu)

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    std::ofstream outputFile("histogramme_couleur.dat");

    if (outputFile.is_open()) {
        int histogrammeR[256] = {0};
        int histogrammeG[256] = {0};
        int histogrammeB[256] = {0};

        for (int i = 0; i < nH; i++) {
            for (int j = 0; j < nW; j++) {
                histogrammeR[ImgIn[(i * nW + j) * 3]]++;
                histogrammeG[ImgIn[(i * nW + j) * 3 + 1]]++;
                histogrammeB[ImgIn[(i * nW + j) * 3 + 2]]++;
            }
        }

        for (int z = 0; z < 256; z++) {
            outputFile << std::setw(15) << z << std::setw(15) << histogrammeR[z] << std::setw(15) << histogrammeG[z] << std::setw(15) << histogrammeB[z] << "\n";
        }

        outputFile.close();
        std::cout << "Les données ont été enregistrées dans le fichier 'histogramme_couleur.dat'." << std::endl;
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier de sortie." << std::endl;
        return -1;
    }

    free(ImgIn);
    return 0;
}