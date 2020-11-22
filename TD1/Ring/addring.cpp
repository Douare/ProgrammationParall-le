#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int addition_ring(int a, int root) {
  int sommefinale = 0;
  int pid;
  int nprocs;
  int* somme = new int[1];
  int* sommetmp = new int[1];
  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  if(pid==root){
    sommetmp[0] = a;
    MPI_Send(sommetmp,1,MPI_INT,(pid+1)%nprocs,0,MPI_COMM_WORLD);
    MPI_Recv(somme,1,MPI_INT,(pid-1)%nprocs,0,MPI_COMM_WORLD,&status);
    sommefinale = somme[0];
  }else{
    MPI_Recv(somme,1,MPI_INT,(pid-1)%nprocs,0,MPI_COMM_WORLD,&status);
    sommetmp[0] = somme[0]+a;
    MPI_Send(sommetmp,1,MPI_INT,(pid+1)%nprocs,0,MPI_COMM_WORLD);
  }
  return sommefinale;
}

int main ( int argc , char **argv )
{
  int pid, nprocs;  
  MPI_Status status;
  MPI_Init (&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
  
  int root = atoi(argv[1]);
  
  srand(time(NULL)+pid);
  int a = rand()%10;

  cout << "je suis " << pid << " et la valeur est " << a << endl;
  
  int somme = addition_ring(a,root);
  if (pid==root)
    cout << "je suis " << pid << " et la somme est " << somme << endl;  
  
  
  MPI_Finalize() ;
  return 0 ;
}
