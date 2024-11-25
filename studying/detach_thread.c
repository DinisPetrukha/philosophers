// A detached thread its a thread that we do not need to return a value,
// by using the pthread_join, the process waits until the pthread finish
// its execution, and we can manage the returned value from that thread
// By doing pthread_detach(), the process no longer waits to pthread finish
// its execution, and when the main process its done, those pthreads will
// clean their memory by its own. This is a good option when we have multiple
// long executions, and we do not need to wait the threads to end to execute
// our main program
// maybe, this can be some infinite loop that will do something during entire
// program until the main finishes

// 				Multi-Threaded Program
// |
// |	...							pthread
// |	pthread_create --------
// |	...						|	...
// |	printf("%d\n", sum);	|	do work
// |	...						|	...
// |	pthread_join --------	|
// |	...			|
// |	...		   \/
// |			Execution PAUSES here until
// 				thread is done work


// 			Detached Thread Program
// |
// |	...							pthread
// |	pthread_create ---------
// |	pthread_detach			|	...
// |	...						|	...
// |	do work					|	do work
// |	...						|	...
// |	...						|	...
// |	...						|	...
// |	exit					|->	resources
// |							|	released

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void	*routine()
{
	int	i;

	i = 0;
	while (i < 10)
	{
		printf("Hello %i\n", i);
		//usleep(1);
		i++;
	}
}

int	main(void)
{
	pthread_t	pth[2];
	int			i;

	i = 0;
	while (i < 2)
	{
		if (pthread_create(&pth[i], NULL, routine, NULL) != 0)
			perror("Error Creating thread\n");
		i++;
		pthread_detach(pth[i]);
	}
	//return (0);
}