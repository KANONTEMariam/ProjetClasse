#include <stdlib.h>
#include <stdio.h>

#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/sem.h>
#include <errno.h>
#include <sys/types.h>

int main (int argc, char* argv[])
{
    int ordreMatrice = atoi(argv[1]), nbElementMatrice;
    int i = atoi(argv[2]);
    int j = atoi(argv[3]);
    int a, b;
    int* tabI = NULL, *tabJ = NULL;
    int *matrice = NULL;
    int cIJ = 0;
    
    int shmidMatrice;
    key_t keyMatrice;
    
    nbElementMatrice = ordreMatrice * ordreMatrice;
    
    
    printf("Processus c[%d,%d]: %d\n", i, j, getpid());
    
    tabI = malloc(ordreMatrice * sizeof(int));
    
    if (tabI == NULL) {
        printf("Processus c[%d,%d]: Allocation de mémoire impossible\n", i, j);
        exit(EXIT_FAILURE);
    }
    
    tabJ = malloc(ordreMatrice * sizeof(int));
    
    if (tabJ == NULL) {
        printf("Allocation de mémoire impossible\n");
        free(tabI);
        exit(EXIT_FAILURE);
    }
    
    keyMatrice = ftok("shmMatrice", 19);
    shmidMatrice = shmget(keyMatrice, 2 * nbElementMatrice * sizeof(int), 0666);
    matrice = (int*) shmat(shmidMatrice,(void*)0,0);
    
    if (matrice == NULL) {
        printf("Processus c[%d,%d]: Lecture de la mémoire partagée impossible\n", i, j);
        free(tabI);
        free(tabJ);
        exit(EXIT_FAILURE);
    }
    
//Copie des données c[i,j]
    for (a = 0; a < ordreMatrice; a++) {
        tabI[a] = matrice[i*ordreMatrice + a];
        tabJ[a] = matrice[j+ ordreMatrice * a];
    }
    
//Affichage des c[i,j] du processus
    printf("c[i]: ");
    for (a = 0; a < ordreMatrice-1; a++) printf("%d, ", tabI[a]);
    printf("%d", tabI[a]);
    putchar('\n');
    printf("c[j]: ");
    for (a = 0; a < ordreMatrice-1; a++) printf("%d, ", tabJ[a]);
    printf("%d", tabJ[a]);
    printf("\n\n");
    
//Calcul du c[i,j] et enregistrement du c[i,j]
    matrice[i*ordreMatrice + j + nbElementMatrice] = 0;
    for (a = 0; a < ordreMatrice; a++) {
        matrice[i*ordreMatrice + j + nbElementMatrice] += tabI[a] * tabJ[a];  
    }
    printf("%d %d\n", i*ordreMatrice+j, matrice[i*ordreMatrice + j + nbElementMatrice]);
       
    shmdt(matrice);
    
    free(tabI);
    free(tabJ);
    
    return 0;
}
