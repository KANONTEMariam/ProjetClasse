#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/sem.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	pid_t pid1,pid2,pid3;
	int status;
	key_t key = ftok("shmfile",65); 
	int i,a=0;
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
	char *str = (char*) shmat(shmid,(void*)0,0);
	sprintf(str, "%d", a);
	pid1 = fork();
    	if(pid1 < 0){
		perror("Erreur de création du processus\n");
		exit(EXIT_FAILURE);
    	}
	if(pid1 == 0){
		//printf("%d",pid1);
		//a = a + 1;
		for(i=0; i < 5 ;i++){
			// lecture de a
			a = atoi(str);
			//printf("Proc %d %d\n", getpid(), a);
			// modification de a
			a = a + 10;
			sleep(a);
			// ecriture de a
			sprintf(str, "%d", a);
		}
    	}
	else
	{
		sleep(7);
		pid2 = fork();
	    	if(pid1 < 0){
			perror("Erreur de création du processus\n");
			//pid1 = wait(&status);
			exit(EXIT_FAILURE);
	    	}
		if(pid2 == 0){
			//printf("%d",pid2);
			//a = a + 1;
			for(i=0; i < 5; i++){
				// lecture de a
				a = atoi(str);
				//printf("Proc %d %d\n", getpid(), a);
				// modification de a
				a = a + 1;
				sleep(a);
				// ecriture de a
				sprintf(str, "%d", a);
			}
	    	}
		else
		{
			sleep(7);
			pid3 = fork();
		    	if(pid3 < 0){
				perror("Erreur de création du processus\n");
				//pid1 = wait(&status);
				//pid2 = wait(&status);
				exit(EXIT_FAILURE);
		    	}
			if(pid3 == 0){
				//printf("%d",pid3);
				//a = a + 1;
				for(i=0; i < 5; i++){
				     // lecture de a
				     a = atoi(str);
				     //printf("Proc %d %d\n", getpid(), a);
				     // modification de a
				     a = a + 1;
				     sleep(a);
				     // ecriture de a
				     sprintf(str, "%d", a);
				}
	    		}
			else
			{
				//pid1 = wait(&status);
				printf("Le pid du fils 1 est %d\n", pid1);
				//pid2 = wait(&status);
				printf("Le pid du fils 2 est %d\n", pid2);
				//pid3 = wait(&status);
				printf("Le pid du fils 3 est %d\n", pid3);
				a = atoi(str);
				printf("Valeur Finale de a = %d\n", a);
				//detacche str de la mémoire partagée
				shmdt(str); 
						
			}
		}
	}
	return 0;
}
