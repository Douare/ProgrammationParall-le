//
// Created by sophie on 22/10/19.
//

#ifndef DARBOUX_CPP_TERRAIN_H
#define DARBOUX_CPP_TERRAIN_H

class mnt {
private:
    int t[2]; // pour la taille du MNT
    float novalue; // la valeur de no_data
    float max; // la hauteur max du MNT

    float *Z; // la matrice du MNT
    float *W; // la matrice résultat du remplissage
public:
    mnt();
    void set_t(int nr, int nc);
    void set_novalue(float novalue);
    void set_max(); // initialisation du max
    void set_ZW(); // allocation mémoire des matrices Z et W

    // getters
    int get_nr();
    int get_nc();
    int get_nr_local();
    int get_nc_local();
    float get_max();
    int get_novalue();

    float get_Z(int i, int j);
    float get_W(int i, int j);

    float* get_Z_ptr();
    float* get_W_ptr();

    // juste pour afficher Z et W
    void printZ();
    void printW();

    ~mnt();
};

#endif //DARBOUX_CPP_TERRAIN_H
