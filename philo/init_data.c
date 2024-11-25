/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:58:21 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/08 14:04:50 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error pthread_mutex_init fork");
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philos2(t_data *data, char *argv[], int i)
{
	data->philos[i].id = (i + 1);
	data->philos[i].dead = &data->dead_flag;
	data->philos[i].start = get_time();
	data->philos[i].philo_dead_flag = 0;
	data->philos[i].n_philos = (size_t)ft_atoi(argv[1]);
	data->philos[i].t_die = (size_t)ft_atoi(argv[2]);
	data->philos[i].t_eat = (size_t)ft_atoi(argv[3]);
	data->philos[i].t_sleep = (size_t)ft_atoi(argv[4]);
}

static int	init_philos(t_data *data, int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < data->main_n_philos)
	{
		data->philos[i].dead_lock = &data->dead_lock;
		if (pthread_mutex_init(&data->philos[i].philo_meal_lock, NULL) != 0)
			return (printf("Error pthread_mutex_init philo_meal_lock\n"));
		if (pthread_mutex_init(&data->philos[i].philo_dead_lock, NULL) != 0)
			return (printf("Error pthread_mutex_init philo_dead_lock\n"));
		data->philos[i].meal_lock = &data->meal_lock;
		data->philos[i].write_lock = &data->write_lock;
		data->philos[i].meal_count_lock = &data->meal_count_lock;
		init_philos2(data, argv, i);
		data->philos[i].last_meal = get_time() + data->philos[i].t_die;
		if (argc == 6)
			data->philos[i].n_times_to_eat = (size_t)ft_atoi(argv[5]);
		data->philos[i].l_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].r_fork = &data->forks[data->n_philos - 1];
		else
			data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char *argv[])
{
	data->n_philos = ft_atoi(argv[1]);
	data->main_n_philos = data->n_philos;
	if (argv[5])
		data->main_n_times_to_eat = ft_atoi(argv[5]);
	data->dead_flag = 0;
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (printf("Error pthread_mutex_init dead_lock\n"));
	if (pthread_mutex_init(&data->thread_initializer, NULL) != 0)
		return (printf("Error pthread_mutex_init thread_lock\n"));
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (printf("Error pthread_mutex_init meal_lock\n"));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (printf("Error pthread_mutex_init write_lock\n"));
	if (pthread_mutex_init(&data->meal_count_lock, NULL) != 0)
		return (printf("Error pthread_mutex_init meal_count_lock\n"));
	if (init_forks(data) != 0)
		return (4);
	if (init_philos(data, argc, argv) != 0)
		return (5);
	return (0);
}
