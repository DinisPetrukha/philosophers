/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:07:28 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/08 14:28:44 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_all_to_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_dead_lock);
		data->philos[i].philo_dead_flag = 1;
		pthread_mutex_unlock(&data->philos[i].philo_dead_lock);
		i++;
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error gettimeofday()");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		if (philo)
		{
			pthread_mutex_lock(philo->dead_lock);
			if (*philo->dead)
			{
				pthread_mutex_unlock(philo->dead_lock);
				return (0);
			}
			pthread_mutex_unlock(philo->dead_lock);
		}
		usleep(500);
	}
	return (0);
}

void	clean_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->thread_initializer);
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->philos[i].philo_dead_lock);
		pthread_mutex_destroy(&data->philos[i].philo_meal_lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}
