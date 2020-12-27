#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc , char* argv[])
{
	for(int i = 0; i < 3; i++) //Create 3 child processes
	{
		if(fork() == 0) //Do this part only on child processes
		{
			printf("Child process with pid %d is started and finished.\n", getpid());
                     
                        exit(0);
                        printf("over now.\n");

		}
	}
	printf("Parent process will sleep for 2 seconds and then output ps...\n");
	sleep(2); //Sleep to ensure that children are done executing
	//Using waitpid() here is the correct way, but we want them to be zombies
	
	printf("Output of ps:\n");
	execvp(argv[1], &argv[1]);
        //system("ps"); //Don't use system() unless you have to
	//Used it here to make things simpler, you can also run ps from terminal
	
	printf("Parent process will be terminated in 2 seconds...\n");
	sleep(2);
	return 0;
}
