#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void shift_droite_gauche_circulaire(int n, int* in, int* out)
{
  int pid, nprocs;
  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  int lenSousTab = n/2;
  int gauche = (pid-1+nprocs)%nprocs;
  int droite = (pid+1)%nprocs;

  int *tabgaucheS = new int[lenSousTab];
  int *tabdroitS = new int[lenSousTab];
  int *tabgaucheR = new int[lenSousTab];
  int *tabdroitR = new int[lenSousTab];

  for (int i = 0; i < n; i++){
    if(i < lenSousTab){
      tabgaucheS[i] = in[i];
    }else{
      tabdroitS[i-lenSousTab] = in[i];
    }
  }

  if(nprocs % 2 == 0) {
    if (pid % 2 == 0){
      MPI_Send(tabgaucheS,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD);
      MPI_Send(tabdroitS,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD);
      MPI_Recv(tabgaucheR,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD,&status);
      MPI_Recv(tabdroitR,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD,&status);
    }else{
      MPI_Recv(tabdroitR,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD,&status);
      MPI_Recv(tabgaucheR,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD,&status);
      MPI_Send(tabdroitS,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD);
      MPI_Send(tabgaucheS,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD);
    }
  }else{
    if (pid % 2 == 0){
      if (pid == 0){ 
        MPI_Send(tabdroitS,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD);
        MPI_Recv(tabgaucheR,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD,&status);
        MPI_Recv(tabdroitR,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD,&status);   
        MPI_Send(tabgaucheS,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD);
      }else{
        //paires
        MPI_Send(tabgaucheS,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD);
        MPI_Send(tabdroitS,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD);
        MPI_Recv(tabgaucheR,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD,&status);
        MPI_Recv(tabdroitR,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD,&status);
      }
    }else{
      //impaires
      MPI_Recv(tabdroitR,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD,&status);
      MPI_Recv(tabgaucheR,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD,&status);
      MPI_Send(tabdroitS,lenSousTab,MPI_INT,droite,0,MPI_COMM_WORLD);
      MPI_Send(tabgaucheS,lenSousTab,MPI_INT,gauche,0,MPI_COMM_WORLD);
    }
  }
    

  

  for (int i = 0; i < n; i++){
    if(i < lenSousTab){
      out[i] = tabgaucheR[i];
    }else{
      out[i] = tabdroitR[i - lenSousTab];
    }
  }


}

void shift_droite_gauche(int n, int* in, int* out)
{
}

int main ( int argc , char **argv )
{
  int pid, nprocs;  
  MPI_Status status;
  MPI_Init (&argc , &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid ) ;
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs ) ;
  
  int nlocal = 2*atoi(argv[1]);
  int* tablocal = new int[nlocal];
  int* tabres = new int[nlocal];

  srand(time(NULL)+pid);
  for (int i=0; i<nlocal; i++)
    tablocal[i] = rand()%10;
  
  cout << "je suis " << pid << " et j'ai le tableau initial : ";
  for (int i=0; i<nlocal; i++)
    cout << tablocal[i] << " ";
  cout << endl;

  //shift_droite_gauche(nlocal,tablocal,tabres);
  shift_droite_gauche_circulaire(nlocal,tablocal,tabres);
  
  cout << "je suis " << pid << " et j'ai le tableau final : ";
  for (int i=0; i<nlocal; i++)
    cout << tabres[i] << " ";
  cout << endl;
  
  delete[] tablocal;
  delete[] tabres;
  MPI_Finalize() ;
  return 0 ;
}
