#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd = open("file.txt", O_RDONLY); //Open the file in read only mode
	pid_t pid = fork(); //Fork and store the return value
	
	if(pid == 0) //This is the child process
	{
		printf("*** Output of the child process: ***\n");
		
		while(1) //Read whole file
		{
			char buffer[512] = {0}; //Initialize with zero
			size_t size = read(fd, buffer, 511); //Read from file
			
			if(size != 0) //Not reached EOF yet
				printf("%s", buffer);
			else //Reached EOF, so break
				break;
		}
	}
	
	else if(pid > 0) //This is the parent process
	{ 
                 printf("in");
		waitpid(pid, NULL, 0); //Wait for the child to finish
		printf("\n*** Output of the parent process: ***\n");
		lseek(fd, SEEK_SET, 0); //This line will be explained below
		
		while(1) //Read whole file
		{
			char buffer[512] = {0}; //Initialize with zero
			size_t size = read(fd, buffer, 511); //Read from file
			
			if(size != 0) //Not reached EOF yet
				printf("%s", buffer);
			else //Reached EOF, so break
				break;
		} 
		
		close(fd); //Close the file in parent process
	}
	
	else //Fork failed if pid < 0
		printf("Error at fork()!\n");
	
	/*
	* Content of the file is printed only once
	* because they share the file descriptor.
	* File pointer reaches the end at the end of
	* child process. Parent process tries to
	* continue where it is left and prints nothing.
	* If you uncomment lseek(), parent process will
	* also print the content of the file since file
	* pointer will be set back to the begining.
	*/ 
}
