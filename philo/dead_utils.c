/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:27:32 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/07 12:43:52 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	finish_the_game(t_data *data)
{
	if (!philo_dead_getter(data))
	{
		pthread_mutex_lock(&data->dead_lock);
		data->everybody_eaten = 1;
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
		set_all_to_dead(data);
	}
}

void	print_dead(t_data *data, t_philo *philo)
{
	size_t	cur_time;

	pthread_mutex_lock(&data->dead_lock);
	if (data->everybody_eaten == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&data->dead_lock);
	cur_time = get_time() - philo->start;
	pthread_mutex_lock(philo->write_lock);
	printf("%li %i died\n", cur_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

int	dead_getter(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_flag == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

int	philo_dead_getter(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_dead_lock);
		if (data->philos[i].philo_dead_flag == 1)
		{
			pthread_mutex_unlock(&data->philos[i].philo_dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].philo_dead_lock);
		i++;
	}
	return (0);
}

int	is_not_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}
