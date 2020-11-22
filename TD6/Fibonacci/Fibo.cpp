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
#include <omp.h>

using namespace std;

//************ Utilisation des tâches openMP *********************************80
/*
    Pour paralléliser la version récursive de fibonacci:
        1- omp sections, section
        2- omp task, parallel single, taskwait
*/

int fibo (int n){
    int x, y;
    if(n<=2){
        return 1;
    }else{
        #pragma omp parallel sections
        {
            #pragma omp section
            {
            x = fibo(n-2);      
            }
            #pragma omp section
            {
            y = fibo(n-1);
            }
        }
        return x+y;
    }
}

int fibo_task (int n){
    int x, y;
    if(n<=2){
        return 1;
    }else{
        #pragma omp single
        {
            #pragma omp task shared(x)
            {
            x = fibo_task(n-2);      
            }
            #pragma omp task shared(y)
            {
            y = fibo_task(n-1);
            }
            #pragma omp taskwait
        }
        return x+y;
    }
}

int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int nthread = atoi(argv[2]);
    omp_set_num_threads(nthread);
    cout << "Fibo de n = " << fibo(n) <<endl;
    cout << "Fibo de n = " << fibo_task(n) <<endl;
    return 0;
}