#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int main ( int argc , char **argv )
{
  int pid, nprocs;  
  MPI_Init (&argc , &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid ) ;
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs ) ;
  MPI_Comm Comm_grille; // Nouveau communicateur pour la topologie cartésienne.
  MPI_Comm Comm_ligne;
  MPI_Comm Comm_colonne;

  int p = atoi(argv[1]);
  int q = atoi(argv[2]);
  
  int *period = new int[2];
  period[0]=0;
  period[1]=0;

  int* dims = new int[2];
  dims[0]=p;
  dims[1]=q;

  srand(time(NULL) + pid);
  int a = rand() % 10;

  int *coords = new int[2];

  int root_comm_col; 
  int root_comm_ligne;

  int somme;
  int somme_finale;

  int vecLigne[2] = {1,0};
  int vecColonne[2] = {0,1};

  int coordsRoot[1] = {0};


  // LE PROGRAMME EST EXECUTE PAR CHAQUE PROCESSEUR

  // Topologie cartésienne
  MPI_Cart_create(MPI_COMM_WORLD, 2, dims, period, 1, &Comm_grille);

  // coords contient les coordonnées de chaque proc
  MPI_Cart_coords(Comm_grille,pid,2,coords);
  cout << "je suis le pid: " << pid << " aux coordonnées (=" << coords[0] << ", " << coords[1]<< ") et ayant a = " << a << endl;
  
  // Création des colonnes dans la grille grâce à la direction du vecteur {0,1}
  MPI_Cart_sub(Comm_grille, vecColonne, &Comm_colonne);

  // Création des lignes {1,0}
  MPI_Cart_sub(Comm_grille, vecLigne, &Comm_ligne);

  // Définition du root pour l'ensemble des colonnes 
  MPI_Cart_rank(Comm_colonne, coordsRoot, &root_comm_col);

  // Somme (MPI_SUM) du bas de la colonne vers le haut : en résulte une grille de 1 ligne
  MPI_Reduce(&a, &somme, 1, MPI_INT, MPI_SUM, root_comm_col, Comm_colonne);

  // On récupère le pid du processeur
  MPI_Comm_rank(Comm_colonne, &pid);

  // Somme des éléments la ligne obtenue grace au reduce des colonne vers root
  if (pid==root_comm_col){
    MPI_Cart_rank(Comm_ligne, coordsRoot, &root_comm_ligne);
    MPI_Reduce(&somme, &somme_finale, 1, MPI_INT, MPI_SUM, root_comm_ligne, Comm_ligne);
    MPI_Comm_rank(Comm_ligne, &pid);
    
    if(pid==root_comm_ligne){
      cout << "je suis le pid: " << pid << " aux coordonnées (=" << coords[0] << ", " << coords[1]<< ") et ayant la somme finale  = " << somme_finale << endl;
    }

  }



  MPI_Finalize() ;



  return 0 ;
}