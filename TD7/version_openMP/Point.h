#ifndef DARBOUX_CPP_POINT_H
#define DARBOUX_CPP_POINT_H

#include <iostream>
using namespace std;
class Point {
public:
    int r;
    int c;

    Point(int r, int c);
    Point* Next_Voisin(Point* centre); // Pour parcourir les 8 voisins par rapport à la cellule étudiée.
    friend ostream& operator <<(ostream& ost, Point const & p);

};

#endif //DARBOUX_CPP_POINT_H
