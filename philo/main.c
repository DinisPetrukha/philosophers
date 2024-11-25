/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:33:43 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/11 11:13:09 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	static t_philo				philosophers[MAX_PHILO];
	static pthread_mutex_t		forks_array[MAX_PHILO];
	static t_data				data;

	data.philos = philosophers;
	data.forks = forks_array;
	if (check_error(argc, argv))
		return (1);
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Error initializing data\n");
		return (2);
	}
	if (create_threads(&data) != 0)
	{
		printf("Error creating threads\n");
		return (3);
	}
	clean_mutex(&data);
	return (0);
}
