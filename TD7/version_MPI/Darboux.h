#ifndef DARBOUX_CPP_DARBOUX_H
#define DARBOUX_CPP_DARBOUX_H
#include "Terrain.h"

#define TAG 10


// lecture dans le MNT : une ligne dans la partie des données de hauteur du MNT
void lecture(FILE *f, float *tab, int nr, int nc);
// construction du terrain par lecture du fichier de données
mnt* Lecture_Terrain(char *nom);
// Initialisation de la matrice W avec les conditions aux bords et la valeur du max des hauteurs
void Init_W(mnt* terrain);
// Mise en place de l'algorithme de remplissage
bool Remplissage(mnt* terrain);

#endif //DARBOUX_CPP_DARBOUX_H
