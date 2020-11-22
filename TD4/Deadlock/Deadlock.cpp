/*********************************************
Pour plus d'informations sur les conditions :
http://en.cppreference.com/w/cpp/thread/condition_variable 
et en français (mal traduit) :
http://fr.cppreference.com/w/cpp/thread/condition_variable
**********************************************/

#include <random>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


#define NUM_THREADS  6
#define TCOUNT 10
#define COUNT_LIMIT 12

int count = 0;
mutex count_m;
condition_variable count_threshold_cv;


void inc_count(int idp){
  double result = 0.0;
  
  for (int i = 0; i < TCOUNT; i++){

    /* spécifique à l'utilisation de conditions.
       Verrouille le mutex
    */
    std::unique_lock<std::mutex> lock(count_m);
    count++;
    
    
    /* 
       Vérifie la valeur de count et envoie un signal aux threads en attente
       lorsque la condition est atteinte.  Notez que cela a lieu
       lorsque le mutex est verrouillé.
    */
    if (count == COUNT_LIMIT){
      count_threshold_cv.notify_one();
      cout << "inc_count(): thread "<< idp << " count = " << count << "Threshold reached." << endl;
    }
    
    cout << "inc_count(): thread "<< idp << " count = " << count << endl;
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

  } 
}


void watch_count(int idp){
  cout << "Starting watch_count(): thread "<< idp << endl;
  /*
  Verrouille le mutex et attend le signal. Notez que wait
  va automatiquement et atomiquement déverrouiller le mutex pendant
  qu'il attend.  
    */
  std::unique_lock<std::mutex> lock(count_m);

  cout << "***Before cond_wait: thread "<<  idp << endl;
  /* Déverrouille le mutex */
  count_threshold_cv.wait(lock);
  cout << "***Thread "<< idp << " Condition signal received." << endl;

}



int main(int argc, char* argv[]){
  thread threads[6];
  threads[2] = thread(watch_count, 2);
  threads[3] = thread(watch_count, 3);
  threads[4] = thread(watch_count, 4);
  threads[5] = thread(watch_count, 5);
  threads[0] = thread(inc_count, 0);
  threads[1] = thread(inc_count, 1);
  
  
  for (int i = 0; i < NUM_THREADS ; i++){
    threads[i].join();
  }
  cout << "Main(): Waited on " << NUM_THREADS <<" threads. Done." << endl;
  
  return 0;
}
