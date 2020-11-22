#include <iostream>
#include <mpi.h>

using namespace std;

int main ( int argc , char **argv )
{
  int pid, nprocs;  
  MPI_Init (&argc , &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid ) ;
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs ) ;
  cout << "I am " << pid << " of " << nprocs << " processors" << endl;
  
  MPI_Finalize( ) ;
  return 0 ;
}
// Exercice 1
// Question 1:
// (base) juliette@juliette-G3-3779:~/Documents/ProgrammationParallele/TD1/Hello$ mpirun -np 10 ./main 
// I am 0 of 10 processors
// I am 5 of 10 processors
// I am 6 of 10 processors
// I am 9 of 10 processors
// I am 2 of 10 processors
// I am 3 of 10 processors
// I am 7 of 10 processors
// I am 4 of 10 processors
// I am 1 of 10 processors
// I am 8 of 10 processors


// Question 2:
// (base) juliette@juliette-G3-3779:~/Documents/ProgrammationParallele/TD1/Hello$ mpirun -np 280 ./main
//
// [...]
//
// [juliette-G3-3779:05766] [[24041,0],0] ORTE_ERROR_LOG: The system limit on number of network connections a process can open was reached in file util/listener.c at line 321
// [juliette-G3-3779:05766] PMIX ERROR: OUT-OF-RESOURCE in file src/server/pmix_server_listener.c at line 273
// --------------------------------------------------------------------------
// Sorry!  You were supposed to get help about:
//     accept failed
// But I couldn't open the help file:
//     /usr/share/openmpi/help-oob-tcp.txt: Too many open files.  Sorry!
// --------------------------------------------------------------------------
