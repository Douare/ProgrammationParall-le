#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>

using namespace std;

double somme = 0;

/* à compléter : addition en anneau */ 
void addition_ring  (int numthread, int nthreads, mutex *mutring){
  mutring[numthread].lock();
  double a = rand()%(numthread+10);
  double somme_locale;

  cout << "Je suis le fils n°" << numthread << " et mon a est égal à ("<< a << ")."<< endl;
  somme_locale = somme;
  somme_locale += a;
  somme = somme_locale;  

  if (numthread != nthreads){
    mutring[numthread+1].unlock();
  }

}


int main(int argc, char* argv[]){
  if (argc < 2)
    {
      cout << "Mauvaise utilisation du programme :\n " << 
	"./Addring [nombre de threads]" << endl;
      return 1;
    }

  int nthreads = atoi(argv[1]); 
  mutex *mutring = new mutex[nthreads];
  thread th[nthreads];

  for (int i = 1; i < nthreads; i++){
    mutring[i].lock();
  }

  for (int i = 0; i < nthreads; i++){
    th[i] = thread(addition_ring,i,nthreads,mutring);
  }

  for (int i = 0; i < nthreads; i++)
    th[i].join();
  
  cout << "Je suis le papa et la somme est égale à "<< somme << endl;
  
  return 0;
}
