/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:02:55 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/11 11:12:55 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_meal_lock);
	if (get_time() > philo->last_meal && philo->eating == false)
	{
		pthread_mutex_unlock(&philo->philo_meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_meal_lock);
	return (0);
}

static void	*ft_monitor(void *ptr)
{
	t_data	*data;
	int		i;

	data = ptr;
	ft_usleep(15, NULL);
	while (1)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (philo_dead_getter(data) || check_last_meal(&data->philos[i]))
			{
				pthread_mutex_lock(&data->dead_lock);
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->dead_lock);
				set_all_to_dead(data);
				print_dead(data, &data->philos[i]);
				return (NULL);
			}
			i++;
		}
	}
}

void	*check_times_eaten(void *ptr)
{
	t_data	*data;
	int		i;
	int		everybody_eaten;

	data = (t_data *)ptr;
	while (philo_dead_getter(data) == 0)
	{
		i = -1;
		everybody_eaten = 1;
		while (++i < data->n_philos)
		{
			pthread_mutex_lock(data->philos[i].meal_count_lock);
			if (data->philos[i].eaten_enough == 0)
			{
				everybody_eaten = 0;
				pthread_mutex_unlock(data->philos[i].meal_count_lock);
				break ;
			}
			pthread_mutex_unlock(data->philos[i].meal_count_lock);
		}
		if (everybody_eaten == 1)
			break ;
	}
	finish_the_game(data);
	return (NULL);
}

int	join_threads(t_data *data)
{
	int	i;

	if (pthread_join(data->monitor, NULL) != 0)
		return (1);
	if (data->main_n_times_to_eat)
	{
		if (pthread_join(data->waiter, NULL) != 0)
		{
			printf("Error joining waiter thread\n");
			return (1);
		}
	}
	i = 0;
	while (i < data->main_n_philos)
	{
		if (pthread_join(data->philos[i].t, NULL) != 0)
		{
			printf("Error joining philosopher\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	if (pthread_create(&data->monitor, NULL, &ft_monitor, data) != 0)
	{
		return (1);
	}
	if (data->main_n_times_to_eat)
	{
		if (pthread_create(&data->waiter, NULL, &check_times_eaten, data) != 0)
			return (2);
	}
	i = 0;
	while (i < data->main_n_philos)
	{
		if (pthread_create(&data->philos[i].t, NULL, &r, &data->philos[i]) != 0)
			return (3);
		i++;
	}
	if (join_threads(data) != 0)
		return (4);
	return (0);
}
