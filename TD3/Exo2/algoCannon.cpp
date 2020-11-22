#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


// génération aléatoire d'une matrice d'entiers taillextaille
// comme un tableau à une dimension
int*  generation_mat(int taille)
{
  int* mat = new int[taille*taille];
  for (int i=0; i<taille*taille; i++)
    mat[i] = rand()%10;
  return mat;
}

// Produit C+=AxB
void operation_elementaire(int n, int* A, int* B, int* C)
{
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      int ele = 0; 
      for (int k=0; k<n; k++)
	ele = ele + A[i*n+k]*B[k*n+j];
      C[i*n+j] = C[i*n+j] + ele;      
    }
  }  
}

// affichage d'une matrice nxn
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
  MPI_Status status;

  int n = atoi(argv[1]);
  srand(pid);
  int gauche, droite, haut, bas;
  
  int *A_local = generation_mat(n);
  int *B_local = generation_mat(n);
  int *C_local = new int[n*n];

  cout << "je suis " << pid << " et A_local : ";
  ecriture(n,A_local);
  
  cout << "je suis " << pid << " et B_local : ";
  ecriture(n,B_local);
  
  for (int i=0; i<n*n; i++)
    C_local[i] = 0;


  // Récupère les dimensions de la matrice
  int dims[2] = {0,0};
  MPI_Dims_create(nprocs,2,dims);

  // periods sert à déterminer si les lignes et les colonnes sont circulaires
  // MPI_Cart_create créé la grille
  int periods[2] = {1,1};
  MPI_Cart_create(MPI_COMM_WORLD,2,dims,periods,1,&Comm_grille);

  // Récupère les coordonnées des pid dans la matrice
  int coords[2];
  MPI_Cart_coords(Comm_grille,pid,2,coords);

  //Etape 1 : décalage des lignes de A et des colonnes de B pour préparer la multiplication
  // Shift
  MPI_Cart_shift(Comm_grille,0,coords[1],&gauche,&droite);
  MPI_Cart_shift(Comm_grille,1,coords[0],&haut,&bas);
  MPI_Sendrecv_replace(A_local,n*n,MPI_INT,droite,54,gauche,54, Comm_grille, &status);
  MPI_Sendrecv_replace(B_local,n*n,MPI_INT,bas,110,haut,110, Comm_grille, &status);

  //Etape 2 : produit des matrices A et B dans C
  MPI_Cart_shift(Comm_grille,0,1,&gauche,&droite);
  MPI_Cart_shift(Comm_grille,1,1,&haut,&bas);
  for (int i = 0; i < nprocs; ++i){
    operation_elementaire(n,A_local,B_local,C_local);
    MPI_Sendrecv_replace(A_local,n*n,MPI_INT,droite,54,gauche,54,Comm_grille,&status);
    MPI_Sendrecv_replace(B_local,n*n,MPI_INT,bas,110,haut,110,Comm_grille,&status);
  }

  cout << "je suis " << pid << " et C_local : ";
  ecriture(n,C_local);
  
   delete[] A_local;
   delete[] B_local;
   delete[] C_local;
  
  MPI_Finalize() ;
  
  return 0 ;
}
