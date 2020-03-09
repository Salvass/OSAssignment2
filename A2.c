#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	
	pid_t pid;
	int pipeFD[2];
	int ret;
	char buf[50];

	ret = pipe(pipeFD);
	if(ret == 1){
		perror("pipe error");
		exit(1);
	}
	
	
	
	pid = fork();
	if(pid ==0)
	{
		dup2(pipeFD[0], STDIN_FILENO);
		//child process
		printf("Child process1\n");
		close(pipeFD[1]);
			
		//read(pipeFD[0], buf, 20);
		
		scanf("%s", buf);
		close(pipeFD[0]);	
		write(pipeFD[1],buf,6);
		printf("Buf1: %s \n",buf);
		exit(0);
	}
	if(pid > 0)
	{
				
	
		pid_t pid2;
		pid2 = fork();
		if(pid2==0){
					dup2(pipeFD[0], STDIN_FILENO);

				//child process
			printf("Child process2\n");
			close(pipeFD[1]);
			//close(pipeFD[0]);		
			//read(pipeFD[0], buf, 20);
			scanf("%s", buf);
			
			printf("Buf2: %s \n",buf);
			exit(0);
		}
		else{
				printf("Parent process\n");

			    dup2(pipeFD[1], STDOUT_FILENO);

			//parent process
	close(pipeFD[0]);
	close(pipeFD[1]);
	//write(pipeFD[1],"hello people!",14);//13 = number of characters in second argument of write
	// try this
	printf("%s", "salva");
			//wait(pid2);
			}
	}
	return 0;
}
