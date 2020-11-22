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

  MPI_Status status;
  MPI_Comm CommGraph;

  int edges[12] = {1,2,0,2,3,4,0,1,1,4,1,3};
  int index[5] = {2,6,8,10,12};

  int a = pid;

  MPI_Graph_create(MPI_COMM_WORLD, 5, index, edges, true, &CommGraph);

  int pid_graph;

  MPI_Comm_rank(CommGraph, &pid_graph);

  cout << "pid=" << pid << " pid_graph=" << pid_graph << endl;
  int nb_v;
  MPI_Graph_neighbors_count(CommGraph,pid,&nb_v);
  int* v = new int[nb_v];
  MPI_Graph_neighbors(CommGraph, pid, nb_v,v );


  int b;
  int res = a;
  for (int i=0; i<nb_v; i++) {
    MPI_Sendrecv (&a, 1, MPI_INT, v[i], 123, &b, 1, MPI_INT, v[i], MPI_ANY_TAG, CommGraph,
                  &status);
    res += b;
  }

  cout << "pid=" << pid << " res=" << res << endl;

  MPI_Comm_free(&CommGraph);
  MPI_Finalize() ;
  return 0 ;
}
