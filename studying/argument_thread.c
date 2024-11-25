#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int	array[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 27};

void	*routine(void *arg)
{
	int	i;
	i = *(int *)arg;
	printf("Thread %i, prime: %i\n", i, array[i]);
	free(arg);
}

int	main(void)
{
	pthread_t	pth[10];
	int			i;
	int			*i_ptr;

	i = 0;
	while (i < 10)
	{
		i_ptr = malloc(sizeof(int));
		*i_ptr = i;
		pthread_create(&pth[i], NULL, routine, i_ptr);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(pth[i], NULL);
		i++;
	}
	printf("As you can see, we do not execute in order\nwe are threads :p\n");
}