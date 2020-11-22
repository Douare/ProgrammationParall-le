#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct max_loc {
    int max;
    int pos;
};


void generation_aleatoire(int n, int *tab, int graine, int max) {
    srand(time(NULL) + graine);
    //srand(2*graine+10);
    for (int i = 0; i < n; i++)
        tab[i] = rand() % (max + 1);
}

struct max_loc* calcul_max(int n, int* tab, int indice) {
    int pid, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int max = 0;
    int j = 0;
    max_loc *tabmax = new max_loc;
    for(int i=0; i<n; i++){
        if(tab[i]>max){
            max = tab[i];
            j = i;
        }
    }
    tabmax->max = max;
    tabmax->pos = indice+j;
    return tabmax;
  
}

int main(int argc, char **argv) {
    int pid, nprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Request request;
    MPI_Status status;

    int n = atoi(argv[1]); // la taille du tableau global
    int root = atoi(argv[2]); // le processeur root

    // Mes initialisations
    int *tab_global;
    int quot = n/nprocs;
    int reste = n%nprocs;
    int *nombreElements = new int[nprocs];
    int *indiceElements = new int[nprocs];
    int *tabRcv = new int[nprocs];
    max_loc *maxLocPid = new max_loc;
    max_loc *maxLocRcv;


    if (pid == root) {
        tab_global = new int[n];
        generation_aleatoire(n, tab_global, pid, 50);
        cout << "je suis : " << pid << " et le tableau initial est ";
        for (int i = 0; i < n; i++)
            cout << tab_global[i] << " ";
        cout << endl;
    }

    // Distribution du tableau
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
    // Récupération du max dans le tab de pid
    maxLocRcv = calcul_max(nombreElements[pid],tabRcv, indiceElements[pid]);
    // On met le max dans maxLocPid et on reçoit dans le root
    MPI_Reduce(maxLocRcv, maxLocPid, 1, MPI_2INT, MPI_MAXLOC, root, MPI_COMM_WORLD);
    // On affiche  

    if (pid == root)
    {
        cout << "Le max est : " << maxLocPid->max << " à l'indice : " << maxLocPid->pos << endl;
    }

    MPI_Finalize();
    return 0;
}
