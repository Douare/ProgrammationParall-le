#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*! 
 * Pour tester si une suite est une suite de syracuse (à partir du premier élément du tableau)
 * \param n la taille du tableau (la suite)
 * \param tab la suite à tester
 * \return 0 si ce n'est pas une suite de Syracuse 1 sinon
 */
int test_syracuse(int n, int* tab)
{
  if (tab[0]<=0){
    return 0;
  }
  for (size_t i = 1; i < n; i++) {
    if (tab[i-1]%2 ==0){
      if(tab[i]!=tab[i-1]/2) {
        return 0;
      }
    }else{
      if(tab[i] !=(3*tab[i-1]+1)){
        return 0;
      }
    }
  }
  return 1;
}


/*!
 * génération d'une suite de Syracuse à partir de U0=x
 * \param n la taille voulue
 * \param tab le tableau qui enregistre la suite
 * \param x la valeur initiale
 */
void syracuse(int n, int* tab, int x)
{
  tab[0] = x;
  for (int i=1; i<n; i++) {
    if (tab[i-1]%2==0)
      tab[i] = tab[i-1]/2;
    else
      tab[i] = 3*tab[i-1]+1;
  }
}

/*!
 * génération aléatoire d'une suite quelconque
 * \param n la taille voulue
 * \param tab le tableau qui enregistre la suite
 * \param graine pour le processus de génération aléatoire
 */
void non_syracuse(int n, int* tab, int graine)
{
  srand(time(NULL)+graine);
  //srand(2*graine+10);  
  for (int i=0; i<n; i++) 
    tab[i] = rand()%50;
}

int main ( int argc , char **argv )
{
  int pid, nprocs;  
  MPI_Init (&argc , &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid ) ;
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs ) ;
  MPI_Request request;
  MPI_Status status;
  
  int n = atoi(argv[1]); // la taille du tableau global
  int root = atoi(argv[2]); // le processeur root
  int x = atoi(argv[3]); // le x pour générer une suite de syracuse
  int cas = atoi(argv[4]);  // les différentes générations possibles
  
  int* tab_global = new int[n];

  // Mes initialisations
  int quot = n/nprocs;
  int reste = n%nprocs;
  int *nombreElements = new int[nprocs];
  int *indiceElements = new int[nprocs];
  int isSyracuse, isSyracuseRcv;
  int *tabRcv = new int[nprocs];

  
  if (pid==root) {
    switch(cas) {
    case 0:
      cout << "test génération aléatoire"<< endl;
      non_syracuse(n,tab_global,pid);
      break;
    case 1:
      cout << "test syracuse partiel"<< endl;
      syracuse(n/2,tab_global,x); 
      non_syracuse(n-n/2,(tab_global+n/2),pid);
      break;
    default:
      cout << "test syracuse"<< endl;
      syracuse(n,tab_global,x);
    }
  }
  if (pid==root){
    cout << "je suis :" << pid << " ";
    for (int i=0; i<n; i++)
      cout << tab_global[i] << " ";
    cout << endl;
  }

  // On utilise scatterv pour partager le tableau en sous-tableaux (1 par proc) 
  // On gère les ghosts en ajoutant l'élément qui précède chaque sous-tableau aux sous-tableaux
  for (int i = 0; i < nprocs; ++i){
        if (reste > i){
            nombreElements[i] = quot + 1;
        }else{
            nombreElements[i] = quot;
        }
        if (i == 0){
            indiceElements[i] = i;
        }else{
            indiceElements[i] = indiceElements[i-1]+nombreElements[i-1]; 
        }
    }
    MPI_Scatterv(tab_global,nombreElements, indiceElements, MPI_INT, tabRcv, quot+1, MPI_INT, root, MPI_COMM_WORLD);
    isSyracuseRcv = test_syracuse(nombreElements[pid],tabRcv);
    MPI_Reduce(&isSyracuseRcv, &isSyracuse, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

  if (pid==root){
    if(isSyracuse == nprocs){
      cout << "La suite est syracuse" << endl;
    }else{
      cout << "La suite n'est pas syacuse" << endl;
    }
  }
    
  
  MPI_Finalize() ;
  return 0 ;
}
