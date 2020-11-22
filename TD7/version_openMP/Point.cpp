#include "Point.h"

Point::Point(int r, int c)
{
    this->r = r;
    this->c = c;
}

ostream& operator <<(ostream& ost, Point const & p)
{
    ost << "(" << p.r << "," << p.c << ")";
    return ost;
}

Point* Point::Next_Voisin(Point* centre) {
    Point* v2 = new Point(0,0);
    if ((this->r == centre->r) && (this->c == centre->c+1)) {
        v2->r = centre->r + 1;
        v2->c = centre->c + 1;
    }
    if ((this->r == centre->r+1) && (this->c == centre->c+1)) {
        v2->r = centre->r + 1;
        v2->c = centre->c;
    }
    if ((this->r == centre->r+1) && (this->c == centre->c)) {
        v2->r = centre->r + 1;
        v2->c = centre->c - 1;
    }
    if ((this->r == centre->r+1) && (this->c == centre->c-1)) {
        v2->r = centre->r;
        v2->c = centre->c - 1;
    }
    if ((this->r == centre->r) && (this->c == centre->c-1)) {
        v2->r = centre->r - 1;
        v2->c = centre->c - 1;
    }
    if ((this->r == centre->r-1) && (this->c == centre->c-1)) {
        v2->r = centre->r - 1;
        v2->c = centre->c;
    }
    if ((this->r == centre->r-1) && (this->c == centre->c)) {
        v2->r = centre->r - 1;
        v2->c = centre->c + 1;
    }
    if ((this->r == centre->r-1) && (this->c == centre->c+1)) {
        v2->r = centre->r;
        v2->c = centre->c + 1;
    }

    return v2;
}
