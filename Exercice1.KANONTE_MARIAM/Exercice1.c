#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid1,pid2,pid3;
	int status;
	pid1 = fork();
    	if(pid1 < 0){
		perror("Erreur de création du processus\n");
		exit(EXIT_FAILURE);
    	}
	if(pid1 == 0){
		//printf("%d",pid1);
    	}
	else
	{
		pid2 = fork();
	    	if(pid1 < 0){
			perror("Erreur de création du processus\n");
			//pid1 = wait(&status);
			exit(EXIT_FAILURE);
	    	}
		if(pid2 == 0){
			//printf("%d",pid2);
	    	}
		else
		{
			pid3 = fork();
		    	if(pid3 < 0){
				perror("Erreur de création du processus\n");
				//pid1 = wait(&status);
				//pid2 = wait(&status);
				exit(EXIT_FAILURE);
		    	}
			if(pid3 == 0){
				//printf("%d",pid3);
	    		}
			else
			{
				//pid1 = wait(&status);
				printf("Le pid du fils 1 est %d\n", pid1);
				//pid2 = wait(&status);
				printf("Le pid du fils 2 est %d\n", pid2);
				//pid3 = wait(&status);
				printf("Le pid du fils 3 est %d\n", pid3);
			}
		}
	}
	return 0;
}
