#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Terrain.h"
#include "Point.h"

using namespace std;

void lecture(FILE *f, float *tab, int nr, int nc) {
    int iter = 0;
    for (int i = 0; i < nr; i++)
        for (int j = 0; j < nc; j++) {
            fscanf (f, "%f", &(tab[i * nc + j]));
            iter++;
        }
}
mnt *Lecture_Terrain(char *nom) {

    mnt *terrain = new mnt();
    FILE *f;
    int *n = new int[2];
    f = fopen(nom, "r");
    if (f != NULL) {
        fscanf(f, "%d", n + 1);
        fscanf(f, "%d", n);
    }
    terrain->set_t(n[0], n[1]);
    terrain->set_ZW();
    float novalue;
    int tmp;
    fscanf(f, "%d", &tmp);
    fscanf(f, "%d", &tmp);
    fscanf(f, "%d", &tmp);
    fscanf(f, "%f", &novalue);


    lecture(f, terrain->get_Z_ptr(), n[0], n[1]);

    if (f != NULL)
        fclose(f);
    delete[] n;
    return terrain;
}

void Init_W(mnt *terrain) {

    float no_value=terrain->get_novalue();
    int nc = terrain->get_nc();
    int nr = terrain->get_nr();

    float *W = terrain->get_W_ptr();
    float *Z = terrain->get_Z_ptr();
    for (int i = 0; i < nr; i++) {
        W[i * nc] = Z[i * nc];
        W[i * nc + nc - 1] = Z[i * nc + nc - 1];
    }
    for (int i = 0; i < nr; i++)
        for (int j = 1; j < nc - 1; j++) {
            if (Z[i * nc + j] == no_value)
                W[i * nc + j] = no_value;
            else
                W[i * nc + j] = terrain->get_max() + 10.0f;
        }
    for (int j = 0; j < nc; j++)
        W[(nr - 1) * nc + j] = Z[(nr - 1) * nc + j];

    for (int j = 0; j < nc; j++)
        W[j] = Z[j];
}

bool Remplissage(mnt *terrain) {

    bool modification = false;

    float *Z = terrain->get_Z_ptr();
    float *W = terrain->get_W_ptr();

    float no_value = terrain->get_novalue();

    int nr = terrain->get_nr();
    int nc = terrain->get_nc();
    float *W_new = new float[nr * nc];

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            Point *centre = new Point(i, j);
            float Zc = Z[i * nc + j];
            float Wc = W[i * nc + j];
            float Wn;
            W_new[i * nc + j] = W[i * nc + j];
            if (Wc > Zc && Wc != no_value) {
                Point *v1 = new Point(i, j + 1);
                for (int k = 0; k < 8; k++) {
                    float Epsilon = 1.0;
                    Wn = W[v1->r * nc + v1->c];
                    if (Zc >= Wn + Epsilon) {
                        W_new[i * nc + j] = Zc;
                        modification = true;
                    } else if (Wc > Wn + Epsilon) {
                        W_new[i * nc + j] = Wn + Epsilon;
                        modification = true;
                    }
                    if (k != 7) {
                        Point *v2 = v1->Next_Voisin(centre);
                        v1->r = v2->r;
                        v1->c = v2->c;
                    }
                }
            }
        }
    }

    for (int i = 0; i < nr; i++)
        for (int j = 0; j < nc; j++)
            W[i * nc + j] = W_new[i * nc + j];

    free(W_new);

    return modification;
}

