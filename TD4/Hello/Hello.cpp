/***********************************************
Pour plus d'informations sur les threads c++11
http://en.cppreference.com/w/cpp/thread/thread
et en français mal traduit :
http://fr.cppreference.com/w/cpp/thread/thread 
************************************************/

#include <iostream>
#include <thread>

using namespace std;

void printHello(){
  auto id = this_thread::get_id();
  cout << " Hello"<< id;
  cout << " World " << id << "!" << endl;
}

#define NUM_THREADS 8

int main(int argc, char* argv[]){
  thread th[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++)
    th[i] = thread(printHello);

  for (int i = 0; i < NUM_THREADS; i++)
    th[i].join();

  
}
