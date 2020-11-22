/************************************************
Pour plus d'informations sur les mutex en c++11
http://en.cppreference.com/w/cpp/thread/mutex 
et en français mal traduit : 
http://fr.cppreference.com/w/cpp/thread/mutex
************************************************/
#include <random>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std;






// à compléter : tri fusion parallèle
void tri_fusion (int* atrier, int n){
  
}

// à compléter : vérification que le tableau est bien trié
void verif(int* c1, int* c2, int n){

}

int main(int argc, char* argv[]){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, 256);
  if (argc < 2)
    {
      cout << "Mauvaise utilisation du programme :\n " << 
	"./Tri [taille du tableau] [nombre de threads]" << endl;
      return 1;
    }
  int size = atoi(argv[1]);
  
  int* Atrier = new int[size];
  int* PourVerif = new int[size];
  
  for (int i = 0; i < size ; i++){
    Atrier[i] = dis(gen);
    PourVerif[i] = Atrier[i];
  }
  
  
  /* à compléter */

  verif(PourVerif,Atrier,size);
  
  delete [] Atrier;
  delete [] PourVerif;
  
  return 0;
}
