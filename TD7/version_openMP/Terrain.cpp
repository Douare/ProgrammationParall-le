//
// Created by sophie on 22/10/19.
//
#include "Terrain.h"
#include <iostream>

using namespace std;

mnt::mnt() : Z(NULL),W(NULL) {
    t[0] = 0;
    t[1] = 0;
}

void mnt::set_t(int nr, int nc) {
    this->t[0] = nr;
    this->t[1] = nc;
}

void mnt::set_novalue(float novalue)
{
    this->novalue = novalue;
}

void mnt::set_max()
{
    float max = 0.0;
    for (int i = 0; i < t[0]; i++)
        for (int j = 0; j < t[1]; j++)
            if (Z[i * t[1] + j] > max)
                max = Z[i * t[1] + j];
    this->max = max;
}

void mnt::set_ZW() {
    Z = new float[t[0]*t[1]];
    W = new float[t[0]*t[1]];
}

int mnt::get_nr() {
    return t[0];
}

int mnt::get_nc(){
    return t[1];
}

float mnt::get_max() {
    return this->max;
}
int mnt::get_novalue() {
    return novalue;
}

float *mnt::get_Z_ptr() {
    return Z;
}

float * mnt::get_W_ptr() {
    return W;
}

void mnt::printW() {
    for (int i=0; i<t[0]; i++) {
        for (int j = 0; j < t[1]; j++)
            cout << W[i*t[1]+j] << " ";
        cout << endl;
    }
    cout << endl;
};

void mnt::printZ() {
    for (int i=0; i<t[0]; i++) {
        for (int j = 0; j < t[1]; j++)
            cout << Z[i*t[1]+j] << " ";
        cout << endl;
    }
    cout << endl;
};

float mnt::get_Z(int i, int j) {
    return Z[i*t[1]+j];
}

float mnt::get_W(int i, int j) {
    return W[i*t[1]+j];
}

mnt::~mnt() {
    if (this!=NULL) {
        if (Z != NULL)
            delete[] Z;
        if (W != NULL)
            delete[] W;
    }
}