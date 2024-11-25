#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function()
{
	printf("Thread start\n");
	sleep(3);
	printf("Thread end\n");
}

int	main(void)
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, thread_function, NULL);
	pthread_create(&t2, NULL, thread_function, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("As we can see, the threads are running simultaneously\n");
	return (0);
}