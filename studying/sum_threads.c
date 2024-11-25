#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int	array[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 27};

void	*routine(void *arg)
{
	int	start;
	int	sum;
	int	i;

	start = *(int *)arg;
	sum = 0;
	i = 0;
	while (i < 5)
	{
		sum += array[i + start];
		i++;
	}
	*(int *)arg = sum;
	return (arg);
}

int	main(void)
{
	pthread_t	pth[2];
	int			i;
	int			*i_ptr;
	int			global_sum;

	i = 0;
	while (i < 2)
	{
		i_ptr = malloc(sizeof(int));
		*i_ptr = i * 5;
		if (pthread_create(&pth[i], NULL, routine, i_ptr) != 0)
		{
			perror("Error creating thread\n");
		}
		i++;
	}
	i = 0;
	global_sum = 0;
	while (i < 2)
	{
		int			*thread_sum;
		if (pthread_join(pth[i], (void **)&thread_sum) != 0)
			perror("Error joining thread");
		global_sum += *thread_sum;
		free(thread_sum);
		i++;
	}
	printf("Global sum: %i\n", global_sum);
}