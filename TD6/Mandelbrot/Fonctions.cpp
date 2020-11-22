//
// Created by sophie on 19/11/2019.
//
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstring>

#include "Fonctions.h"

using namespace std;

//****************************************************************************80

int i4_min ( int i1, int i2 ){
    int value;

    if ( i1 < i2 )
    {
        value = i1;
    }
    else
    {
        value = i2;
    }
    return value;
}
//****************************************************************************80

void i4pp_delete ( int **a, int m, int n ){
    int i;

    for ( i = 0; i < m; i++ )
    {
        delete [] a[i];
    }

    delete [] a;

    return;
}
//****************************************************************************80

int **i4pp_new ( int m, int n ){
    int **a;
    int i;

    a = new int *[m];

    if ( a == NULL )
    {
        cerr << "\n";
        cerr << "I4PP_NEW - Fatal error!\n";
        cerr << "  Unable to allocate row pointer array.\n";
        exit ( 1 );
    }

    for ( i = 0; i < m; i++ )
    {
        a[i] = new int[n];
        if ( a[i] == NULL )
        {
            cerr << "\n";
            cerr << "I4PP_NEW - Fatal error!\n";
            cerr << "  Unable to allocate row array.\n";
            exit ( 1 );
        }
    }

    return a;
}
