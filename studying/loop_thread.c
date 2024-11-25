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
	pthread_t	pth[8];
	int			i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 8)
	{
		if (pthread_create(&pth[i], NULL, add_email, NULL) != 0)
		{
			perror("Error creating a thread\n");
			return (1);
		}
		printf("Thread %i started execution\n", i + 1);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(pth[i], NULL) != 0)
			return (2);
		printf("Thread %i joined execution\n", i + 1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Mails: %i\n", mails);
	return (0);
}