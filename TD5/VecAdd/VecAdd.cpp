/* *********************************************
Pour plus d'informations sur les threads c++11
http://en.cppreference.com/w/cpp/thread/thread
et en français mal traduit :
http://fr.cppreference.com/w/cpp/thread/thread 
***********************************************/

#include <random>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

/* 
   Mesure et affiche le temps d'exécution d'une fonction.
   Pour mesurer le temps de calcul de l'appel f(args) :
   BENCHMARK(f(args));
*/
#define BENCHMARK(fun)							\
  do { chrono::time_point<chrono::system_clock> start, end;		\
    start = chrono::system_clock::now();				\
    fun;								\
    end = chrono::system_clock::now();					\
    chrono::duration<double> elapsed_seconds = end-start;		\
    time_t end_time = chrono::system_clock::to_time_t(end);		\
    cout << #fun 							\
	 << " elapsed time: " << elapsed_seconds.count() << "s\n";	\
  } while (0)



/* addition séquentielle de deux vecteurs */
void vecadd (int size, float* v1, float* v2, float* v3){
  for (int i = 0; i < size; i++){
    v3[i] = v1[i] + v2[i];
  }
}



/* addition parallèle (TD n°4) */
void vecadd_parallel(int size, float* v1, float* v2, float* v3, int nthreads){
  int div = size/nthreads;
  int reste = size%nthreads;
  int debut = 0;
  thread th[nthreads];
  for (int i = 0; i < nthreads; i++){
    if (reste>i){
      debut = (div+1)*i;
      th[i] = thread(vecadd,div+1,v1+debut,v2+debut,v3+debut);
    }else{
      debut = div*i;
      th[i] = thread(vecadd,div,v1+debut,v2+debut,v3+debut);
    }
  }
  for (int i = 0; i < nthreads; i++)
    th[i].join();
}

/* addition parallèle avec openmp (à compléter) */
void vecadd_omp (int size, float* v1, float* v2, float* v3, int nthreads){
    #pragma omp parallel for 
    for (int i=0 ; i < nthreads; i++){
      v3[i] = v1[i] + v2[i];
    }
}


// à compléter : vérification que c1 et c2 sont les mêmes
void verif(int size, float* c1, float* c2){
}

int main(int argc, char* argv[]){
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0, 256);
  if (argc < 3)
    {
      cout << "Mauvaise utilisation du programme :\n " << 
	"./VecAdd [taille du tableau] [nombre de threads]" << endl;
      return 1;
    }
  int size = atoi(argv[1]);
  int nthreads = atoi(argv[2]);  
  
  float * A = new float[size];
  float * B = new float[size];
  float * Cseq = new float[size];

  float * Cpar = new float[size];

  
  
  #pragma omp parallel for 
  for (int i = 0; i < size ; i++){
    A[i] = dis(gen);
    B[i] = dis(gen);
  }
  
  BENCHMARK(vecadd(size, A, B, Cseq));
  BENCHMARK(vecadd_parallel(size, A, B, Cpar, nthreads));
  
  verif(size,Cseq,Cpar);

  
  BENCHMARK(vecadd_omp(size, A, B, Cpar, nthreads));
  verif(size,Cseq, Cpar);

  
  
  delete [] A;
  delete [] B;
  delete [] Cseq;
  delete [] Cpar;
  
  return 0;
}
