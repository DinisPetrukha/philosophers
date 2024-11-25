// mutex is like "locks" that execute some part of the code only when other thread its not touching
// the same memory at the same time. This prevents the program of trace racings.
// with the mutex function, will lock a part of code when some thread is touching some thread and
// unlock after.

// A mutex is a synchronization primitive that enforces
// limits on access to a shared resource when we have
// multiple thread of execution

#include <stdio.h>
#include <pthread.h>

int	mails = 0;
pthread_mutex_t mutex;

void	*add_email()
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex); // Only 1 thread can access this section
		mails++;					// of code at a time
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}


int	main(void)
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&t1, NULL, add_email, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, add_email, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	pthread_mutex_destroy(&mutex);
	printf("Mails: %i\n", mails);
}