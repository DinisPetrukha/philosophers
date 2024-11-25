#include <stdio.h>
#include <pthread.h>

void	*computation(void *add)
{
	int sum = 0;
	long *add_num = (long *) (add);

	for (long i = 0; i < 1000000000; i++)
		sum += *add_num;
	printf("Add: %ld\n", *add_num);
	return (NULL);
}

int	main()
{
	pthread_t	thread1;
	pthread_t	thread2;

	long	value1 = 1;
	long	value2 = 2;

	// Multi-threaded execution of function computation()
	pthread_create(&thread1, NULL, computation, (void *)&value1);	//Creating a thread
	pthread_create(&thread2, NULL, computation, (void*) &value2);
	pthread_join(thread1, NULL);						//Join the thread execution, with the main
	pthread_join(thread2, NULL);

	// Same is down here, but the execution its single-threaded
	// computation((void *) &value1);
	// computation((void *) &value2);

	// What happens is that the multi threaded manner takes less time to execute
	return (0);
}