#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	int pid, pd[2]; //pd[0] is for reading, pd[1] is for writing
	
	if(pipe(pd) == -1) //Create the pipe and check for errors
	{
		printf("Error at pipe()!\n");
		exit(EXIT_FAILURE);
	}
	
	pid = fork(); //May the fork be with you
	
	if(pid > 0) //I am your father!
	{        printf("uuuuu \n");
		char message[512] = {0}; //Initialize with zero
		printf("coming in baby \n");
		read(pd[0], message, 511); //Wait for child to fill the pipe
		printf("Parent process got message from the child: %s", message);
	}
	
	else if(pid == 0) //NOOOOOOOO!!!!
	{
		size_t size = 0;
		char *line = NULL;
		
		printf("Child process waiting for input: ");
		getline(&line, &size, stdin); //Get a line of input from terminal
		write(pd[1], line, size); //Write it to pipe
		free(line);
	}
	
	else //Fork failed
	{
		printf("Error at fork()!\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
