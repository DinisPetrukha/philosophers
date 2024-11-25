#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void *roll_dice()
{
	int	value = (rand() % 6 )+ 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	return (result);
}

int	main(void)
{
	int			*res;
	pthread_t	pth[6];
	int			i;

	srand(time(NULL));
	i = 0;
	while (i < 6)
	{
		if (pthread_create(&pth[i], NULL, roll_dice, NULL) != 0)
		{
			perror("Error creating thread\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < 6)
	{
		if (pthread_join(pth[i], (void *)&res) != 0)
		{
			perror("Error joining thread\n");
			return (2);
		}
		printf("Random number thread %i: %i\n", i + 1, *res);
		free(res);
		i++;
	}
	return (0);
}