#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

int*  generation_mat(int taille)
{
  int* mat = new int[taille*taille];
  for (int i=0; i<taille*taille; i++)
    mat[i] = rand()%10;
  return mat;
}

int* transposition(int n, int* A)
{

  int* ATranspose = new int[n*n];
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      ATranspose[i*n+j] = A[j*n+i];
    }
  }
  return ATranspose;
}

void ecriture(int n, int* A)
{
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      cout << A[i*n+j] << " ";
  cout << endl; 
}

int main ( int argc , char **argv )
{
  int pid, nprocs;  
  MPI_Init (&argc , &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid ) ;
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs ) ;
  MPI_Comm Comm_grille; // Nouveau communicateur pour la topologie cartésienne.

  int n = atoi(argv[1]);
  
  srand(pid);
  int* A_local = generation_mat(n);
  cout << "pid=" << pid << " ";
  ecriture(n,A_local);

  int* B_local_transpose = transposition (n,A_local);
  int* A_local_transpose = new int[n*n];
  
  int nbprocs_dims[2];
  int period[2];
  nbprocs_dims[0]=0;
  nbprocs_dims[1]=0;
  period[0] = 0;
  period[1] = 0;
  MPI_Dims_create(nprocs, 2, nbprocs_dims);  
  MPI_Cart_create(MPI_COMM_WORLD, 2, nbprocs_dims, period, true, &Comm_grille);
  int mycoords[2];

  MPI_Cart_coords(Comm_grille, pid, 2, mycoords);

  cout << "pid=" << pid << " (i,j)=" << mycoords[0] << " " << mycoords[1] << endl;

  int coords[2];
  coords[0] = mycoords[1];
  coords[1] = mycoords[0];

  int dest;
  MPI_Cart_rank(Comm_grille,coords,&dest);


  MPI_Request request_send;
  MPI_Request request_recv;
  MPI_Status status;
  MPI_Isend(B_local_transpose,n*n,MPI_INT,dest,123,MPI_COMM_WORLD,&request_send);
  MPI_Irecv(A_local_transpose,n*n,MPI_INT,dest,MPI_ANY_TAG,MPI_COMM_WORLD,&request_recv);

  MPI_Wait(&request_recv,&status);
  cout << "pid=" << pid << " ";
  ecriture(n,A_local_transpose);


  MPI_Comm_free(&Comm_grille);
  delete[] A_local;
  delete[] B_local_transpose;
  delete[] A_local_transpose;
  MPI_Finalize() ;
  
  

  return 0 ;
}
