/***********************************************
Pour plus d'informations sur les threads c++11
http://en.cppreference.com/w/cpp/thread/thread
et en français mal traduit :
http://fr.cppreference.com/w/cpp/thread/thread 
************************************************/

#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]){
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    cout << " Hello"<< id;
    cout << " World " << id << "!" << endl;
  }
}
