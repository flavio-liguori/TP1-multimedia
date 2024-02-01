#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgSeuillee[250];
    int nH, nW, nTaille, S_R, S_G, S_B;

    if (argc != 6)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm Seuil_R Seuil_G Seuil_B\n");
        exit (1);
    }

    sscanf (argv[1], "%s", cNomImgLue);
    sscanf (argv[2], "%s", cNomImgSeuillee);
    sscanf (argv[3], "%d", &S_R);
    sscanf (argv[4], "%d", &S_G);
    sscanf (argv[5], "%d", &S_B);

    OCTET *ImgIn, *ImgOutR, *ImgOutG, *ImgOutB;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3; // Trois composantes couleur (Rouge, Vert, Bleu)

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOutR, OCTET, nTaille);
    allocation_tableau(ImgOutG, OCTET, nTaille);
    allocation_tableau(ImgOutB, OCTET, nTaille);

    // Seuillage des composantes couleurs
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            // Seuillage pour la composante Rouge
            ImgOutR[(i * nW + j) * 3] = (ImgIn[(i * nW + j) * 3] < S_R) ? 0 : 255;

            // Seuillage pour la composante Vert
            ImgOutG[(i * nW + j) * 3 + 1] = (ImgIn[(i * nW + j) * 3 + 1] < S_G) ? 0 : 255;

            // Seuillage pour la composante Bleu
            ImgOutB[(i * nW + j) * 3 + 2] = (ImgIn[(i * nW + j) * 3 + 2] < S_B) ? 0 : 255;
        }
    }

    // Écrire les images seuillées
    ecrire_image_ppm(cNomImgSeuillee, ImgOutR, nH, nW);
    ecrire_image_ppm(cNomImgSeuillee, ImgOutG, nH, nW);
    ecrire_image_ppm(cNomImgSeuillee, ImgOutB, nH, nW);

    free(ImgIn);
    free(ImgOutR);
    free(ImgOutG);
    free(ImgOutB);

    return 0;
}