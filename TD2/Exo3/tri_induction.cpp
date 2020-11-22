#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*!
 * pour calculer un indice local à partir d'un indice global
 * /param n la taille totale du tableau
 * /param i_global l'indice dans le tableau complet
 * /return i_local l'indice du tableau en local
 */
int global_to_local(int n, int i_global)
{
  return 0;
}

/*!
 * pour calculer un indice global à partir d'un indice local
 * /param n la taille totale du tableau
 * /param i_local l'indice local initial
 * /return i_global l'indice de l'élément correspondant dans le tableau global
 */
int local_to_global(int n, int i_local)
{
  return 0;
}

/*!
 * pour calculer le numéro du processeur destinataire à partir d'un indice dans le tableau total
 * /param n la taille totale du tableau
 * /param i_global l'indice dans le tableau global
 * /return pid_dest le numéro du processeur propriétaire de l'élément
 */
int pid_dest(int n, int i_global)
{
  return 0;
}

/*! 
 * Petite fonction pour etre sûr de générer un tableau dont tous les éléments sont distincts
 * \param n la taille du tableau total
 * \param tab le tableau à construire
 * \param graine pour initialiser le processus de génération aléatoire de nombre
 */
void generation(int n, int* tab, int graine)
{  
  srand(time(NULL)+graine);
  //srand(2*graine+10);
  for (int i=0; i<n; i++) {
    bool test = true;
    while (test) {
      test = false;
      tab[i] = rand()%50;
      for (int j=0; j<i; j++) 
	if (tab[i]==tab[j]) 
	  test = true;
    }
  }
}

int main ( int argc , char **argv )
{
  int pid, nprocs;  
  MPI_Init (&argc , &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid ) ;
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs ) ;
  MPI_Request request;
  MPI_Status status;
  
  int n = atoi(argv[1]);
  int root = atoi(argv[2]);

  int* tab_global = new int[n];
  int* tab_local;
  
  if (pid==root)   
    generation(n,tab_global,pid);  
  
  MPI_Finalize() ;
  return 0 ;
}
