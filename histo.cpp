#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    int nH, nW, nTaille;

    if (argc != 2)
    {
        printf("Usage: ImageIn.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    int histogramme[256] = {0};

    // Calculer l'histogramme
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            histogramme[ImgIn[i * nW + j]]++;
        }
    }

    // Écrire l'histogramme dans le fichier
    std::ofstream outputFile("histo.dat");

    if (outputFile.is_open()) {
        for (int z = 0; z < 256; z++) {
            outputFile << z << " " << histogramme[z] << "\n";
        }

        outputFile.close();
        std::cout << "Les données de l'histogramme ont été enregistrées dans le fichier 'histo.dat'." << std::endl;
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier de sortie." << std::endl;
        return -1;
    }

    free(ImgIn);
    return 0;
}